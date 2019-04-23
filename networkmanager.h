#pragma once
#include <QObject>
#include <WinSock2.h>
#include <iomanip>
#include <array>
#include <string>
#include <QTimer>
#include <sstream>
#include <QtConcurrent/QtConcurrent>
#include <QThread>
#include <QCoreApplication>
#include <QProcess>
#include <map>
#include <QHostInfo>
#include <QFile>
#ifndef HAVE_REMOTE
#define HAVE_REMOTE
#endif
#include "pcap.h"
namespace sta {
    class NetworkManager : public QObject{
        Q_OBJECT
     public:
        NetworkManager();
        ~NetworkManager(); 
	 public slots:
		void selectDevice(int);
	    void updateDeviceList();
		std::map<QString, QString> getAliases() const;
		void setAliases(const std::map<QString, QString>&);
		std::vector<pcap_if_t*>& getDevices();
		std::map<QString, QString> getIpDnsCache() const;
		void setIpDnsCache(const std::map<QString, QString>&);
		void installFilter(const QString&);
	 signals:
		 void dataRead(const std::vector<QList<QString>>&, int, QTime);//emits data read from adapter
		 void toolbarMessage(QString, int = 0);
		 void newAdapterClearData();//when a new adapter is opened clear data in table and chart
		 void aliasesChanged();
		 void lookupDone(const QString&);
		 void filterInstalled(const QString&);
     private: //helper classess
		
		 struct IPAddress {
			 u_char byte1;
			 u_char byte2;
			 u_char byte3;
			 u_char byte4;
		 };
		 struct IPHeader {
			 u_char verIHL;			// Version (4 bits) + Internet header length (4 bits)
			 u_char TOS;			    // Type of service
			 u_short tLen;			// Total length
			 u_short identification; // Identification
			 u_short flagsFO;		// Flags (3 bits) + Fragment offset (13 bits)
			 u_char TTL;				// Time to live
			 u_char proto;			// Protocol
			 u_short crc;			// Header checksum
			 IPAddress sAddr;		// Source address
			 IPAddress dAddr;	    // Destination address
			 u_int opPad;			// Option + Padding
		 };
		 struct UDPHeader {
			 u_short sPort; //Source port
			 u_short dPort; //Destination port
			 u_short len;   //Datagram length
			 u_short crc;   //Checksum
		 };
		 struct TCPHeader {
			 u_short sPort; //Source port
			 u_short dPort; //Destination port
			 u_int seqnum; // Sequence Number 
			 u_int acknum; // Acknowledgement number 
			 u_char th_off; // Header length 
			 u_char flags; // packet flags 
			 u_short win; // Window size 
			 u_short crc; // Header Checksum 
			 u_short urgptr; // Urgent pointer
		 };
		 friend class CaptureClass;//qobject doesnt support nested classes...
	private://FUNCTIONS
		 void openAdapter();
		QString ipToAlias(const QString&);//converts a name into another
		QString ipToDNS(const QString&, bool);//converts ip to dns
		QString getProtocol(const u_char&);//maps from number to protocol name string
		void clearDeviceList();//deletes device list instances and clears devicelist vector

	private://DATA MEMBERS
		std::vector<pcap_if_t*> mAllDevices;//list of devices mapped to a vector
		pcap_if_t* mCurrentDevice;//device we currently listening on
		pcap_t* mAddressHandle;//handle to opened session
		std::map<QString, QString> mAliases;//aliased names for common dns names (such as MyDesktop)
		std::map<QString, QString> mCachedIp;//caches ip to dns mappings to reduce mapping calls
		CaptureClass* mPacketCapture = nullptr;
		QThread mThread;
    };

	class CaptureClass : public QObject {
		Q_OBJECT
	public:
		CaptureClass(QObject* parent = nullptr) : QObject{ parent} {}
	public slots:
		void startCapture(NetworkManager*);
	private:
		friend class NetworkManager;
	};
}
