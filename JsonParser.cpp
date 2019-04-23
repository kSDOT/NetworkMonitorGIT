#include "JsonParser.h"
namespace sta{

qint64 JsonParser::writeMapToFile(const std::map<QString, QString>& map, QFile& fileJ,
	std::function<QByteArray(const std::map<QString, QString>&, const QByteArray&)> func) {
	
	quint64 bytesWritten;
	if (!fileJ.open(QFile::ReadOnly | QFile::Text))
		return 0.0;

	QByteArray result{ func(map, fileJ.readAll()) };
	fileJ.close();

	if (!fileJ.open(QFile::WriteOnly | QFile::Text))
		return 0.0;
	
	bytesWritten = fileJ.write(result);
	fileJ.close();
	return bytesWritten;
}

QByteArray JsonParser::editItem(const std::map<QString, QString>& map, const QByteArray& ba, const QString& type){
	QJsonDocument docComplete = QJsonDocument::fromJson(ba);

	QJsonObject object = docComplete.object();
	object.remove(type);
	object.insert(type, toVariant(map).toJsonValue());
	docComplete = QJsonDocument::fromVariant(object.toVariantMap());

	return docComplete.toJson();
}

QVariant JsonParser::toVariant(const std::map<QString, QString> & map) {
	QVariantMap  variantMap;
	for (const auto& pair : map)
		variantMap[pair.first] = pair.second;

	return variantMap;
}

std::map<QString, QString> JsonParser::readMapFromFile(QFile & filej, std::function<std::map<QString, QString>(const QByteArray&)> func) {

	if (!filej.open(QFile::ReadOnly | QFile::Text))
		return std::map<QString, QString>();

	std::map<QString, QString> map{ func(filej.readAll()) };
	filej.close();

	return map;
}

std::map<QString, QString> JsonParser::readDocument(const QByteArray& array, const QString& type) {
	QJsonDocument doc = QJsonDocument::fromJson(array);
	if (doc.isEmpty() || !doc.isObject()) return std::map<QString, QString>();
	return readMap(doc.object(), type);
}

std::map<QString, QString> JsonParser::readMap(const QJsonObject& object, const QString& mapObjectName) {
	QJsonObject mapToRead = object[mapObjectName].toObject();
	std::map<QString, QString> map;
	for (const auto& key : mapToRead.keys())
		map[key] = mapToRead.value(key).toString();
	return map;
}
}