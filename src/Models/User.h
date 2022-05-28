#pragma once

#include <QObject>
#include <QString>
#include <QMap>
#include "Module.h"

namespace Person
{
	class User
	{
	public:
		Q_GADGET

	public:
		enum UserRole
		{
			Standard = 0,
			Guest,
			Children,
			Admin
		};
		Q_ENUM(UserRole);

		Q_PROPERTY(QString ui_login MEMBER login);
		Q_PROPERTY(QString ui_password MEMBER password);
		Q_PROPERTY(QString ui_name MEMBER name);
		Q_PROPERTY(UserRole ui_userRole MEMBER userRole);
		Q_PROPERTY(QString ui_userRoleDisplay READ getUserRole);
		Q_PROPERTY(bool ui_isBlocked MEMBER isBlocked);
		Q_PROPERTY(QString ui_avatar MEMBER avatar);
		Q_PROPERTY(bool ui_isAlwaysLogged MEMBER isAlwaysLogged);
		Q_PROPERTY(bool ui_isGuest READ isGuest);

	public:
		User() = default;
		User(const QString &login_, const QString &password_, const QString &name_, const UserRole &role = Standard, const bool &isBlocked_ = false, const QString &avatar_ = "", const bool &isAlwaysLogged_ = 0)
			: login(login_), password(password_), name(name_), userRole(role), isBlocked(isBlocked_), avatar(avatar_), isAlwaysLogged(isAlwaysLogged_) { }

		QString login = "";
		QString password = "";
		QString name = "";
		UserRole userRole = Guest;
		bool isBlocked = false;
		QString avatar = "";
		QMap<QString, bool> modulesEnabled;

		bool isAlwaysLogged = false;

		QString getUserRole()
		{
			QString res = "unknowkn";

			switch(userRole) {
			case Standard:
				res = "Standard User";
				break;
			case Guest:
				res = "Guest";
				break;
			case Children:
				res = "Child";
				break;
			case Admin:
				res = "Admin";
				break;
			}

			return res;
		}

		bool isGuest()
		{
			return userRole == UserRole::Guest;
		}

		bool isLogged()
		{
			return login.size() && userRole != UserRole::Guest;
		}

		bool operator==(const User &other) const
		{
			return login == other.login
				   && password == other.password
				   && name == other.name
				   && userRole == other.userRole
				   && isBlocked == other.isBlocked
				   && avatar == other.avatar
				   && isAlwaysLogged == other.isAlwaysLogged;
		}

		bool operator!=(const User &other) const
		{
			return login != other.login
				   || password != other.password
				   || name != other.name
				   || userRole != other.userRole
				   || isBlocked != other.isBlocked
				   || avatar != other.avatar
				   || isAlwaysLogged != other.isAlwaysLogged;
		}
	};
}
Q_DECLARE_METATYPE(Person::User)
Q_DECLARE_METATYPE(Person::User::UserRole)
