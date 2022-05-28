#include "JobController.h"

using namespace Managers;
using namespace Job;
using namespace Listeners;

namespace Controllers
{
	JobController::JobController(const std::shared_ptr<JobManagement> &jobManagement,

								 QObject *parent)
		: QObject(parent), m_jobManager(jobManagement) //, m_synchronizer(synchornizer_)
	{
	}

	JobController::~JobController()
	{
	}

	void JobController::onSynced()
	{
		DB::Status dbStatus;
		auto replyHistory = m_jobManager->selectAll(&dbStatus);

		if(dbStatus == DB::Status::OK) {
			history = QVector<JobHistory>::fromStdVector(replyHistory);
			calculateSummary();

			emit jobChanged();
		}
	}

	void JobController::update()
	{
		DB::Status dbStatus;
		auto replyHistory = m_jobManager->selectAllWeb(&dbStatus);

		if(dbStatus == DB::Status::OK) {
			history = QVector<JobHistory>::fromStdVector(replyHistory);
			calculateSummary();
		}

		emit jobChanged();
	}

	void JobController::fake()
	{
		DB::Status db;
		m_jobManager->remove(JobHistory("daw_1234", 0), &db);

		for(auto &listener: Publisher::listeners) {
			if(!listener.expired()) {
				listener.lock().get()->onLocalUpdates(JobHistory());
			}
		}
	}

	void JobController::calculateSummary()
	{
		long long totalDuration = 0;
		for(const auto &record: history) {
			totalDuration += record.duration - (WORKING_DAY_HOUR * 60 * 60 * 1000);
		}

		timeSummary = totalDuration / 1000;
	}
}
