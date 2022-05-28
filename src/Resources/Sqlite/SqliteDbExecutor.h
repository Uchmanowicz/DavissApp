#pragma once

#include "Resources/ILocalDbExecutor.h"

namespace DB
{
	class SqliteDbExecutor : public ILocalDbExecutor
	{
	public:
		SqliteDbExecutor(const QString &databaseName);
	};
}
