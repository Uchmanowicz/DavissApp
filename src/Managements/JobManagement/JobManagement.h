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

class JobManagement : public CRUDLocalManagement<std::string, JobHistory>, public CRUDWebManagement<std::string, JobHistory>
{
public:
	JobManagement(const std::shared_ptr<LocalManagement> &localManagement, const std::shared_ptr<WebManagement> &webManagement);
	~JobManagement();

	JobHistory select(const std::string &login_inTimestmap, DBStatus::StatusType *status = nullptr) const override;
	std::vector<JobHistory> selectAll(DBStatus::StatusType *status = nullptr) const override;
	bool insert(const JobHistory &jobHistory, DBStatus::StatusType *status = nullptr) override;
	bool remove(const JobHistory &jobHistory, DBStatus::StatusType *status = nullptr) override;
	bool removeAll(DBStatus::StatusType *status = nullptr) override;
	bool update(const JobHistory &jobHistory, DBStatus::StatusType *status = nullptr) override;

	JobHistory selectWeb(const std::string &login_inTimestmap, DBStatus::StatusType *status = nullptr) const override;
	std::vector<JobHistory> selectAllWeb(DBStatus::StatusType *status = nullptr) const override;
	bool insertWeb(const JobHistory &jobHistory, DBStatus::StatusType *status = nullptr) override;
	bool removeWeb(const JobHistory &jobHistory, DBStatus::StatusType *status = nullptr) override;
	bool removeAllWeb(DBStatus::StatusType *status = nullptr) override;
	bool updateWeb(const JobHistory &jobHistory, DBStatus::StatusType *status = nullptr) override;

private:
	std::shared_ptr<LocalManagement> localManager;
	std::shared_ptr<WebManagement> webManager;

	static JobHistory fetchFromRecord(const QSqlRecord &record);
	static JobHistory fetchFromRecordWeb(const QJsonObject &records);
	static std::string toJsonWeb(const JobHistory &jobHistory);

	static long long splitLoginTimestamp(const std::string &login_inTimestamp);
	static std::string toLoginTimestamp(const long long &inTimestamp);
};
