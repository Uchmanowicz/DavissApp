#include "DepotManager.h"

using namespace Depot;
using namespace Person;
using namespace DB;

namespace Managers
{
	DepotManager::DepotManager(const std::shared_ptr<LocalManagement> &localManagement, const std::shared_ptr<WebManagement> &webManagement) //, const std::shared_ptr<Synchronizer> &synchronizer_)
		: m_localManager(localManagement), m_webManager(webManagement) //, m_synchronizer(synchronizer_)
	{
	}

	Depot::Item DepotManager::select(const std::string &login, Status *status) const
	{
		DB::Query query;
		query.query = QString("SELECT * FROM %1 WHERE %2 = '%3';")
						  .arg(DepotTable::TABLE_NAME, DepotTable::LOGIN, login.c_str())
						  .toStdString();

		auto reply = m_localManager->getRecord(query, status);

		if(!reply.isEmpty()) {
			return fetchFromRecord(reply);
		}

		return Depot::Item();
	}

	std::vector<Depot::Item> DepotManager::selectAll(Status *status) const
	{
		DB::Query query;
		query.query = QString("SELECT * FROM %1;")
						  .arg(DepotTable::TABLE_NAME)
						  .toStdString();

		auto reply = m_localManager->getRecords(query, status);

		std::vector<Depot::Item> DepotItems;
		for(const auto &DepotItem: reply) {
			DepotItems.push_back(fetchFromRecord(DepotItem));
		}

		return DepotItems;
	}

	bool DepotManager::insert(const Depot::Item &depotItem, Status *status)
	{
		DB::Query query;
		query.query = QString("INSERT INTO %1(%2, %3, %4, %5, %6, %7, %8) VALUES('%9', '%10', '%11', '%12', '%13', '%14', '%15');")
						  .arg(DepotTable::TABLE_NAME, DepotTable::LOGIN, DepotTable::AMOUNT, DepotTable::UNIT, DepotTable::CATEGORY, DepotTable::LOCALIZATION, DepotTable::PARAMETERS, DepotTable::ID)
						  .arg(depotItem.login, QString::number(depotItem.amount), depotItem.unit, depotItem.category, depotItem.localization, Depot::ParameterParser::toJsonString(depotItem.parameters), depotItem.getID())
						  .toStdString();

		return m_localManager->execQuery(query, status);
	}

	bool DepotManager::remove(const Depot::Item &depotItem, Status *status)
	{
		DB::Query query;
		query.query = QString("DELETE FROM %1 WHERE %2 = '%3';")
						  .arg(DepotTable::TABLE_NAME, DepotTable::ID, depotItem.getID())
						  .toStdString();

		return m_localManager->execQuery(query, status);
	}

	bool DepotManager::removeAll(Status *status)
	{
		DB::Query query;
		query.query = QString("DELETE FROM %1 WHERE %2 = '%3';")
						  .arg(DepotTable::TABLE_NAME, DepotTable::LOGIN, UserSession::getInstance().getUser().login)
						  .toStdString();

		return m_localManager->execQuery(query, status);
	}

	bool DepotManager::update(const Depot::Item &depotItem, Status *status)
	{
		DB::Query query;
		query.query = QString("UPDATE %1 SET %2='%3', %4='%5', %6='%7', %8='%9', %10='%11' WHERE %12 = '%13';")
						  .arg(DepotTable::TABLE_NAME, DepotTable::CATEGORY, depotItem.category, DepotTable::AMOUNT, QString::number(depotItem.amount), DepotTable::UNIT, depotItem.unit)
						  .arg(DepotTable::LOCALIZATION, depotItem.localization, DepotTable::PARAMETERS, Depot::ParameterParser::toJsonString(depotItem.parameters), DepotTable::ID, depotItem.getID())
						  .toStdString();

		return m_localManager->execQuery(query, status);
	}

