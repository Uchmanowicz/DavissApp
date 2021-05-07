#pragma once

#include <stdexcept>
#include <vector>

#include <QtSql>
#include <QString>

#include "Common/Utility.h"
#include "Templates/CRUDRepository.h"
#include "Templates/QueryRespository.h"

class SqlLocalManagement //: private CRUDLocalRepository<Query<Obj>, QSqlRecord>
{
public:
	SqlLocalManagement(const QSqlDatabase &database);
	~SqlLocalManagement() = default;

	QSqlRecord getRecord(const Query &query, DBStatus::StatusType *status = nullptr) const;
	std::vector<QSqlRecord> getRecords(const Query &query, DBStatus::StatusType *status = nullptr) const;
	bool execQuery(const Query &query, DBStatus::StatusType *status = nullptr) const;

private:
	QSqlDatabase m_database;

	void fetchError(const QSqlError &sqlErr, DBStatus::StatusType *status = nullptr) const;
};

//#include "LocalManagement_impl.h"
