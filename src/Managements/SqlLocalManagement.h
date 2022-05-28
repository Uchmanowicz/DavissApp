#pragma once

#include <stdexcept>
#include <vector>

#include <QtSql>
#include <QString>

#include "Common/Utility.h"
#include "Templates/CRUDRepository.h"
#include "Templates/QueryRespository.h"

namespace DB
{
	class SqlLocalManagement //: private CRUDLocalRepository<Query<Obj>, QSqlRecord>
	{
	public:
		SqlLocalManagement(const QSqlDatabase &database);
		~SqlLocalManagement() = default;

		QSqlRecord getRecord(const DB::Query &query, DB::Status *status = nullptr) const;
		std::vector<QSqlRecord> getRecords(const DB::Query &query, DB::Status *status = nullptr) const;
		bool execQuery(const DB::Query &query, DB::Status *status = nullptr) const;

	private:
		QSqlDatabase m_database;

		void fetchError(const QSqlError &sqlErr, DB::Status *status = nullptr) const;
	};
}
//#include "LocalManagement_impl.h"
