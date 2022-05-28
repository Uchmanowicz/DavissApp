#include "AppManagement.h"

using namespace App;
using namespace Templates;
using namespace DB;

namespace Managers
{
	AppManagement::AppManagement(const QSqlDatabase &database)
		: m_localManager(database)
	{
	}

	AppManagement::~AppManagement()
	{
	}

	Settings AppManagement::select(const std::string &app, Status *status) const
	{
		auto apps = selectAll(status);
		return apps.front();
	}

	std::vector<Settings> AppManagement::selectAll(Status *status) const
	{
		DB::Query query;
		query.query = QString("SELECT * FROM %1")
						  .arg(AppTable::TABLE_NAME)
						  .toStdString();

		auto reply = m_localManager.getRecords(query, status);

		std::vector<Settings> apps;
		for(const auto &app: reply) {
			apps.push_back(fetchFromRecord(app));
		}

		return apps;
	}

	bool AppManagement::insert(const Settings &app, Status *status)
	{
		DB::Query query;
		query.query = QString("INSERT INTO %1(%2, %3) VALUES('%4', '%5');")
						  .arg(AppTable::TABLE_NAME, AppTable::APPEARANCE, AppTable::SYNC, QString::number(app.appearance), QString::number(app.sync))
						  .toStdString();

		return m_localManager.execQuery(query, status);
	}

	bool AppManagement::remove(const Settings &app, Status *status)
	{
		return removeAll(status);
	}

	bool AppManagement::removeAll(Status *status)
	{
		DB::Query query;
		query.query = QString("DELETE FROM %1;")
						  .arg(AppTable::TABLE_NAME)
						  .toStdString();

		return m_localManager.execQuery(query, status);
	}

	bool AppManagement::update(const Settings &app, Status *status)
	{
		removeAll(status);

		return insert(app, status);
	}

	Settings AppManagement::fetchFromRecord(const QSqlRecord &record)
	{
		Settings app;
		app.appearance = static_cast<Settings::Appearance>(record.field(AppTable::APPEARANCE).value().toInt(0));
		app.sync = record.field(AppTable::SYNC).value().toBool();

		return app;
	}
}
