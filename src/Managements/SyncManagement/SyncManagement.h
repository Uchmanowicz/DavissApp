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

class SyncManagement : public CRUDLocalManagement<std::string, Sync>, public CRUDWebManagement<std::string, Sync>
{
public:
	SyncManagement(const QSqlDatabase &database, const std::shared_ptr<WebDatabaseManager> &databaseWeb);
	~SyncManagement();

	Sync select(const std::string &login, DBStatus::StatusType *status = nullptr) const override;
	std::vector<Sync> selectAll(DBStatus::StatusType *status = nullptr) const override;
	bool insert(const Sync &localSync, DBStatus::StatusType *status = nullptr) override;
	bool remove(const Sync &sync, DBStatus::StatusType *status = nullptr) override;
	bool removeAll(DBStatus::StatusType *status = nullptr) override;
	bool update(const Sync &localSync, DBStatus::StatusType *status = nullptr) override;

	Sync selectWeb(const std::string &login, DBStatus::StatusType *status = nullptr) const override;
	std::vector<Sync> selectAllWeb(DBStatus::StatusType *status = nullptr) const override;
	bool insertWeb(const Sync &webSync, DBStatus::StatusType *status = nullptr) override;
	bool removeWeb(const Sync &webSync, DBStatus::StatusType *status = nullptr) override;
	bool removeAllWeb(DBStatus::StatusType *status = nullptr) override;
	bool updateWeb(const Sync &webSync, DBStatus::StatusType *status = nullptr) override;

private:
	LocalManagement m_localManager;
	WebManagement m_webManager;

	static Sync fetchFromRecord(const QSqlRecord &record);
	static Sync fetchFromRecordWeb(const QJsonObject &records);
	static std::string fetchToJsonWeb(const Sync &sync);
};
