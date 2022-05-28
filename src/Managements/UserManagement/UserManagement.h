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

namespace Managers
{
	class UserManagement : public Templates::CRUDLocalManagement<std::string, Person::User>, public Templates::CRUDWebManagement<std::string, Person::User>
	{
	public:
		UserManagement(const QSqlDatabase &database, const std::shared_ptr<DB::IWebDbExecutor> &databaseWeb); //, const std::shared_ptr<Synchronizer> &synchronizer_);
		~UserManagement();

		Person::User select(const std::string &login, DB::Status *status = nullptr) const override;
		std::vector<Person::User> selectAll(DB::Status *status = nullptr) const override;
		bool insert(const Person::User &user, DB::Status *status = nullptr) override;
		bool remove(const Person::User &user, DB::Status *status = nullptr) override;
		bool removeAll(DB::Status *status = nullptr) override;
		bool update(const Person::User &user, DB::Status *status = nullptr) override;

		Person::User selectWeb(const std::string &login, DB::Status *status = nullptr) const override;
		std::vector<Person::User> selectAllWeb(DB::Status *status = nullptr) const override;
		bool insertWeb(const Person::User &user, DB::Status *status = nullptr) override;
		bool removeWeb(const Person::User &user, DB::Status *status = nullptr) override;
		bool removeAllWeb(DB::Status *status = nullptr) override;
		bool updateWeb(const Person::User &user, DB::Status *status = nullptr) override;

	private:
		DB::LocalManagement m_localManager;
		WebManagement m_webManager;
		//	std::shared_ptr<Synchronizer> m_synchronizer;

		std::string m_lastError;
		static Person::User fetchUserFromRecord(const QSqlRecord &record);
		static Person::User fetchUserFromRecordWeb(const QJsonObject &records);
		static std::string fetchUserToJsonWeb(const Person::User &user);

		static QMap<QString, bool> modulesFromJson(const QString &jsonString);
		static std::string modulesToJson(const QMap<QString, bool> &modulesMap);
	};
}
