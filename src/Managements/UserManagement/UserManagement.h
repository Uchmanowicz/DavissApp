#pragma once

#include <QtSql>
#include <QString>

#include "Common/Utility.h"
#include "Common/UserSession.h"
#include "Managements/WebManagement.h"
#include "Managements/LocalManagement.h"
#include "Templates/CRUDManagement.h"
#include "Templates/QueryRespository.h"
//#include "Services/Synchronizer.h"
#include "Models/User.h"
#include "UserTable.h"

class UserManagement : public CRUDLocalManagement<std::string, User>, public CRUDWebManagement<std::string, User>
{
public:
	UserManagement(const QSqlDatabase &database, const std::shared_ptr<WebDatabaseManager> &databaseWeb); //, const std::shared_ptr<Synchronizer> &synchronizer_);
	~UserManagement();

	User select(const std::string &login, DBStatus::StatusType *status = nullptr) const override;
	std::vector<User> selectAll(DBStatus::StatusType *status = nullptr) const override;
	bool insert(const User &user, DBStatus::StatusType *status = nullptr) override;
	bool remove(const User &user, DBStatus::StatusType *status = nullptr) override;
	bool removeAll(DBStatus::StatusType *status = nullptr) override;
	bool update(const User &user, DBStatus::StatusType *status = nullptr) override;

	User selectWeb(const std::string &login, DBStatus::StatusType *status = nullptr) const override;
	std::vector<User> selectAllWeb(DBStatus::StatusType *status = nullptr) const override;
	bool insertWeb(const User &user, DBStatus::StatusType *status = nullptr) override;
	bool removeWeb(const User &user, DBStatus::StatusType *status = nullptr) override;
	bool removeAllWeb(DBStatus::StatusType *status = nullptr) override;
	bool updateWeb(const User &user, DBStatus::StatusType *status = nullptr) override;

private:
	LocalManagement m_localManager;
	WebManagement m_webManager;
	//	std::shared_ptr<Synchronizer> m_synchronizer;

	std::string m_lastError;
	static User fetchUserFromRecord(const QSqlRecord &record);
	static User fetchUserFromRecordWeb(const QJsonObject &records);
	static std::string fetchUserToJsonWeb(const User &user);

	static QMap<QString, bool> modulesFromJson(const QString &jsonString);
	static std::string modulesToJson(const QMap<QString, bool> &modulesMap);
};
