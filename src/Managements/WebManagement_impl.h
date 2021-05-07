#pragma once

#include "WebManagement.h"

template <typename Obj>
WebManagement<Obj>::WebManagement(const std::shared_ptr<WebDatabaseManager> &database)
	: m_database(database)
{
}

template <typename Obj>
WebManagement<Obj>::~WebManagement()
{
}

template <typename Obj>
QJsonObject WebManagement<Obj>::get(const Query<Obj> &query, DBStatus::StatusType *status) const
{
	QString req(query.query.c_str());
	return m_database->get(req, status);
}

template <typename Obj>
QJsonObject WebManagement<Obj>::put(const Query<Obj> &query, DBStatus::StatusType *status) const
{
	QString req(query.query.c_str());
	QString body(query.body.c_str());
	return m_database->put(req, body, status);
}

template <typename Obj>
QJsonObject WebManagement<Obj>::post(const Query<Obj> &query, DBStatus::StatusType *status) const
{
	QString req(query.query.c_str());
	QString body(query.body.c_str());
	return m_database->post(req, body, status);
}

template <typename Obj>
QJsonObject WebManagement<Obj>::delete_(const Query<Obj> &query, DBStatus::StatusType *status) const
{
	QString req(query.query.c_str());
	return m_database->delete_(req, status);
}

template <typename Obj>
QJsonObject WebManagement<Obj>::selectWeb(const Query<Obj> &query, DBStatus::StatusType *status) const
{
		return get(query, status);
}

template <typename Obj>
std::vector<QJsonObject> WebManagement<Obj>::selectAllWeb(const Query<Obj> &query, DBStatus::StatusType *status) const
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

template <typename Obj>
bool WebManagement<Obj>::insertWeb(const Query<Obj> &query, DBStatus::StatusType *status)
{
	auto reply = post(query, status);
	return reply[""].toInt() > 0;
}

template <typename Obj>
bool WebManagement<Obj>::updateWeb(const Query<Obj> &query, DBStatus::StatusType *status)
{
	auto reply = put(query, status);
	return reply[""].toInt() > 0;
}

template <typename Obj>
bool WebManagement<Obj>::removeWeb(const Query<Obj> &query, DBStatus::StatusType *status)
{
	auto reply = delete_(query, status);
	return reply[""].toInt() > 0;
}

template <typename Obj>
bool WebManagement<Obj>::removeAllWeb(const Query<Obj> &query, DBStatus::StatusType *status)
{
	auto reply = delete_(query, status);
	return reply[""].toInt() > 0;
}
