#pragma once

#include <QObject>
#include <QString>

/// @brief
///
/// Class is template for all modules (main features)
class Module
{   
public:
	Q_GADGET

public:
	Q_PROPERTY(QString ui_id MEMBER id);
	Q_PROPERTY(QString ui_name MEMBER name);
	Q_PROPERTY(QString ui_icon MEMBER icon);
	Q_PROPERTY(QString ui_moduleIcon MEMBER moduleIcon);
	Q_PROPERTY(bool ui_isEnabled MEMBER isEnabled);

public:
	Module() {}

	/// @brief
	///
	/// Default constructor to create Module
	/// @param id_ Specific id for module
	/// @param name_ Module name which is displayed
	/// @param isEnabled_ State of enabled (visible) module
	Module(const QString &id_, const QString &name_, const bool &isEnabled_ = false)
		: id(id_), name(name_), isEnabled(isEnabled_)
	{
		icon = "qrc:///ui/Images/Modules/" + id + "/" + "Icon";
		moduleIcon = "qrc:///ui/Images/Modules/" + id + "/" + "ModuleIcon";
	}

	QString id = "";
	QString name = "";
	QString icon = "";
	QString moduleIcon = "";
	bool isEnabled = false;

	bool operator==(const Module &other) const
	{
		return id == other.id
				&& name == other.name
				&& icon == other.icon
				&& moduleIcon == other.moduleIcon
				&& isEnabled == other.isEnabled;
	}

	bool operator!=(const Module &other) const
	{
		return id == other.id
				|| name == other.name
				|| icon == other.icon
				|| moduleIcon == other.moduleIcon
				|| isEnabled == other.isEnabled;
	}
};
Q_DECLARE_METATYPE(Module)

