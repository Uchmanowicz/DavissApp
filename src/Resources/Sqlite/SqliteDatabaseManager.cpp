#include "SqliteDatabaseManager.h"

SqliteDatabaseManager::SqliteDatabaseManager(const QString &databaseName)
	: DatabaseManager("QSQLITE")
{
	setDatabaseName(databaseName);

	if(open()) {
		createDatabaseArchitecture();
	}else {
		qCritical().noquote() << "DATABASE_ERR_COULDNT_OPEN";
	}
}
