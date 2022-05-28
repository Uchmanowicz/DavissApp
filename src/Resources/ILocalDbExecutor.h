#pragma once

#include <QtSql>
#include <QDebug>

#include "Managements/AppManagement/AppTable.h"
#include "Managements/UserManagement/UserTable.h"
#include "Managements/JobManagement/JobHistoryTable.h"
#include "Managements/Depot/DepotTable.h"
#include "Managements/SyncManagement/SyncTable.h"

namespace DB
{
	class ILocalDbExecutor : public QSqlDatabase
	{
		static int CONNECTION_INDEX;

	public:
		ILocalDbExecutor(const QString &driver);
		virtual ~ILocalDbExecutor();
		virtual void createDatabaseArchitecture();

	protected:
		virtual void createAppTable();
		virtual void createUsersTable();
		virtual void createJobHistory();
		virtual void createDepotTable();
		virtual void createSyncTable();
	};
}
