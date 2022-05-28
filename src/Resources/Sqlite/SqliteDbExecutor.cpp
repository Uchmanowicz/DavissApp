#include "SqliteDbExecutor.h"

namespace DB
{
	SqliteDbExecutor::SqliteDbExecutor(const QString &databaseName)
		: ILocalDbExecutor("QSQLITE")
	{
		setDatabaseName(databaseName);

		if(open()) {
			createDatabaseArchitecture();
		} else {
			qCritical().noquote() << "DATABASE_ERR_COULDNT_OPEN";
		}
	}
}
