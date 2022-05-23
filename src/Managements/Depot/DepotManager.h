#pragma once

#include <QtSql>

#include "Common/Utility.h"
#include "Common/UserSession.h"
#include "Managements/WebManagement.h"
#include "Managements/LocalManagement.h"
#include "Templates/CRUDManagement.h"
#include "Templates/QueryRespository.h"
//#include "Services/Synchronizer.h"
#include "Models/Depot/Item.h"
#include "Parsers/Depot/ParameterParser.h"
#include "Managements/Depot/DepotTable.h"

using namespace Depot;

namespace Managers
{
	class DepotManager : public CRUDLocalManagement<std::string, Depot::Item>, public CRUDWebManagement<std::string, Depot::Item>
	{
	public:
		DepotManager(const std::shared_ptr<LocalManagement> &localManagement, const std::shared_ptr<WebManagement> &webManagement); //, const std::shared_ptr<Synchronizer> &synchronizer_);
		~DepotManager() = default;

		Depot::Item select(const std::string &login, DBStatus::StatusType *status = nullptr) const override;
		std::vector<Depot::Item> selectAll(DBStatus::StatusType *status = nullptr) const override;
		bool insert(const Depot::Item &depotItem, DBStatus::StatusType *status = nullptr) override;
		bool remove(const Depot::Item &depotItem, DBStatus::StatusType *status = nullptr) override;
		bool removeAll(DBStatus::StatusType *status = nullptr) override;
		bool update(const Depot::Item &depotItem, DBStatus::StatusType *status = nullptr) override;

		Depot::Item selectWeb(const std::string &login, DBStatus::StatusType *status = nullptr) const override;
		std::vector<Depot::Item> selectAllWeb(DBStatus::StatusType *status = nullptr) const override;
		bool insertWeb(const Depot::Item &depotItem, DBStatus::StatusType *status = nullptr) override;
		bool removeWeb(const Depot::Item &depotItem, DBStatus::StatusType *status = nullptr) override;
		bool removeAllWeb(DBStatus::StatusType *status = nullptr) override;
		bool updateWeb(const Depot::Item &depotItem, DBStatus::StatusType *status = nullptr) override;

	private:
		std::shared_ptr<LocalManagement> m_localManager;
		std::shared_ptr<WebManagement> m_webManager;
		//	std::shared_ptr<Synchronizer> m_synchronizer;

		std::string m_lastError;
		static Depot::Item fetchFromRecord(const QSqlRecord &record);
		static Depot::Item fetchFromRecordWeb(const QJsonObject &records);
		static std::string fetchToJsonWeb(const Depot::Item &depotItem);

		//	static QMap<QString, bool> modulesFromJson(const QString &jsonString);
		//	static std::string modulesToJson(const QMap<QString, bool> &modulesMap);
	};
}
