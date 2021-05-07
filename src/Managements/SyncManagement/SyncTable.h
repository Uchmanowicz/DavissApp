#pragma once

#include "Managements/UserManagement/UserTable.h"
#include "Managements/JobManagement/JobHistoryTable.h"

struct SyncTable final
{
	static constexpr char const *TABLE_NAME = "Sync";
	static constexpr char const *LOGIN = "Login";
	static constexpr char const *USER_SYNC = UserTable::TABLE_NAME;
	static constexpr char const *JOB_SYNC = JobHistoryTable::TABLE_NAME;

};
