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
		static QJsonObject toJson(const Parameter &data);
		static QJsonArray toJson(const QMap<DataName, Parameter> &dataMap);
		static QString toJsonString(const QMap<DataName, Parameter> &dataMap);
		static Parameter fromJson(const QJsonObject &dataJson);
		static QMap<DataName, Parameter> fromJson(const QJsonArray &dataJson);
		static Parameter fromJsonString(const QString &dataString);

	private:
		static bool validateJson(const QJsonObject &json);
	};
}
