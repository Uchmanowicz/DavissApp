#include "WebManagement.h"

// using namespace Managers;

WebManagement::WebManagement(const std::shared_ptr<DB::IWebDbExecutor> &database)
	: m_database(database)
{
}

WebManagement::~WebManagement()
{
}

QJsonObject WebManagement::get(const DB::Query &query, DB::Status *status) const
{
	QString req(query.query.c_str());
	return m_database->get(req, status);
}

bool WebManagement::put(const DB::Query &query, DB::Status *status) const
{
	QString req(query.query.c_str());
	QString body(query.body.c_str());
	auto reply = m_database->put(req, body, status);
	return reply[""].toInt() > 0;
}

bool WebManagement::post(const DB::Query &query, DB::Status *status) const
{
	QString req(query.query.c_str());
	QString body(query.body.c_str());
	auto reply = m_database->post(req, body, status);
	return reply[""].toInt() > 0;
}

bool WebManagement::remove(const DB::Query &query, DB::Status *status) const
{
	QString req(query.query.c_str());
	auto reply = m_database->delete_(req, status);
	return reply[""].toInt() > 0;
}

QJsonObject WebManagement::getRecord(const DB::Query &query, DB::Status *status) const
{
	return get(query, status);
}

std::vector<QJsonObject> WebManagement::getRecords(const DB::Query &query, DB::Status *status) const
{
	auto reply = get(query, status);

	QJsonArray replyArr = reply["records"].toArray();

	std::vector<QJsonObject> objs;
	for(const auto &record: replyArr) {
		QJsonObject recordObj = record.toObject();
		objs.push_back(recordObj);
	}

	return objs;
}

bool WebManagement::execQuery(const DB::Query &query, DB::Status *status) const
{
	switch(query.type) {
	case DB::Query::Type::INSERT:
		return post(query, status);
		break;
	case DB::Query::Type::UPDATE:
		return put(query, status);
		break;
	case DB::Query::Type::REMOVE:
		return remove(query, status);
		break;
	default:
		qDebug() << "Error during parse quering: Query Type empty";
		return false;
		break;
	}
}