	Depot::Item DepotManager::selectWeb(const std::string &login, Status *status) const
	{
		DB::Query query;
		query.query = QString("/%1/%2").arg(DepotTable::TABLE_NAME, login.c_str()).toStdString();

		auto reply = m_webManager->getRecord(query, status);

		if(!reply.empty()) {
			return fetchFromRecordWeb(reply);
		}

		return Depot::Item();
	}

	std::vector<Depot::Item> DepotManager::selectAllWeb(Status *status) const
	{
		DB::Query query;
		query.query = QString("/%1?filter=%2,eq,%3").arg(DepotTable::TABLE_NAME, DepotTable::LOGIN, UserSession::getInstance().getUser().login).toStdString();

		auto reply = m_webManager->getRecords(query, status);

		std::vector<Depot::Item> depotItems;
		for(auto const &depotItemObj: reply) {
			depotItems.push_back(fetchFromRecordWeb(depotItemObj));
		}

		return depotItems;
	}

	bool DepotManager::insertWeb(const Depot::Item &DepotItem, Status *status)
	{
		DB::Query query;
		query.query = QString("/%1").arg(DepotTable::TABLE_NAME).toStdString();
		query.body = fetchToJsonWeb(DepotItem);

		return m_webManager->execQuery(query, status);
	}

	bool DepotManager::removeWeb(const Depot::Item &DepotItem, Status *status)
	{
		DB::Query query;
		query.query = QString("/%1/%2").arg(DepotTable::TABLE_NAME, DepotItem.login).toStdString();

		return m_webManager->execQuery(query, status);
	}

	bool DepotManager::removeAllWeb(Status *status)
	{
		return 0;
	}

	bool DepotManager::updateWeb(const Depot::Item &DepotItem, Status *status)
	{
		auto qrTxt = QString("/%1/%2").arg(DepotTable::TABLE_NAME, DepotItem.login).toStdString();
		DB::Query query(qrTxt, fetchToJsonWeb(DepotItem), DB::Query::UPDATE);

		return m_webManager->execQuery(query, status);
	}

	Depot::Item DepotManager::fetchFromRecord(const QSqlRecord &record)
	{
		Depot::Item depotItem;
		depotItem.login = record.field(DepotTable::LOGIN).value().toString();
		depotItem.category = record.field(DepotTable::CATEGORY).value().toString();
		depotItem.amount = record.field(DepotTable::AMOUNT).value().toLongLong();
		depotItem.unit = record.field(DepotTable::UNIT).value().toString();
		depotItem.localization = record.field(DepotTable::LOCALIZATION).value().toString();
		depotItem.parameters = Depot::ParameterParser::fromJson(record.field(DepotTable::PARAMETERS).value().toJsonArray());

		return depotItem;
	}

	Depot::Item DepotManager::fetchFromRecordWeb(const QJsonObject &records)
	{
		Depot::Item depotItem;
		depotItem.login = records[DepotTable::LOGIN].toString();
		depotItem.category = records[DepotTable::CATEGORY].toString();
		depotItem.amount = records[DepotTable::AMOUNT].toDouble();
		depotItem.unit = records[DepotTable::UNIT].toString();
		depotItem.localization = records[DepotTable::LOCALIZATION].toString();
		depotItem.parameters = Depot::ParameterParser::fromJson(records[DepotTable::PARAMETERS].toArray());

		return depotItem;
	}

	std::string DepotManager::fetchToJsonWeb(const Depot::Item &depotItem)
	{
		QJsonObject obj;
		obj.insert(DepotTable::LOGIN, depotItem.login);
		obj.insert(DepotTable::CATEGORY, depotItem.category);
		obj.insert(DepotTable::AMOUNT, depotItem.amount);
		obj.insert(DepotTable::UNIT, depotItem.unit);
		obj.insert(DepotTable::LOCALIZATION, depotItem.localization);
		obj.insert(DepotTable::PARAMETERS, Depot::ParameterParser::toJsonString(depotItem.parameters));
		QJsonDocument doc(obj);

		return doc.toJson(QJsonDocument::Compact).toStdString();
	}
}
