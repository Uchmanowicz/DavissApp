#pragma once

#include <string>
#include <QtSql>

#include "Common/Utility.h"
#include "Managements/LocalManagement.h"
#include "Templates/CRUDManagement.h"
#include "Templates/QueryRespository.h"
#include "Models/App.h"
#include "AppTable.h"

namespace Managers
{
	class AppManagement : public Templates::CRUDLocalManagement<std::string, App::Settings>
	{
	public:
		AppManagement(const QSqlDatabase &database);
		~AppManagement();

		App::Settings select(const std::string &app, DB::Status *status = nullptr) const override;
		std::vector<App::Settings> selectAll(DB::Status *status = nullptr) const override;
		bool insert(const App::Settings &app, DB::Status *status = nullptr) override;
		bool remove(const App::Settings &app, DB::Status *status = nullptr) override;
		bool removeAll(DB::Status *status = nullptr) override;
		bool update(const App::Settings &app, DB::Status *status = nullptr) override;

	private:
		DB::LocalManagement m_localManager;

		static App::Settings fetchFromRecord(const QSqlRecord &record);
	};
}
