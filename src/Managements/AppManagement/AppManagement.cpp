#include "AppManagement.h"

AppManagement::AppManagement(const QSqlDatabase &database)
	: m_localManager(database)
{
}

AppManagement::~AppManagement()
{
}

App AppManagement::select(const std::string &app, DBStatus::StatusType *status) const
{
	auto apps = selectAll(status);
	return apps.front();
}

std::vector<App> AppManagement::selectAll(DBStatus::StatusType *status) const
{
	Query query;
	query.query = QString("SELECT * FROM %1")
					  .arg(AppTable::TABLE_NAME)
					  .toStdString();

	auto reply = m_localManager.getRecords(query, status);

	std::vector<App> apps;
	for(const auto &app: reply) {
		apps.push_back(fetchFromRecord(app));
	}

	return apps;
}

bool AppManagement::insert(const App &app, DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("INSERT INTO %1(%2, %3) VALUES('%4', '%5');")
					  .arg(AppTable::TABLE_NAME, AppTable::APPEARANCE, AppTable::SYNC, QString::number(app.appearance), QString::number(app.sync))
					  .toStdString();

	return m_localManager.execQuery(query, status);
}

bool AppManagement::remove(const App &app, DBStatus::StatusType *status)
{
	return removeAll(status);
}

bool AppManagement::removeAll(DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("DELETE FROM %1;")
					  .arg(AppTable::TABLE_NAME)
					  .toStdString();

	return m_localManager.execQuery(query, status);
}

bool AppManagement::update(const App &app, DBStatus::StatusType *status)
{
	removeAll(status);

	return insert(app, status);
}

App AppManagement::fetchFromRecord(const QSqlRecord &record)
{
	App app;
	app.appearance = static_cast<App::Appearance>(record.field(AppTable::APPEARANCE).value().toInt(0));
	app.sync = record.field(AppTable::SYNC).value().toBool();

	return app;
}
