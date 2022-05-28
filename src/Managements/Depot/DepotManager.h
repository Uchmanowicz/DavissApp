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
	class DepotManager : public Templates::CRUDLocalManagement<std::string, Depot::Item>, public Templates::CRUDWebManagement<std::string, Depot::Item>
	{
	public:
		DepotManager(const std::shared_ptr<DB::LocalManagement> &localManagement, const std::shared_ptr<WebManagement> &webManagement); //, const std::shared_ptr<Synchronizer> &synchronizer_);
		~DepotManager() = default;

		Depot::Item select(const std::string &login, DB::Status *status = nullptr) const override;
		std::vector<Depot::Item> selectAll(DB::Status *status = nullptr) const override;
		bool insert(const Depot::Item &depotItem, DB::Status *status = nullptr) override;
		bool remove(const Depot::Item &depotItem, DB::Status *status = nullptr) override;
		bool removeAll(DB::Status *status = nullptr) override;
		bool update(const Depot::Item &depotItem, DB::Status *status = nullptr) override;

		Depot::Item selectWeb(const std::string &login, DB::Status *status = nullptr) const override;
		std::vector<Depot::Item> selectAllWeb(DB::Status *status = nullptr) const override;
		bool insertWeb(const Depot::Item &depotItem, DB::Status *status = nullptr) override;
		bool removeWeb(const Depot::Item &depotItem, DB::Status *status = nullptr) override;
		bool removeAllWeb(DB::Status *status = nullptr) override;
		bool updateWeb(const Depot::Item &depotItem, DB::Status *status = nullptr) override;

	private:
		std::shared_ptr<DB::LocalManagement> m_localManager;
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
