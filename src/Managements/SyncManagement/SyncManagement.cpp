#include "SyncManagement.h"

SyncManagement::SyncManagement(const QSqlDatabase &database, const std::shared_ptr<WebDatabaseManager> &databaseWeb)
	: m_localManager(database), m_webManager(databaseWeb)
{
}

SyncManagement::~SyncManagement()
{
}

Sync SyncManagement::select(const std::string &login, DBStatus::StatusType *status) const
{
	Query query;
	query.query = QString("SELECT * FROM %1 WHERE %2 = '%3';")
					  .arg(SyncTable::TABLE_NAME, SyncTable::LOGIN, login.c_str())
					  .toStdString();

	auto reply = m_localManager.getRecord(query, status);

	if(!reply.isEmpty()) {
		return fetchFromRecord(reply);
	}

	return Sync();
}

std::vector<Sync> SyncManagement::selectAll(DBStatus::StatusType *status) const
{
	Query query;
	query.query = QString("SELECT * FROM %1 WHERE %2 = '%3';")
					  .arg(SyncTable::TABLE_NAME, SyncTable::LOGIN, UserSession::getInstance().getUser().login)
					  .toStdString();

	auto reply = m_localManager.getRecords(query, status);

	std::vector<Sync> syncs;
	for(const auto &sync: reply) {
		syncs.push_back(fetchFromRecord(sync));
	}

	return syncs;
}

bool SyncManagement::insert(const Sync &localSync, DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("INSERT INTO %1(%2, %3, %4) VALUES('%5', '%6', '%7');")
					  .arg(SyncTable::TABLE_NAME, SyncTable::LOGIN, SyncTable::USER_SYNC, SyncTable::JOB_SYNC, UserSession::getInstance().getUser().login, QString::number(localSync.userSync), QString::number(localSync.jobSync))
					  .toStdString();

	return m_localManager.execQuery(query, status);
}

bool SyncManagement::remove(const Sync &sync, DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("DELETE FROM %1 WHERE %2 = '%3';")
					  .arg(SyncTable::TABLE_NAME, SyncTable::LOGIN, UserSession::getInstance().getUser().login)
					  .toStdString();

	return m_localManager.execQuery(query, status);
}

bool SyncManagement::removeAll(DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("DELETE FROM %1;")
					  .arg(SyncTable::TABLE_NAME)
					  .toStdString();

	return m_localManager.execQuery(query, status);
}

bool SyncManagement::update(const Sync &sync, DBStatus::StatusType *status)
{
	auto existRecord = select(UserSession::getInstance().getUser().login.toStdString(), status);

	if(existRecord == Sync()) {
		return insert(sync, status);
	}

	Query query;
	query.query = QString("UPDATE %1 SET %2='%3', %4='%5' WHERE %6='%7';")
					  .arg(SyncTable::TABLE_NAME, SyncTable::USER_SYNC, QString::number(sync.userSync), SyncTable::JOB_SYNC, QString::number(sync.jobSync), SyncTable::LOGIN, UserSession::getInstance().getUser().login)
					  .toStdString();

	return m_localManager.execQuery(query, status);
	;
}

Sync SyncManagement::selectWeb(const std::string &login, DBStatus::StatusType *status) const
{
	Query query;
	query.query = QString("/%1/%2").arg(SyncTable::TABLE_NAME, UserSession::getInstance().getUser().login).toStdString();

	auto reply = m_webManager.getRecord(query, status);

	if(!reply.empty()) {
		return fetchFromRecordWeb(reply);
	}

	return Sync();
}

std::vector<Sync> SyncManagement::selectAllWeb(DBStatus::StatusType *status) const
{
	Query query;
	query.query = QString("/%1?filter=%2,eq,%3").arg(SyncTable::TABLE_NAME, SyncTable::LOGIN, UserSession::getInstance().getUser().login).toStdString();

	auto reply = m_webManager.getRecords(query, status);

	std::vector<Sync> syncs;
	for(auto const &syncObj: reply) {
		syncs.push_back(fetchFromRecordWeb(syncObj));
	}

	return syncs;
}

bool SyncManagement::insertWeb(const Sync &webSync, DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("/%1").arg(SyncTable::TABLE_NAME).toStdString();
	query.body = fetchToJsonWeb(webSync);

	return m_webManager.execQuery(query, status);
}

bool SyncManagement::removeWeb(const Sync &webSync, DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("/%1/%2").arg(SyncTable::TABLE_NAME, UserSession::getInstance().getUser().login).toStdString();

	return m_webManager.execQuery(query, status);
}

bool SyncManagement::removeAllWeb(DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("/%1?filter=%2,eq,%3").arg(SyncTable::TABLE_NAME, SyncTable::LOGIN, UserSession::getInstance().getUser().login).toStdString();

	return m_webManager.execQuery(query, status);
}

bool SyncManagement::updateWeb(const Sync &sync, DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("/%1/%2").arg(SyncTable::TABLE_NAME, UserSession::getInstance().getUser().login).toStdString();
	query.body = fetchToJsonWeb(sync);

	return m_webManager.execQuery(query, status);
}

Sync SyncManagement::fetchFromRecord(const QSqlRecord &record)
{
	Sync sync;
	sync.userSync = record.field(SyncTable::USER_SYNC).value().toLongLong();
	sync.jobSync = record.field(SyncTable::JOB_SYNC).value().toLongLong();

	return sync;
}

Sync SyncManagement::fetchFromRecordWeb(const QJsonObject &records)
{
	Sync sync;
	sync.userSync = static_cast<long long>(records[SyncTable::USER_SYNC].toDouble());
	sync.jobSync = static_cast<long long>(records[SyncTable::JOB_SYNC].toDouble());

	return sync;
}

std::string SyncManagement::fetchToJsonWeb(const Sync &sync)
{
	QJsonObject obj;
	obj.insert(SyncTable::USER_SYNC, sync.userSync);
	obj.insert(SyncTable::JOB_SYNC, sync.jobSync);
	QJsonDocument doc(obj);

	return doc.toJson(QJsonDocument::Compact).toStdString();
}
