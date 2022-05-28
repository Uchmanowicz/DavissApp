#pragma once

#include <stdexcept>
#include <vector>

#include <QtSql>
#include <QString>

#include "Templates/CRUDRepository.h"

namespace DB
{
	class LocalManagement : Templates::CRUDLocalRepository
	{
	public:
		LocalManagement(const QSqlDatabase &database);
		~LocalManagement();

		QSqlRecord getRecord(const DB::Query &query, DB::Status *status = nullptr) const override;
		std::vector<QSqlRecord> getRecords(const DB::Query &query, DB::Status *status = nullptr) const override;
		bool execQuery(const DB::Query &query, DB::Status *status = nullptr) const override;

	private:
		QSqlDatabase m_database;

		void fetchError(const QSqlError &sqlErr, DB::Status *status = nullptr) const;
	};
}
