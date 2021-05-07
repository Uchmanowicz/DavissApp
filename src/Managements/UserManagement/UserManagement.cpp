#include "UserManagement.h"

UserManagement::UserManagement(const QSqlDatabase &database, const std::shared_ptr<WebDatabaseManager> &databaseWeb) //, const std::shared_ptr<Synchronizer> &synchronizer_)
	: m_localManager(database), m_webManager(databaseWeb) //, m_synchronizer(synchronizer_)
{
}

UserManagement::~UserManagement()
{
}

User UserManagement::select(const std::string &login, DBStatus::StatusType *status) const
{
	Query query;
	query.query = QString("SELECT * FROM %1 WHERE %2 = '%3';")
					  .arg(UserTable::TABLE_NAME, UserTable::LOGIN, login.c_str())
					  .toStdString();

	auto reply = m_localManager.getRecord(query, status);

	if(!reply.isEmpty()) {
		return fetchUserFromRecord(reply);
	}

	return User();
}

std::vector<User> UserManagement::selectAll(DBStatus::StatusType *status) const
{
	Query query;
	query.query = QString("SELECT * FROM %1;")
					  .arg(UserTable::TABLE_NAME)
					  .toStdString();

	auto reply = m_localManager.getRecords(query, status);

	std::vector<User> users;
	for(const auto &user: reply) {
		users.push_back(fetchUserFromRecord(user));
	}

	return users;
}

bool UserManagement::insert(const User &user, DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("INSERT INTO %1(%2, %3, %4, %5, %6, %7, %8, %9) VALUES('%10', '%11', '%12', '%13', '%14', '%15', '%16', '%17');")
					  .arg(UserTable::TABLE_NAME, UserTable::LOGIN, UserTable::PASSWORD, UserTable::NAME, UserTable::ROLE, UserTable::IS_BLOCKED, UserTable::IsAlwaysLogged, UserTable::MODULES, UserTable::AVATAR)
					  .arg(user.login, user.password, user.name, QString::number(user.userRole), QString::number(user.isBlocked), QString::number(user.isAlwaysLogged), QString(modulesToJson(user.modulesEnabled).c_str()), user.avatar)
					  .toStdString();

	return m_localManager.execQuery(query, status);
}

bool UserManagement::remove(const User &user, DBStatus::StatusType *status)
{
	if(user.login == "Guest") {
		return true;
	}

	Query query;
	query.query = QString("DELETE FROM %1 WHERE %2 = '%3';")
					  .arg(UserTable::TABLE_NAME, UserTable::LOGIN, user.login)
					  .toStdString();

	return m_localManager.execQuery(query, status);
}

bool UserManagement::removeAll(DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("DELETE FROM %1 WHERE %2 = '%3';")
					  .arg(UserTable::TABLE_NAME, UserTable::LOGIN, UserSession::getInstance().getUser().login)
					  .toStdString();

	return m_localManager.execQuery(query, status);
}

bool UserManagement::update(const User &user, DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("UPDATE %1 SET %2='%3', %4='%5', %6='%7', %8='%9', %10='%11', %12='%13', %14='%15' WHERE %16 = '%17';")
					  .arg(UserTable::TABLE_NAME, UserTable::PASSWORD, user.password, UserTable::NAME, user.name, UserTable::ROLE, QString::number(user.userRole))
					  .arg(UserTable::MODULES, QString(modulesToJson(user.modulesEnabled).c_str()), UserTable::AVATAR, user.avatar, UserTable::IS_BLOCKED, QString::number(user.isBlocked), UserTable::IsAlwaysLogged, QString::number(user.isAlwaysLogged), UserTable::LOGIN, user.login)
					  .toStdString();

	return m_localManager.execQuery(query, status);
}

User UserManagement::selectWeb(const std::string &login, DBStatus::StatusType *status) const
{
	Query query;
	query.query = QString("/%1/%2").arg(UserTable::TABLE_NAME, login.c_str()).toStdString();

	auto reply = m_webManager.getRecord(query, status);

	if(!reply.empty()) {
		return fetchUserFromRecordWeb(reply);
	}

	return User();
}

