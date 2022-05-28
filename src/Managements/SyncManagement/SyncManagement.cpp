#include "SyncManagement.h"

using namespace Person;

namespace Managers
{
	SyncManagement::SyncManagement(const QSqlDatabase &database, const std::shared_ptr<DB::IWebDbExecutor> &databaseWeb)
		: m_localManager(database), m_webManager(databaseWeb)
	{
	}

	SyncManagement::~SyncManagement()
	{
	}

	Sync::Entities SyncManagement::select(const std::string &login, DB::Status *status) const
	{
		DB::Query query;
		query.query = QString("SELECT * FROM %1 WHERE %2 = '%3';")
						  .arg(Sync::SyncTable::TABLE_NAME, Sync::SyncTable::LOGIN, login.c_str())
						  .toStdString();

		auto reply = m_localManager.getRecord(query, status);

		if(!reply.isEmpty()) {
			return fetchFromRecord(reply);
		}

		return {};
	}

	std::vector<Sync::Entities> SyncManagement::selectAll(DB::Status *status) const
	{
		DB::Query query;
		query.query = QString("SELECT * FROM %1 WHERE %2 = '%3';")
						  .arg(Sync::SyncTable::TABLE_NAME, Sync::SyncTable::LOGIN, UserSession::getInstance().getUser().login)
						  .toStdString();

		auto reply = m_localManager.getRecords(query, status);

		std::vector<Sync::Entities> syncs;
		for(const auto &sync: reply) {
			syncs.push_back(fetchFromRecord(sync));
		}

		return syncs;
	}

	bool SyncManagement::insert(const Sync::Entities &localSync, DB::Status *status)
	{
		DB::Query query;
		query.query = QString("INSERT INTO %1(%2, %3, %4) VALUES('%5', '%6', '%7');")
						  .arg(Sync::SyncTable::TABLE_NAME, Sync::SyncTable::LOGIN, Sync::SyncTable::USER_SYNC, Sync::SyncTable::JOB_SYNC, UserSession::getInstance().getUser().login, QString::number(localSync.userSync), QString::number(localSync.jobSync))
						  .toStdString();

		return m_localManager.execQuery(query, status);
	}

	bool SyncManagement::remove(const Sync::Entities &sync, DB::Status *status)
	{
		DB::Query query;
		query.query = QString("DELETE FROM %1 WHERE %2 = '%3';")
						  .arg(Sync::SyncTable::TABLE_NAME, Sync::SyncTable::LOGIN, UserSession::getInstance().getUser().login)
						  .toStdString();

		return m_localManager.execQuery(query, status);
	}

	bool SyncManagement::removeAll(DB::Status *status)
	{
		DB::Query query;
		query.query = QString("DELETE FROM %1;")
						  .arg(Sync::SyncTable::TABLE_NAME)
						  .toStdString();

		return m_localManager.execQuery(query, status);
	}

	bool SyncManagement::update(const Sync::Entities &sync, DB::Status *status)
	{
		auto existRecord = select(UserSession::getInstance().getUser().login.toStdString(), status);

		if(existRecord == Sync::Entities()) {
			return insert(sync, status);
		}

		DB::Query query;
		query.query = QString("UPDATE %1 SET %2='%3', %4='%5' WHERE %6='%7';")
						  .arg(Sync::SyncTable::TABLE_NAME, Sync::SyncTable::USER_SYNC, QString::number(sync.userSync), Sync::SyncTable::JOB_SYNC, QString::number(sync.jobSync), Sync::SyncTable::LOGIN, UserSession::getInstance().getUser().login)
						  .toStdString();

		return m_localManager.execQuery(query, status);
		;
	}

	Sync::Entities SyncManagement::selectWeb(const std::string &login, DB::Status *status) const
	{
		DB::Query query;
		query.query = QString("/%1/%2").arg(Sync::SyncTable::TABLE_NAME, UserSession::getInstance().getUser().login).toStdString();

		auto reply = m_webManager.getRecord(query, status);

		if(!reply.empty()) {
			return fetchFromRecordWeb(reply);
		}

		return {};
	}

	std::vector<Sync::Entities> SyncManagement::selectAllWeb(DB::Status *status) const
	{
		DB::Query query;
		query.query = QString("/%1?filter=%2,eq,%3").arg(Sync::SyncTable::TABLE_NAME, Sync::SyncTable::LOGIN, UserSession::getInstance().getUser().login).toStdString();

		auto reply = m_webManager.getRecords(query, status);

		std::vector<Sync::Entities> syncs;
		for(auto const &syncObj: reply) {
			syncs.push_back(fetchFromRecordWeb(syncObj));
		}

		return syncs;
	}

	bool SyncManagement::insertWeb(const Sync::Entities &webSync, DB::Status *status)
	{
		DB::Query query;
		query.query = QString("/%1").arg(Sync::SyncTable::TABLE_NAME).toStdString();
		query.body = fetchToJsonWeb(webSync);

		return m_webManager.execQuery(query, status);
	}

	bool SyncManagement::removeWeb(const Sync::Entities &webSync, DB::Status *status)
	{
		DB::Query query;
		query.query = QString("/%1/%2").arg(Sync::SyncTable::TABLE_NAME, UserSession::getInstance().getUser().login).toStdString();

		return m_webManager.execQuery(query, status);
	}

	bool SyncManagement::removeAllWeb(DB::Status *status)
	{
		DB::Query query;
		query.query = QString("/%1?filter=%2,eq,%3").arg(Sync::SyncTable::TABLE_NAME, Sync::SyncTable::LOGIN, UserSession::getInstance().getUser().login).toStdString();

		return m_webManager.execQuery(query, status);
	}

	bool SyncManagement::updateWeb(const Sync::Entities &sync, DB::Status *status)
	{
		DB::Query query;
		query.query = QString("/%1/%2").arg(Sync::SyncTable::TABLE_NAME, UserSession::getInstance().getUser().login).toStdString();
		query.body = fetchToJsonWeb(sync);

		return m_webManager.execQuery(query, status);
	}

	Sync::Entities SyncManagement::fetchFromRecord(const QSqlRecord &record)
	{
		Sync::Entities sync;
		sync.userSync = record.field(Sync::SyncTable::USER_SYNC).value().toLongLong();
		sync.jobSync = record.field(Sync::SyncTable::JOB_SYNC).value().toLongLong();

		return sync;
	}

	Sync::Entities SyncManagement::fetchFromRecordWeb(const QJsonObject &records)
	{
		Sync::Entities sync;
		sync.userSync = static_cast<long long>(records[Sync::SyncTable::USER_SYNC].toDouble());
		sync.jobSync = static_cast<long long>(records[Sync::SyncTable::JOB_SYNC].toDouble());

		return sync;
	}

	std::string SyncManagement::fetchToJsonWeb(const Sync::Entities &sync)
	{
		QJsonObject obj;
		obj.insert(Sync::SyncTable::USER_SYNC, sync.userSync);
		obj.insert(Sync::SyncTable::JOB_SYNC, sync.jobSync);
		QJsonDocument doc(obj);

		return doc.toJson(QJsonDocument::Compact).toStdString();
	}
}
