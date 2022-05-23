#pragma once

#include <QObject>
#include <QVariantMap>
#include <QString>
#include <QUuid>

namespace Depot
{
	typedef QString DataName;

	class Item
	{
		Q_GADGET
	public:
		struct Parameter
		{
			QString name = "";
			QString value = "";
			QString unit = "";

			Parameter() { }
			Parameter(const QString &_name, const QString &_value, const QString &_unit)
				: name(_name), value(_value), unit(_unit)
			{ }

			QString toString() const
			{
				return QString(name + value + unit);
			}

			bool operator==(const Parameter &other) const = default;
		};

		Q_PROPERTY(QString ui_login MEMBER login);
		Q_PROPERTY(QString ui_category MEMBER category);
		Q_PROPERTY(long long ui_amount MEMBER amount);
		Q_PROPERTY(QString ui_unit MEMBER unit);
		Q_PROPERTY(QString ui_localization MEMBER localization);
		Q_PROPERTY(QMap<DataName, Parameter> ui_parameters MEMBER parameters);

		Item() { }
		Item(const QString &_login, const QString &_category, const long long &_amount, const QString &_unit, const QString &_localization, const QMap<DataName, Parameter> &_parameters)
			: login(_login), category(_category), amount(_amount), unit(_unit), localization(_localization), parameters(_parameters)
		{
			id = getID();
		}

		QString login = "";
		QString id = "";
		QString category = "";
		long long amount = 0L;
		QString unit = "";
		QString localization = "";
		QMap<DataName, Parameter> parameters;

		QString getID() const
		{
			return QUuid::createUuidV3("DepotItem", QString(login + category + QString::number(amount) + unit + localization)).toString();
		}

		bool operator==(const Item &other) const
		{
			return true;
		}
	};
}
Q_DECLARE_METATYPE(Depot::Item)
Q_DECLARE_METATYPE(Depot::Item::Parameter)
