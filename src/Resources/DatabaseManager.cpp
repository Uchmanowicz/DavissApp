#include "DatabaseManager.h"

int DatabaseManager::CONNECTION_INDEX = 0;

DatabaseManager::DatabaseManager(const QString &driver)
	: QSqlDatabase(QSqlDatabase::addDatabase(driver, QString("Connection") + QString::number(++CONNECTION_INDEX)))
{
}

DatabaseManager::~DatabaseManager()
{
	if(isOpen()) {
		close();
	}
}

void DatabaseManager::createDatabaseArchitecture()
{
	createAppTable();
	createUsersTable();
	createJobHistory();
	createDepotTable();
	createSyncTable();
}

void DatabaseManager::createAppTable()
{
	QString sql(QString("CREATE TABLE IF NOT EXISTS "
						" %1("
						"%2 text primary key,"
						"%3 bool"
						");")
					.arg(AppTable::TABLE_NAME, AppTable::APPEARANCE, AppTable::SYNC));

	QSqlQuery query(*this);
	if(!query.exec(sql)) {
		qCritical().noquote() << query.lastError().text();
	}
}

void DatabaseManager::createUsersTable()
{
	QString sql(QString("CREATE TABLE IF NOT EXISTS "
						" %1("
						"%2 text primary key,"
						"%3 text,"
						"%4 text,"
						"%5 integer,"
						"%6 text,"
						"%7 bool,"
						"%8 bool,"
						"%9 blob"
						");")
					.arg(UserTable::TABLE_NAME, UserTable::LOGIN, UserTable::PASSWORD, UserTable::NAME, UserTable::ROLE, UserTable::MODULES, UserTable::IS_BLOCKED, UserTable::IsAlwaysLogged, UserTable::AVATAR));

	QSqlQuery query(*this);
	if(!query.exec(sql)) {
		qCritical().noquote() << query.lastError().text();
	}
}

void DatabaseManager::createJobHistory()
{
	QString sql(QString("CREATE TABLE IF NOT EXISTS "
						" %1("
						"%2 text primary key,"
						"%3 integer,"
						"%4 integer,"
						"%5 text"
						");")
					.arg(JobHistoryTable::TABLE_NAME, JobHistoryTable::LOGIN_TIMESTAMP, JobHistoryTable::OUT_TIMESTAMP, JobHistoryTable::DURATION, JobHistoryTable::LOGIN));

	QSqlQuery query(*this);
	if(!query.exec(sql)) {
		qCritical().noquote() << query.lastError().text();
	}
}

void DatabaseManager::createDepotTable()
{
	QString sql(QString("CREATE TABLE IF NOT EXISTS "
						" %1("
						"%2 text primary key,"
						"%3 tex,"
						"%4 text,"
						"%5 long,"
						"%6 text,"
						"%7 text,"
						"%8 text"
						");")
					.arg(DepotTable::TABLE_NAME, DepotTable::ID, DepotTable::LOGIN, DepotTable::CATEGORY, DepotTable::AMOUNT, DepotTable::UNIT, DepotTable::LOCALIZATION, DepotTable::PARAMETERS));

	QSqlQuery query(*this);
	if(!query.exec(sql)) {
		qCritical().noquote() << query.lastError().text();
	}
}

void DatabaseManager::createSyncTable()
{
	QString sql(QString("CREATE TABLE IF NOT EXISTS "
						" %1("
						"%2 text primary key,"
						"%3 integer,"
						"%4 integer"
						");")
					.arg(SyncTable::TABLE_NAME, SyncTable::LOGIN, SyncTable::USER_SYNC, SyncTable::JOB_SYNC));

	QSqlQuery query(*this);
	if(!query.exec(sql)) {
		qCritical().noquote() << query.lastError().text();
	}
}