std::vector<User> UserManagement::selectAllWeb(DBStatus::StatusType *status) const
{
	Query query;
	query.query = QString("/%1?filter=%2,eq,%3").arg(UserTable::TABLE_NAME, UserTable::LOGIN, UserSession::getInstance().getUser().login).toStdString();

	auto reply = m_webManager.getRecords(query, status);

	std::vector<User> users;
	for(auto const &userObj: reply) {
		users.push_back(fetchUserFromRecordWeb(userObj));
	}

	return users;
}

bool UserManagement::insertWeb(const User &user, DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("/%1").arg(UserTable::TABLE_NAME).toStdString();
	query.body = fetchUserToJsonWeb(user);

	return m_webManager.execQuery(query, status);
}

bool UserManagement::removeWeb(const User &user, DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("/%1/%2").arg(UserTable::TABLE_NAME, user.login).toStdString();

	return m_webManager.execQuery(query, status);
}

bool UserManagement::removeAllWeb(DBStatus::StatusType *status)
{
	return 0;
}

bool UserManagement::updateWeb(const User &user, DBStatus::StatusType *status)
{
	auto qrTxt = QString("/%1/%2").arg(UserTable::TABLE_NAME, user.login).toStdString();
	Query query(qrTxt, fetchUserToJsonWeb(user), Query::UPDATE);

	return m_webManager.execQuery(query, status);
}

User UserManagement::fetchUserFromRecord(const QSqlRecord &record)
{
	User user;
	user.login = record.field(UserTable::LOGIN).value().toString();
	user.password = record.field(UserTable::PASSWORD).value().toString();
	user.name = record.field(UserTable::NAME).value().toString();
	user.userRole = (User::UserRole)record.field(UserTable::ROLE).value().toInt();
	user.avatar = record.field(UserTable::AVATAR).value().toString();
	user.isBlocked = record.field(UserTable::IS_BLOCKED).value().toInt();
	user.isAlwaysLogged = record.field(UserTable::IsAlwaysLogged).value().toInt();
	user.modulesEnabled = modulesFromJson(record.field(UserTable::MODULES).value().toString());

	return user;
}

User UserManagement::fetchUserFromRecordWeb(const QJsonObject &records)
{
	User user;
	user.login = records[UserTable::LOGIN].toString();
	user.password = records[UserTable::PASSWORD].toString();
	user.name = records[UserTable::NAME].toString();
	user.userRole = static_cast<User::UserRole>(records[UserTable::ROLE].toInt());
	user.isBlocked = records[UserTable::IS_BLOCKED].toBool();
	user.avatar = records[UserTable::AVATAR].toString().replace(" ", "+");
	user.modulesEnabled = modulesFromJson(records[UserTable::MODULES].toString());

	return user;
}

std::string UserManagement::fetchUserToJsonWeb(const User &user)
{
	QJsonObject obj;
	obj.insert(UserTable::PASSWORD, user.password);
	obj.insert(UserTable::NAME, user.name);
	obj.insert(UserTable::ROLE, user.userRole);
	obj.insert(UserTable::IS_BLOCKED, user.isBlocked ? "1" : "0");
	obj.insert(UserTable::AVATAR, user.avatar);
	obj.insert(UserTable::MODULES, QString(modulesToJson(user.modulesEnabled).c_str()));
	QJsonDocument doc(obj);

	return doc.toJson(QJsonDocument::Compact).toStdString();
}

QMap<QString, bool> UserManagement::modulesFromJson(const QString &jsonString)
{
	QMap<QString, bool> modulesMap;

	auto obj = QJsonDocument::fromJson(jsonString.toUtf8());
	auto arr = obj["Modules"].toArray();
	for(const auto &moduleVal: arr) {
		QString id = moduleVal.toObject()["id"].toString();
		bool isEnabled = moduleVal.toObject()["isEnabled"].toBool(false);
		modulesMap[id] = isEnabled;
	}

	return modulesMap;
}

std::string UserManagement::modulesToJson(const QMap<QString, bool> &modulesMap)
{
	QJsonObject obj;
	QJsonArray arr;
	for(auto it = modulesMap.begin(); it != modulesMap.end(); ++it) {
		QJsonObject objModule;
		objModule.insert("id", it.key());
		objModule.insert("isEnabled", it.value());
		arr << objModule;
	}
	obj.insert("Modules", arr);
	QJsonDocument doc(arr);
	return ""; // doc.toJson(QJsonDocument::Compact).toStdString();
}
