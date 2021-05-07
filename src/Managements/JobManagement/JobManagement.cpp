#include "JobManagement.h"

JobManagement::JobManagement(const std::shared_ptr<LocalManagement> &localManagement, const std::shared_ptr<WebManagement> &webManagement)
	:  localManager(localManagement), webManager(webManagement)
{
}

JobManagement::~JobManagement()
{
}

JobHistory JobManagement::select(const std::string &login_inTimestmap, DBStatus::StatusType *status ) const
{
	Query query;
	query.query = QString("SELECT * FROM %1 WHERE %2 = '%3';")
			.arg(JobHistoryTable::TABLE_NAME, JobHistoryTable::LOGIN_TIMESTAMP, login_inTimestmap.c_str()).toStdString();

	auto reply = localManager->getRecord(query, status);

	if(!reply.isEmpty()) {
		return fetchFromRecord(reply);
	}

	return JobHistory();
}

std::vector<JobHistory> JobManagement::selectAll(DBStatus::StatusType *status) const
{
	Query query;
	query.query = QString("SELECT * FROM %1 WHERE %2 = '%3';")
			.arg(JobHistoryTable::TABLE_NAME, JobHistoryTable::LOGIN, UserSession::getInstance().getUser().login).toStdString();

	auto reply = localManager->getRecords(query, status);

	std::vector<JobHistory> jobHistorys;
	for(const auto &jobHistory: reply) {
		jobHistorys.push_back(fetchFromRecord(jobHistory));
	}

	return jobHistorys;
}

bool JobManagement::insert(const JobHistory &jobHistory, DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("INSERT INTO %1(%2, %3, %4, %5) VALUES('%6', '%7', '%8', '%9');")
			.arg(JobHistoryTable::TABLE_NAME, JobHistoryTable::LOGIN_TIMESTAMP, JobHistoryTable::OUT_TIMESTAMP, JobHistoryTable::DURATION,
					 JobHistoryTable::LOGIN)
			.arg(jobHistory.login_inTimestamp, QString::number(jobHistory.outTimestamp), QString::number(jobHistory.duration), UserSession::getInstance().getUser().login).toStdString();

	auto success = localManager->execQuery(query, status);
	return  success;
}

bool JobManagement::remove(const JobHistory &jobHistory, DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("DELETE FROM %1 WHERE %2 = '%3';")
			.arg(JobHistoryTable::TABLE_NAME, JobHistoryTable::LOGIN_TIMESTAMP, jobHistory.login_inTimestamp).toStdString();

	auto success = localManager->execQuery(query, status);
	return  success;
}

bool JobManagement::removeAll(DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("DELETE FROM %1 WHERE %2 = '%3';")
			.arg(JobHistoryTable::TABLE_NAME, JobHistoryTable::LOGIN, UserSession::getInstance().getUser().login).toStdString();

	auto success = localManager->execQuery(query, status);
	return  success;
}

bool JobManagement::update(const JobHistory &jobHistory, DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("UPDATE %1 SET %2='%3', %4='%5', %6='%7', %8='%9' WHERE %10 = '%11';")
			.arg(JobHistoryTable::TABLE_NAME, JobHistoryTable::LOGIN_TIMESTAMP, jobHistory.login_inTimestamp, JobHistoryTable::OUT_TIMESTAMP, QString::number(jobHistory.outTimestamp))
			.arg(JobHistoryTable::DURATION, QString::number(jobHistory.duration), JobHistoryTable::LOGIN, UserSession::getInstance().getUser().login).toStdString();


	auto success = localManager->execQuery(query, status);
	return  success;
}

JobHistory JobManagement::selectWeb(const std::string &login_inTimestmap, DBStatus::StatusType *status) const
{
	Query query;
	query.query = QString("/%2/%3").arg(JobHistoryTable::TABLE_NAME, login_inTimestmap.c_str()).toStdString();
	query.type = Query::Type::SELECT;

	auto reply = webManager->getRecord(query, status);

	if(!reply.empty()) {
		return fetchFromRecordWeb(reply);
	}

	return JobHistory();
}

