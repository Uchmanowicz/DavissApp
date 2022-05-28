#pragma once

#include <vector>
#include <string>

#include <QJsonArray>
#include <QJsonObject>
#include <QString>

#include "Templates/CRUDRepository.h"
#include "Resources/IWebDbExecutor.h"

class WebManagement : private Templates::CRUDWebRepository
{
public:
	WebManagement(const std::shared_ptr<DB::IWebDbExecutor> &database);
	virtual ~WebManagement();

	QJsonObject getRecord(const DB::Query &query, DB::Status *status = nullptr) const override;
	std::vector<QJsonObject> getRecords(const DB::Query &query, DB::Status *status = nullptr) const override;
	bool execQuery(const DB::Query &query, DB::Status *status = nullptr) const override;

private:
	std::shared_ptr<DB::IWebDbExecutor> m_database;
	std::string m_lastError;

	QJsonObject get(const DB::Query &query, DB::Status *status) const;
	bool put(const DB::Query &query, DB::Status *status) const;
	bool post(const DB::Query &query, DB::Status *status) const;
	bool remove(const DB::Query &query, DB::Status *status) const;
};
