#pragma once
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariant>
#include <map>
#include <QFIle>
#include <functional>
#include <QTextStream>
//JSON file format:
/*
{
"settings": {(Map<settingNameString, settingValueString>)},
"aliases": {(Map<originalNameString, aliasString>)},
"ipCache": {(Map<ipString, dnsString>)}
}
*/
namespace sta {
	class JsonParser
	{
	public:
		JsonParser() = delete;
		~JsonParser() = delete;
		//aliases

		static qint64 writeAliasesToFile(const std::map<QString, QString>& map, QFile& fileJ) { return writeMapToFile(map, fileJ, writeAliases); }
		static QByteArray writeAliases(const std::map<QString, QString>& map, const QByteArray& ba) { return editItem(map, ba, "aliases"); }

		static std::map<QString, QString> readAliasesFromFile(QFile& fileJ) {
			return readMapFromFile(fileJ,
				static_cast<std::map<QString, QString>(*)(const QByteArray&)>(readAliases));
		}
		static std::map<QString, QString> readAliases(const QByteArray& ba) { return readDocument(ba, "aliases"); }

		//settings	
		static qint64 writeSettingsToFile(const std::map<QString, QString>& map, QFile& fileJ) { return writeMapToFile(map, fileJ, writeSettings); }
		static QByteArray writeSettings(const std::map<QString, QString>& map, const QByteArray& ba) { return editItem(map, ba, "settings"); }

		static std::map<QString, QString> readSettingsFromFile(QFile& fileJ) { return readMapFromFile(fileJ, static_cast<std::map<QString, QString>(*)(const QByteArray&)>(readSettings)); }
		static std::map<QString, QString> readSettings(const QByteArray& ba) { return readDocument(ba, "settings"); }

		//ip cache
		static qint64 writeIpCacheToFile(const std::map<QString, QString>& map, QFile& fileJ) { return writeMapToFile(map, fileJ, writeIpCache); }
		static QByteArray writeIpCache(const std::map<QString, QString>& map, const QByteArray& ba) { return editItem(map, ba, "ipCache"); }

		static std::map<QString, QString> readIpCacheFromFile(QFile& fileJ) { return readMapFromFile(fileJ, static_cast<std::map<QString, QString>(*)(const QByteArray&)>(readIpCache)); }
		static std::map<QString, QString> readIpCache(const QByteArray& ba) { return readDocument(ba, "ipCache"); }

	private:
		//common write funcionality
		static QVariant toVariant(const std::map<QString, QString>&);
		static qint64 JsonParser::writeMapToFile(const std::map<QString, QString>&, QFile&,
			std::function<QByteArray(const std::map<QString, QString>&, const QByteArray&)>);
		static QByteArray editItem(const std::map<QString, QString>&, const QByteArray&, const QString&);

		//common read funcionality
		static std::map<QString, QString> JsonParser::readMapFromFile(QFile&, std::function<std::map<QString, QString>(const QByteArray&)> func);
		static std::map<QString, QString> readMap(const QJsonObject&, const QString&);
		static std::map<QString, QString> readDocument(const QByteArray&, const QString&);
	};

}