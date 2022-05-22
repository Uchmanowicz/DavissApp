#pragma once

#include <QObject>
#include <QString>
#include <QUuid>
#include "Module.h"

class DepotItem
{
	Q_GADGET

public:
	Q_PROPERTY(QString ui_login MEMBER login);
	Q_PROPERTY(QString ui_category MEMBER category);
	Q_PROPERTY(long long ui_amount MEMBER amount);
	Q_PROPERTY(QString ui_unit MEMBER unit);
	Q_PROPERTY(QString ui_localization MEMBER localization);
	Q_PROPERTY(QString ui_data MEMBER data);

	DepotItem() { }
	DepotItem(const QString &_login, const QString &_category, const long long &_amount, const QString &_unit, const QString &_localization, const QString &_data)
		: login(_login), category(_category), amount(_amount), unit(_unit), localization(_localization), data(_data)
	{
		id = getID();
	}

	QString login = "";
	QString id = "";
	QString category = "";
	long long amount = 0L;
	QString unit = "";
	QString localization = "";
	QString data = "";

	QString getID() const
	{
		return QUuid::createUuidV3("DepotItem", QString(login + category + QString::number(amount) + unit + localization + data)).toString();
	}

	bool operator==(const DepotItem &other) const = default;
};
Q_DECLARE_METATYPE(DepotItem)
