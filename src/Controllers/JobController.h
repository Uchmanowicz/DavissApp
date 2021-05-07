#pragma once

#include <functional>

#include <QDebug>
#include <QVector>

#include "Models/Module.h"

#include "Models/JobHistory.h"
#include "Models/Time.h"
#include "Managements/JobManagement/JobManagement.h"
#include "Templates/SynchronizerHandler.h"
//#include "Services/Synchronizer.h"


class JobController : public QObject, public Publisher<ILocalSyncUpdates<JobHistory>>, public IJobSync
{
	Q_OBJECT

	static constexpr int WORKING_DAY_HOUR = 8;

public:
	Q_PROPERTY(QVector<JobHistory> ui_history MEMBER history NOTIFY jobChanged)
	Q_PROPERTY(int ui_timeSummary MEMBER timeSummary NOTIFY jobChanged)

	explicit JobController(const std::shared_ptr<JobManagement> &jobManagement,

													QObject *parent = nullptr);
	~JobController();

	void onSynced() override;


	void fake();
	void update();

	QVector<JobHistory> history;
	int timeSummary;

	template<typename Ab>
	void test(Ab t) {

	}

signals:
	void jobChanged();

private:
	std::shared_ptr<JobManagement> m_jobManager;
//	std::shared_ptr<SynchronizerHandler> m_synchronizer;

	void calculateSummary();
};


