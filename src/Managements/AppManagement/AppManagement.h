#pragma once

#include <string>
#include <QtSql>

#include "Common/Utility.h"
#include "Managements/LocalManagement.h"
#include "Templates/CRUDManagement.h"
#include "Templates/QueryRespository.h"
#include "Models/App.h"
#include "AppTable.h"

class AppManagement : public CRUDLocalManagement<std::string, App>
{
public:
	AppManagement(const QSqlDatabase &database);
	~AppManagement();

	App select(const std::string &app, DBStatus::StatusType *status = nullptr) const override;
	std::vector<App> selectAll(DBStatus::StatusType *status = nullptr) const override;
	bool insert(const App &app, DBStatus::StatusType *status = nullptr) override;
	bool remove(const App &app, DBStatus::StatusType *status = nullptr) override;
	bool removeAll(DBStatus::StatusType *status = nullptr) override;
	bool update(const App &app, DBStatus::StatusType *status = nullptr) override;

private:
	LocalManagement m_localManager;

	static App fetchFromRecord(const QSqlRecord &record);
};
