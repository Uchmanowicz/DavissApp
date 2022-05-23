#pragma once

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "Models/Depot/Item.h"

namespace Depot
{
	class ParameterParser
	{
		static constexpr auto KEY_NAME = "name";
		static constexpr auto KEY_VALUE = "value";
		static constexpr auto KEY_UNIT = "unit";

	public:
		static QJsonObject toJson(const Item::Parameter &data);
		static QJsonArray toJson(const QMap<DataName, Item::Parameter> &dataMap);
		static QString toJsonString(const QMap<DataName, Item::Parameter> &dataMap);
		static Item::Parameter fromJson(const QJsonObject &dataJson);
		static QMap<DataName, Item::Parameter> fromJson(const QJsonArray &dataJson);
		static Item::Parameter fromJsonString(const QString &dataString);

	private:
		static bool validateJson(const QJsonObject &json);
	};
}
