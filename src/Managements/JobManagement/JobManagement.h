#pragma once

#include <QtSql>
#include <QString>

#include "Common/Utility.h"
#include "Common/UserSession.h"
#include "Managements/WebManagement.h"
#include "Managements/LocalManagement.h"
#include "Templates/CRUDManagement.h"
#include "Templates/SynchronizerHandler.h"
//#include "Services/Synchronizer.h"
#include "Models/JobHistory.h"
#include "JobHistoryTable.h"

namespace Managers
{
	class JobManagement : public Templates::CRUDLocalManagement<std::string, Job::JobHistory>, public Templates::CRUDWebManagement<std::string, Job::JobHistory>
	{
	public:
		JobManagement(const std::shared_ptr<DB::LocalManagement> &localManagement, const std::shared_ptr<WebManagement> &webManagement);
		~JobManagement();

		Job::JobHistory select(const std::string &login_inTimestmap, DB::Status *status = nullptr) const override;
		std::vector<Job::JobHistory> selectAll(DB::Status *status = nullptr) const override;
		bool insert(const Job::JobHistory &jobHistory, DB::Status *status = nullptr) override;
		bool remove(const Job::JobHistory &jobHistory, DB::Status *status = nullptr) override;
		bool removeAll(DB::Status *status = nullptr) override;
		bool update(const Job::JobHistory &jobHistory, DB::Status *status = nullptr) override;

		Job::JobHistory selectWeb(const std::string &login_inTimestmap, DB::Status *status = nullptr) const override;
		std::vector<Job::JobHistory> selectAllWeb(DB::Status *status = nullptr) const override;
		bool insertWeb(const Job::JobHistory &jobHistory, DB::Status *status = nullptr) override;
		bool removeWeb(const Job::JobHistory &jobHistory, DB::Status *status = nullptr) override;
		bool removeAllWeb(DB::Status *status = nullptr) override;
		bool updateWeb(const Job::JobHistory &jobHistory, DB::Status *status = nullptr) override;

	private:
		std::shared_ptr<DB::LocalManagement> localManager;
		std::shared_ptr<WebManagement> webManager;

		static Job::JobHistory fetchFromRecord(const QSqlRecord &record);
		static Job::JobHistory fetchFromRecordWeb(const QJsonObject &records);
		static std::string toJsonWeb(const Job::JobHistory &jobHistory);

		static long long splitLoginTimestamp(const std::string &login_inTimestamp);
		static std::string toLoginTimestamp(const long long &inTimestamp);
	};
}
