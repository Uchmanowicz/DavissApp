#include "ParameterParser.h"

namespace Depot
{
	QJsonObject ParameterParser::toJson(const Item::Parameter &data)
	{
		return QJsonObject {{KEY_NAME, data.name},
							{KEY_VALUE, data.value},
							{KEY_UNIT, data.unit}};
	}

	QJsonArray ParameterParser::toJson(const QMap<DataName, Item::Parameter> &dataMap)
	{
		QJsonArray arr;
		for(const auto &item: dataMap) {
			arr << toJson(item);
		}
		return arr;
	}

	QString ParameterParser::toJsonString(const QMap<DataName, Item::Parameter> &dataMap)
	{
		QJsonDocument doc;
		doc.setArray(toJson(dataMap));
		return doc.toJson();
	}

	Item::Parameter ParameterParser::fromJson(const QJsonObject &dataJson)
	{
		if(!validateJson(dataJson)) {
		}

		return Item::Parameter(dataJson[KEY_NAME].toString(), dataJson[KEY_VALUE].toString(), dataJson[KEY_UNIT].toString());
	}

	QMap<DataName, Item::Parameter> ParameterParser::fromJson(const QJsonArray &dataJson)
	{
		QMap<DataName, Item::Parameter> dataMap;
		for(const auto &dataVal: dataJson) {
			const auto data = fromJson(dataVal.toObject());
			dataMap.insert(data.name, data);
		}
		return dataMap;
	}

	Item::Parameter ParameterParser::fromJsonString(const QString &dataString)
	{
		QJsonDocument doc = QJsonDocument::fromJson(dataString.toUtf8());
		if(doc.isObject()) {
			return fromJson(doc.object());
		}

		return {};
	}

	bool ParameterParser::validateJson(const QJsonObject &json)
	{
		return json.contains(KEY_NAME)
			   && json.contains(KEY_VALUE)
			   && json.contains(KEY_UNIT);
	}
}
