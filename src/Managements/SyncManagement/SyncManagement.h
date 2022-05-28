#pragma once

#include <QtSql>
#include <QString>

#include "Common/Utility.h"
#include "Common/UserSession.h"
#include "Managements/WebManagement.h"
#include "Managements/LocalManagement.h"
#include "Templates/CRUDManagement.h"
#include "Templates/QueryRespository.h"
#include "Templates/SynchronizerHandler.h"
#include "Models/Sync.h"
#include "SyncTable.h"

namespace Managers
{
	class SyncManagement : public Templates::CRUDLocalManagement<std::string, Sync::Entities>, public Templates::CRUDWebManagement<std::string, Sync::Entities>
	{
	public:
		SyncManagement(const QSqlDatabase &database, const std::shared_ptr<DB::IWebDbExecutor> &databaseWeb);
		~SyncManagement();

		Sync::Entities select(const std::string &login, DB::Status *status = nullptr) const override;
		std::vector<Sync::Entities> selectAll(DB::Status *status = nullptr) const override;
		bool insert(const Sync::Entities &localSync, DB::Status *status = nullptr) override;
		bool remove(const Sync::Entities &sync, DB::Status *status = nullptr) override;
		bool removeAll(DB::Status *status = nullptr) override;
		bool update(const Sync::Entities &localSync, DB::Status *status = nullptr) override;

		Sync::Entities selectWeb(const std::string &login, DB::Status *status = nullptr) const override;
		std::vector<Sync::Entities> selectAllWeb(DB::Status *status = nullptr) const override;
		bool insertWeb(const Sync::Entities &webSync, DB::Status *status = nullptr) override;
		bool removeWeb(const Sync::Entities &webSync, DB::Status *status = nullptr) override;
		bool removeAllWeb(DB::Status *status = nullptr) override;
		bool updateWeb(const Sync::Entities &webSync, DB::Status *status = nullptr) override;

	private:
		DB::LocalManagement m_localManager;
		WebManagement m_webManager;

		static Sync::Entities fetchFromRecord(const QSqlRecord &record);
		static Sync::Entities fetchFromRecordWeb(const QJsonObject &records);
		static std::string fetchToJsonWeb(const Sync::Entities &sync);
	};
}
