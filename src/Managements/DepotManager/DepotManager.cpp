#include "DepotManager.h"

DepotManager::DepotManager(const QSqlDatabase &database, const std::shared_ptr<WebDatabaseManager> &databaseWeb) //, const std::shared_ptr<Synchronizer> &synchronizer_)
	: m_localManager(database), m_webManager(databaseWeb) //, m_synchronizer(synchronizer_)
{
}

DepotManager::~DepotManager()
{
}

DepotItem DepotManager::select(const std::string &login, DBStatus::StatusType *status) const
{
	Query query;
	query.query = QString("SELECT * FROM %1 WHERE %2 = '%3';")
					  .arg(DepotTable::TABLE_NAME, DepotTable::LOGIN, login.c_str())
					  .toStdString();

	auto reply = m_localManager.getRecord(query, status);

	if(!reply.isEmpty()) {
		return fetchFromRecord(reply);
	}

	return DepotItem();
}

std::vector<DepotItem> DepotManager::selectAll(DBStatus::StatusType *status) const
{
	Query query;
	query.query = QString("SELECT * FROM %1;")
					  .arg(DepotTable::TABLE_NAME)
					  .toStdString();

	auto reply = m_localManager.getRecords(query, status);

	std::vector<DepotItem> DepotItems;
	for(const auto &DepotItem: reply) {
		DepotItems.push_back(fetchFromRecord(DepotItem));
	}

	return DepotItems;
}

bool DepotManager::insert(const DepotItem &depotItem, DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("INSERT INTO %1(%2, %3, %4, %5, %6, %7, %8) VALUES('%9', '%10', '%11', '%12', '%13', '%14', '%15');")
					  .arg(DepotTable::TABLE_NAME, DepotTable::LOGIN, DepotTable::AMOUNT, DepotTable::UNIT, DepotTable::CATEGORY, DepotTable::LOCALIZATION, DepotTable::DATA, DepotTable::ID)
					  .arg(depotItem.login, depotItem.login, QString::number(depotItem.amount), depotItem.unit, depotItem.category, depotItem.localization, depotItem.data, depotItem.getID())
					  .toStdString();

	return m_localManager.execQuery(query, status);
}

bool DepotManager::remove(const DepotItem &depotItem, DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("DELETE FROM %1 WHERE %2 = '%3';")
					  .arg(DepotTable::TABLE_NAME, DepotTable::ID, depotItem.getID())
					  .toStdString();

	return m_localManager.execQuery(query, status);
}

bool DepotManager::removeAll(DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("DELETE FROM %1 WHERE %2 = '%3';")
					  .arg(DepotTable::TABLE_NAME, DepotTable::LOGIN, UserSession::getInstance().getUser().login)
					  .toStdString();

	return m_localManager.execQuery(query, status);
}

bool DepotManager::update(const DepotItem &depotItem, DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("UPDATE %1 SET %2='%3', %4='%5', %6='%7', %8='%9', %10='%11' WHERE %12 = '%13';")
					  .arg(DepotTable::TABLE_NAME, DepotTable::CATEGORY, depotItem.category, DepotTable::AMOUNT, QString::number(depotItem.amount), DepotTable::UNIT, depotItem.unit)
					  .arg(DepotTable::LOCALIZATION, depotItem.localization, DepotTable::DATA, depotItem.data, DepotTable::ID, depotItem.getID())
					  .toStdString();

	return m_localManager.execQuery(query, status);
}

DepotItem DepotManager::selectWeb(const std::string &login, DBStatus::StatusType *status) const
{
	Query query;
	query.query = QString("/%1/%2").arg(DepotTable::TABLE_NAME, login.c_str()).toStdString();

	auto reply = m_webManager.getRecord(query, status);

	if(!reply.empty()) {
		return fetchFromRecordWeb(reply);
	}

	return DepotItem();
}

std::vector<DepotItem> DepotManager::selectAllWeb(DBStatus::StatusType *status) const
{
	Query query;
	query.query = QString("/%1?filter=%2,eq,%3").arg(DepotTable::TABLE_NAME, DepotTable::LOGIN, UserSession::getInstance().getUser().login).toStdString();

	auto reply = m_webManager.getRecords(query, status);

	std::vector<DepotItem> DepotItems;
	for(auto const &DepotItemObj: reply) {
		DepotItems.push_back(fetchFromRecordWeb(DepotItemObj));
	}

	return DepotItems;
}

bool DepotManager::insertWeb(const DepotItem &DepotItem, DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("/%1").arg(DepotTable::TABLE_NAME).toStdString();
	query.body = fetchToJsonWeb(DepotItem);

	return m_webManager.execQuery(query, status);
}

bool DepotManager::removeWeb(const DepotItem &DepotItem, DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("/%1/%2").arg(DepotTable::TABLE_NAME, DepotItem.login).toStdString();

	return m_webManager.execQuery(query, status);
}

bool DepotManager::removeAllWeb(DBStatus::StatusType *status)
{
	return 0;
}

bool DepotManager::updateWeb(const DepotItem &DepotItem, DBStatus::StatusType *status)
{
	auto qrTxt = QString("/%1/%2").arg(DepotTable::TABLE_NAME, DepotItem.login).toStdString();
	Query query(qrTxt, fetchToJsonWeb(DepotItem), Query::UPDATE);

	return m_webManager.execQuery(query, status);
}

DepotItem DepotManager::fetchFromRecord(const QSqlRecord &record)
{
	DepotItem depotItem;
	depotItem.login = record.field(DepotTable::LOGIN).value().toString();
	depotItem.category = record.field(DepotTable::CATEGORY).value().toString();
	depotItem.amount = record.field(DepotTable::AMOUNT).value().toLongLong();
	depotItem.unit = record.field(DepotTable::UNIT).value().toString();
	depotItem.localization = record.field(DepotTable::LOCALIZATION).value().toString();
	depotItem.data = record.field(DepotTable::DATA).value().toString();

	return depotItem;
}

DepotItem DepotManager::fetchFromRecordWeb(const QJsonObject &records)
{
	DepotItem DepotItem;
	DepotItem.login = records[DepotTable::LOGIN].toString();
	DepotItem.category = records[DepotTable::CATEGORY].toString();
	DepotItem.amount = records[DepotTable::AMOUNT].toDouble();
	DepotItem.unit = records[DepotTable::UNIT].toString();
	DepotItem.localization = records[DepotTable::LOCALIZATION].toString();
	DepotItem.data = records[DepotTable::DATA].toString();

	return DepotItem;
}

std::string DepotManager::fetchToJsonWeb(const DepotItem &depotItem)
{
	QJsonObject obj;
	//	obj.insert(DepotTable::PASSWORD, DepotItem.password);
	//	obj.insert(DepotTable::NAME, DepotItem.name);
	//	obj.insert(DepotTable::ROLE, DepotItem.DepotItemRole);
	//	obj.insert(DepotTable::IS_BLOCKED, DepotItem.isBlocked ? "1" : "0");
	//	obj.insert(DepotTable::AVATAR, DepotItem.avatar);
	//	obj.insert(DepotTable::MODULES, QString(modulesToJson(DepotItem.modulesEnabled).c_str()));
	QJsonDocument doc(obj);

	return doc.toJson(QJsonDocument::Compact).toStdString();
}
