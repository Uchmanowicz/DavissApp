#include "JobController.h"

JobController::JobController(const std::shared_ptr<JobManagement> &jobManagement,

														 QObject *parent)
	: QObject(parent), m_jobManager(jobManagement)//, m_synchronizer(synchornizer_)
{
}

JobController::~JobController()
{
}

void JobController::onSynced()
{
	DBStatus::StatusType dbStatus;
	auto replyHistory = m_jobManager->selectAll(&dbStatus);

	if(dbStatus == DBStatus::OK) {
		history = QVector<JobHistory>::fromStdVector(replyHistory);
		calculateSummary();

		emit jobChanged();
	}
}

void JobController::update()
{
	DBStatus::StatusType dbStatus;
	auto replyHistory = m_jobManager->selectAllWeb(&dbStatus);

	if(dbStatus == DBStatus::OK) {
		history = QVector<JobHistory>::fromStdVector(replyHistory);
		calculateSummary();
	}

	emit jobChanged();
}

void JobController::fake()
{
	DBStatus::StatusType db;
	m_jobManager->remove(JobHistory("daw_1234",0), &db);

	for(auto &listener : Publisher::listeners) {
		if(!listener.expired()) {
			listener.lock().get()->onLocalUpdates(JobHistory());
		}
	}
}

void JobController::calculateSummary()
{
	long long totalDuration = 0;
	for(const auto &record: history) {
		totalDuration += record.duration - (WORKING_DAY_HOUR*60*60*1000);
	}

	timeSummary = totalDuration/1000;
}
