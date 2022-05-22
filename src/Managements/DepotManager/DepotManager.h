#pragma once

#include <QtSql>

#include "Common/Utility.h"
#include "Common/UserSession.h"
#include "Managements/WebManagement.h"
#include "Managements/LocalManagement.h"
#include "Templates/CRUDManagement.h"
#include "Templates/QueryRespository.h"
//#include "Services/Synchronizer.h"
#include "Models/DepotItem.h"
#include "DepotTable.h"

class DepotManager : public CRUDLocalManagement<std::string, DepotItem>, public CRUDWebManagement<std::string, DepotItem>
{
public:
	DepotManager(const QSqlDatabase &database, const std::shared_ptr<WebDatabaseManager> &databaseWeb); //, const std::shared_ptr<Synchronizer> &synchronizer_);
	~DepotManager();

	DepotItem select(const std::string &login, DBStatus::StatusType *status = nullptr) const override;
	std::vector<DepotItem> selectAll(DBStatus::StatusType *status = nullptr) const override;
	bool insert(const DepotItem &depotItem, DBStatus::StatusType *status = nullptr) override;
	bool remove(const DepotItem &depotItem, DBStatus::StatusType *status = nullptr) override;
	bool removeAll(DBStatus::StatusType *status = nullptr) override;
	bool update(const DepotItem &depotItem, DBStatus::StatusType *status = nullptr) override;

	DepotItem selectWeb(const std::string &login, DBStatus::StatusType *status = nullptr) const override;
	std::vector<DepotItem> selectAllWeb(DBStatus::StatusType *status = nullptr) const override;
	bool insertWeb(const DepotItem &depotItem, DBStatus::StatusType *status = nullptr) override;
	bool removeWeb(const DepotItem &depotItem, DBStatus::StatusType *status = nullptr) override;
	bool removeAllWeb(DBStatus::StatusType *status = nullptr) override;
	bool updateWeb(const DepotItem &depotItem, DBStatus::StatusType *status = nullptr) override;

private:
	LocalManagement m_localManager;
	WebManagement m_webManager;
	//	std::shared_ptr<Synchronizer> m_synchronizer;

	std::string m_lastError;
	static DepotItem fetchFromRecord(const QSqlRecord &record);
	static DepotItem fetchFromRecordWeb(const QJsonObject &records);
	static std::string fetchToJsonWeb(const DepotItem &depotItem);

	//	static QMap<QString, bool> modulesFromJson(const QString &jsonString);
	//	static std::string modulesToJson(const QMap<QString, bool> &modulesMap);
};
