#pragma once

#include <stdexcept>
#include <vector>

#include <QtSql>
#include <QString>

#include "Templates/CRUDRepository.h"

class LocalManagement : CRUDLocalRepository
{
public:
	LocalManagement(const QSqlDatabase &database);
	~LocalManagement();

	QSqlRecord getRecord(const Query &query, DBStatus::StatusType *status = nullptr) const override;
	std::vector<QSqlRecord> getRecords(const Query &query, DBStatus::StatusType *status = nullptr) const override;
	bool execQuery(const Query &query, DBStatus::StatusType *status = nullptr) const override;

private:
	QSqlDatabase m_database;

	void fetchError(const QSqlError &sqlErr, DBStatus::StatusType *status = nullptr) const;
};
