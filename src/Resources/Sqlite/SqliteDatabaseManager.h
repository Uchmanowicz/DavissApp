#pragma once

#include "Resources/DatabaseManager.h"

class SqliteDatabaseManager : public DatabaseManager
{
public:
	SqliteDatabaseManager(const QString &databaseName);

};
