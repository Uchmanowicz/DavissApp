#pragma once

#include <QtSql>
#include <QDebug>

#include "Managements/AppManagement/AppTable.h"
#include "Managements/UserManagement/UserTable.h"
#include "Managements/JobManagement/JobHistoryTable.h"
#include "Managements/SyncManagement/SyncTable.h"

class DatabaseManager : public QSqlDatabase
{
	static int CONNECTION_INDEX;

public:
	DatabaseManager(const QString &driver);
	virtual ~DatabaseManager();
	virtual void createDatabaseArchitecture();

protected:
	virtual void createAppTable();
	virtual void createUsersTable();
	virtual void createJobHistory();
	virtual void createSyncTable();
};