std::vector<JobHistory> JobManagement::selectAllWeb(DBStatus::StatusType *status) const
{
	Query query;
	query.query = QString("/%1?filter=%2,eq,%3").arg(JobHistoryTable::TABLE_NAME, JobHistoryTable::LOGIN,
																									 UserSession::getInstance().getUser().login).toStdString();
	query.type = Query::Type::SELECT;

	auto reply = webManager->getRecords(query, status);

	std::vector<JobHistory> jobHistorys;
	for(auto const &jobHistoryObj: reply) {
		jobHistorys.push_back(fetchFromRecordWeb(jobHistoryObj));
	}

	return jobHistorys;
}

bool JobManagement::insertWeb(const JobHistory &jobHistory, DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("/%1").arg(JobHistoryTable::TABLE_NAME).toStdString();
	query.body = toJsonWeb(jobHistory);
	query.type = Query::Type::INSERT;

	return webManager->execQuery(query, status);
}

bool JobManagement::removeWeb(const JobHistory &jobHistory, DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("/%1/%2").arg(JobHistoryTable::TABLE_NAME, jobHistory.login_inTimestamp).toStdString();
	query.type = Query::Type::REMOVE;

	return webManager->execQuery(query, status);
}

bool JobManagement::removeAllWeb(DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("/%1?filter=%2,eq,%3").arg(JobHistoryTable::TABLE_NAME, JobHistoryTable::LOGIN, UserSession::getInstance().getUser().login).toStdString();
	query.type = Query::Type::REMOVE;

	return webManager->execQuery(query, status);
}

bool JobManagement::updateWeb(const JobHistory &jobHistory, DBStatus::StatusType *status)
{
	Query query;
	query.query = QString("/%2/%3").arg(JobHistoryTable::TABLE_NAME, jobHistory.login_inTimestamp).toStdString();
	query.body = toJsonWeb(jobHistory);
	query.type = Query::Type::UPDATE;

	return webManager->execQuery(query, status);
}

long long JobManagement::splitLoginTimestamp(const std::string &login_inTimestamp)
{
	auto strings = QString(login_inTimestamp.c_str()).split("_");
	return strings.at(1).toLongLong();
}

std::string toLoginTimestamp(const long long &inTimestamp)
{
	std::string res(UserSession::getInstance().getUser().login.toStdString());
	res.append("_");
	res.append(std::to_string(inTimestamp));
	return res;
}

JobHistory JobManagement::fetchFromRecord(const QSqlRecord &record)
{
	JobHistory JobHistory;
	JobHistory.login_inTimestamp = record.field(JobHistoryTable::LOGIN_TIMESTAMP).value().toString();
	JobHistory.inTimestamp = splitLoginTimestamp(JobHistory.login_inTimestamp.toStdString());
	JobHistory.outTimestamp = record.field(JobHistoryTable::OUT_TIMESTAMP).value().toLongLong();
	JobHistory.duration = record.field(JobHistoryTable::DURATION).value().toLongLong();
	return JobHistory;
}

JobHistory JobManagement::fetchFromRecordWeb(const QJsonObject &records)
{
	JobHistory JobHistory;
	JobHistory.login_inTimestamp = records[JobHistoryTable::LOGIN_TIMESTAMP].toString();
	JobHistory.inTimestamp = splitLoginTimestamp(JobHistory.login_inTimestamp.toStdString());
	JobHistory.outTimestamp = records[JobHistoryTable::OUT_TIMESTAMP].toDouble();
	JobHistory.duration = records[JobHistoryTable::DURATION].toDouble();
	return JobHistory;
}

std::string JobManagement::toJsonWeb(const JobHistory &jobHistory)
{
	QJsonObject obj;
	obj.insert(JobHistoryTable::LOGIN_TIMESTAMP,  jobHistory.login_inTimestamp);
	obj.insert(JobHistoryTable::OUT_TIMESTAMP, jobHistory.outTimestamp);
	obj.insert(JobHistoryTable::DURATION, static_cast<double>(jobHistory.duration));
	obj.insert(JobHistoryTable::LOGIN, UserSession::getInstance().getUser().login);
	QJsonDocument doc(obj);

	return doc.toJson(QJsonDocument::Compact).toStdString();
}
