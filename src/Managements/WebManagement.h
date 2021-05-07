#pragma once

#include <vector>
#include <string>

#include <QJsonArray>
#include <QJsonObject>
#include <QString>

#include "Templates/CRUDRepository.h"
#include "Resources/PhpApiCrud/WebDatabaseManager.h"

class WebManagement: private CRUDWebRepository
{   
public:
	WebManagement(const std::shared_ptr<WebDatabaseManager> &database);
	virtual ~WebManagement();

	QJsonObject getRecord(const Query &query, DBStatus::StatusType *status = nullptr) const override;
	std::vector<QJsonObject> getRecords(const Query &query, DBStatus::StatusType *status = nullptr) const override;
	bool execQuery(const Query &query, DBStatus::StatusType *status = nullptr) const override;

private:
	std::shared_ptr<WebDatabaseManager> m_database;
	std::string m_lastError;

	QJsonObject get(const Query &query, DBStatus::StatusType *status) const;
	bool put(const Query &query, DBStatus::StatusType *status) const;
	bool post(const Query &query, DBStatus::StatusType *status) const;
	bool remove(const Query &query, DBStatus::StatusType *status) const;

};
