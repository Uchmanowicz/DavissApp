#pragma once

#include <memory>
#include <vector>
#include <string>

#include <QtSql>

#include "Templates/QueryRespository.h"
#include "Resources/DatabaseStatus.h"

class CRUDLocalRepository
{   
public:
	CRUDLocalRepository() = default;
	virtual ~CRUDLocalRepository() = default;
	virtual QSqlRecord getRecord(const Query &query, DBStatus::StatusType *status = nullptr) const = 0;
	virtual std::vector<QSqlRecord> getRecords(const Query &query, DBStatus::StatusType *status = nullptr) const = 0;
	virtual bool execQuery(const Query &query, DBStatus::StatusType *status = nullptr) const = 0;
};

class CRUDWebRepository
{
public:
	CRUDWebRepository() = default;
	virtual ~CRUDWebRepository() = default;
	virtual QJsonObject getRecord(const Query &query, DBStatus::StatusType *status = nullptr) const = 0;
	virtual std::vector<QJsonObject> getRecords(const Query &query, DBStatus::StatusType *status = nullptr) const = 0;
	virtual bool execQuery(const Query &query, DBStatus::StatusType *status = nullptr) const = 0;
};


