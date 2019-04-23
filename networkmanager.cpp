#include "networkmanager.h"
#include "JsonParser.h"
namespace sta {
	NetworkManager::NetworkManager() :
		mCurrentDevice{ nullptr }, mAddressHandle{ nullptr }{
	
			//initialises socket use (socket should be  closed in destructor)
			WSADATA wsaData = { 0 };
			WSAStartup(MAKEWORD(2, 2), &wsaData);
	}	
	NetworkManager::~NetworkManager() {
		mThread.requestInterruption();
		mThread.quit();
		mThread.wait();
		if (mAllDevices.size() > 0)
			pcap_freealldevs(mAllDevices.front());
		WSACleanup();
	}
	void NetworkManager::selectDevice(int index) {
		//cancel future execution, open adapter sesion and runs a listen on it

		mCurrentDevice = getDevices()[index];
		openAdapter();
		auto restOfCode = [this]() {
			mPacketCapture = new CaptureClass{};
			mPacketCapture->moveToThread(&mThread);
			connect(&mThread, &QThread::started, [this]() { mPacketCapture->startCapture(this); });
			connect(&mThread, &QThread::started, [this]() {emit newAdapterClearData(); });
			connect(&mThread, &QThread::finished, mPacketCapture, &QObject::deleteLater);
			mThread.start();
		};

		if (mPacketCapture) {
			emit toolbarMessage("Changing session");
			connect(&mThread, &QThread::finished, this, restOfCode, Qt::QueuedConnection);
			mThread.requestInterruption();
			mThread.quit();
		}
		else
			restOfCode();
	}
	void NetworkManager::updateDeviceList() {
		//clears available device list and updates it
		pcap_if_t* deviceList;
		std::array<char, PCAP_ERRBUF_SIZE> errbuf;
		clearDeviceList();

		if (pcap_findalldevs_ex(const_cast<char*>(PCAP_SRC_IF_STRING), nullptr,
			&deviceList, errbuf.data()) == -1)
			throw std::runtime_error(std::string("Error trying to get adapter list: ") + errbuf.data());

		//map the list to a vector
		for (pcap_if_t* device = deviceList; device; device = device->next)
			mAllDevices.push_back(device);
	}
	std::map<QString, QString> NetworkManager::getAliases() const {
		return mAliases; 
	}
	void NetworkManager::setAliases(const std::map<QString, QString>& map) {
		mAliases = map;
		emit aliasesChanged();
	}
	std::vector<pcap_if_t*>& NetworkManager::getDevices(){ 
		return mAllDevices; 
	}
	std::map<QString, QString>  NetworkManager::getIpDnsCache() const {
		return mCachedIp;
	}
	void  NetworkManager::setIpDnsCache(const 	std::map<QString, QString>& map) {
		mCachedIp = map;
	}
	void NetworkManager::installFilter(const QString& filter){
		if (mCurrentDevice == nullptr)
			return;
		u_int netMask;
		bpf_program fCode;
		//sets filters
		if (mCurrentDevice->addresses)
			netMask = ((sockaddr_in*)(mCurrentDevice->addresses->netmask))->sin_addr.S_un.S_addr;
		else
			netMask = 0xffffff;

		auto a = pcap_compile(mAddressHandle, &fCode, filter.toUtf8(), 0, netMask);
		auto b = pcap_setfilter(mAddressHandle, &fCode);
		if (a >= 0 && b >= 0)//on both success
			emit filterInstalled(filter);
	}
	void NetworkManager::openAdapter() {
		//opens a session on currentdevice and stores its address
		std::array<char, PCAP_ERRBUF_SIZE> errbuf;
		if (mAddressHandle = pcap_open(mCurrentDevice->name,
			65536,
			PCAP_OPENFLAG_PROMISCUOUS,
			1000,
			nullptr,
			errbuf.data()
		); mAddressHandle == nullptr)
			throw std::runtime_error("\n Unable to open adapter. " + std::string(mCurrentDevice->name) + " is not supported by Npcap.\
										Error provided:" + errbuf.data());

		emit toolbarMessage("Opened adapter : " + QString(mCurrentDevice->description), 1000);
	}
	QString NetworkManager::ipToAlias(const QString & name) {
		if (auto it = mAliases.find(name); it != mAliases.end())
			return it->second;
		return name;
	}
	QString NetworkManager::ipToDNS(const QString & ip, bool destination) {
		if (auto it = mCachedIp.find(ip); it != mCachedIp.end())//try not to call gatnameinfo 
			return it->second;

		//emit message, call to getnameInfo may take very long(maybe i should call it on another thread and time it out after 2 sec
		//to prevent some  edge cases when   it takes couple of seconds per translation)
		emit toolbarMessage(QString("Translating ") + (destination ? "destination" : "host") + QString(" address: ") + ip, 0);
		//translate ip to dns, cache the result and return it
		sockaddr_in saGNI;
		char hostname[NI_MAXHOST];
		char servInfo[NI_MAXSERV];
		saGNI.sin_family = AF_INET;

		QByteArray b = ip.toLocal8Bit();

		saGNI.sin_addr.s_addr = inet_addr(b.data());
		//saGNI.sin_port = htons(port);  
		if (getnameinfo((sockaddr*)& saGNI,
			sizeof(sockaddr),
			hostname,
			NI_MAXHOST, servInfo, NI_MAXSERV, NI_NUMERICSERV)){ 
			mCachedIp.insert({ ip, ip });
			return QString(ip);//on failure
		}
		mCachedIp.insert({ ip, hostname });

		return QString(hostname);
	}
	QString NetworkManager::getProtocol(const u_char & ch) {
		switch (ch) {
		case 4:
			return "IP";
		case 6:
			return "TCP";
		case 17:
			return "UDP";
		default:
			return "Other protocol, " + QString::number(ch, 16);
		}
	}
	void NetworkManager::clearDeviceList() {
		if (mAllDevices.size() > 0) {
			pcap_freealldevs(mAllDevices.front());
			mAllDevices.clear();
		}
	}
	void CaptureClass::startCapture(NetworkManager * data) {
		//1-Gets packet from current session
		//2-Formats it appropiatly and sends it out a qstringlist so tableview can map it to a table
		//3-Sends total size of packets sniffed during the last time interval, together with a timestamp
		pcap_pkthdr* header;
		const u_char* packetData;
		int result;
		time_t local_tv_sec;
		std::ostringstream ss;

		NetworkManager::IPHeader* ipHeader;
		NetworkManager::UDPHeader* udpHeader;
		u_int ipLen;

		QString sourceIp;
		QString destinationIp;
		std::vector<QList<QString>> vec;
		vec.reserve(64);
		int totalLength = 0;

		QTime startTime;
		startTime.start();

		QString deviceDescription = data->mCurrentDevice->description;//in case our mCurrentDevice gets deleted, we keep the value
																//(mCurrentDevice deletion doesnt affect any other part)

		while (!QThread::currentThread()->isInterruptionRequested()
			&& (result = pcap_next_ex(data->mAddressHandle, &header, &packetData)) >= 0) {//1-start the capture
			emit data->toolbarMessage("Listening to : " + deviceDescription);
			
			if (result == 0) {//timeout elapsed
				if (int elapsedTime = startTime.elapsed(); //send out vec of packets every x msec
					elapsedTime >= 200) {
					emit data->dataRead(vec, totalLength, QTime::currentTime());
					startTime.restart();
					vec.clear();
					totalLength = 0;
				}
				else
					continue;
			}
			QList<QString> output;

			//2-[0]first format packet timestamps
			local_tv_sec = header->ts.tv_sec;

			ss << std::put_time(std::localtime(&local_tv_sec), "%H:%M:%S") << '.' << header->ts.tv_usec;
			output << QString::fromStdString(ss.str());//[0]time 
			ss.str("");

			//2-[1]get sourceIp and store its dns name
			ipHeader = reinterpret_cast<NetworkManager::IPHeader*>(const_cast<u_char*>(packetData) + 14);//get position of ip header by skipping
																					  //14->length of internet header(MAC header)
																					  //$$care when connection is not enthernet	
			ipLen = (ipHeader->verIHL & 0b00001111u) * 4;//get position of udp header( length is the number of 4byte words)
			udpHeader = reinterpret_cast<NetworkManager::UDPHeader*>(reinterpret_cast<u_char*>(ipHeader) + ipLen);

			ss << static_cast<int>(ipHeader->sAddr.byte1) << '.'
				<< static_cast<int>(ipHeader->sAddr.byte2) << '.'
				<< static_cast<int>(ipHeader->sAddr.byte3) << '.'
				<< static_cast<int>(ipHeader->sAddr.byte4);

			sourceIp = QString::fromStdString(ss.str());

			output << data->ipToAlias(data->ipToDNS(sourceIp, 0)); //[1]sourceIp
			ss.str("");

			//2-[2]get destinationIp and store its dns name
			ss << static_cast<int>(ipHeader->dAddr.byte1) << '.'
				<< static_cast<int>(ipHeader->dAddr.byte2) << '.'
				<< static_cast<int>(ipHeader->dAddr.byte3) << '.'
				<< static_cast<int>(ipHeader->dAddr.byte4);

			destinationIp = QString::fromStdString(ss.str());

			output << data->ipToAlias(data->ipToDNS(destinationIp, 1));//[2]destinationIp
			ss.str("");
			//2-[3]type of protocol
			output << data->getProtocol(ipHeader->proto);//[3]details
			ss.str("");

			//3- add total length of packets
			totalLength += header->len - sizeof(pcap_file_header);

			vec.push_back(output);
			if (int elapsedTime = startTime.elapsed(); //send out vec of packets every x msec
				elapsedTime >= 200) {
				emit data->dataRead(vec, totalLength, QTime::currentTime());
				startTime.restart();
				vec.clear();
				totalLength = 0;
			}
		}
	}
}

