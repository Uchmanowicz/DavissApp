#include "Synchronizer.h"

Synchronizer::Synchronizer(const std::string &dbPath_, const std::string &domain_, const std::shared_ptr<AppController> &appController_, const std::shared_ptr<UserController> &userController_)
	: dbPath(dbPath_), domain(domain_), appController(appController_), userController(userController_)
{
	reset();
}

Synchronizer::~Synchronizer()
{
	stopSynchronizing();
}

void Synchronizer::startSynchronizing()
{
	stopFlag = false;
	thread = std::thread(&Synchronizer::synchronizing, this);
}

void Synchronizer::stopSynchronizing()
{
	stopFlag = true;
	if(thread.joinable()) {
		thread.join();
	}
}

// void Synchronizer::onUserChanged(const User &user)
//{
//	if(currentUser != user) {
//		reset();
//		currentUser = user;

//		if(currentApp.sync && currentUser.isLogged() && stopFlag) {
//			startSynchronizing();
//		}else {
//			stopSynchronizing();
//		}
//	}
//}

void Synchronizer::onAppChanged(const App &app)
{
	currentApp = app;
	if(currentApp.sync && currentUser.isLogged() && stopFlag) {
		startSynchronizing();
	} else {
		stopSynchronizing();
	}
}

void Synchronizer::onLocalUpdates(const JobHistory &jobHistory)
{
	qDebug() << "LOKALZNMA ZMIANA W JOB!";
	updateLocalSyncTimestamp(&Sync::jobSync);
}

void Synchronizer::onLocalUpdates(const User &user)
{
	qDebug() << "LOKALZNMA ZMIANA W USER!";

	if(currentUser.login != user.login) {
		reset();
		currentUser = user;

		if(currentApp.sync && currentUser.isLogged() && stopFlag) {
			startSynchronizing();
		} else {
			stopSynchronizing();
		}
	}

	updateLocalSyncTimestamp(&Sync::userSync);
}

void Synchronizer::reset()
{
	std::lock_guard<std::mutex> lock(mutex_syncData);
	localSyncData = Sync();
	webSyncData = Sync();
}

void Synchronizer::synchronizing()
{
	using namespace std::chrono_literals;

	initManagers();

	std::unique_lock<std::mutex> lock_syncData(mutex_syncData);
	lock_syncData.unlock();

	DBStatus::StatusType dbStatus;
	auto timer = 10s;

	while(!stopFlag) {
		if(anyLocalUpdates) {
			this->anyLocalUpdates = false;
			syncManager->update(localSyncData, &dbStatus);
			timer = 9s;
		}

		if(timer == 10s) {
			timer = 0s;

			lock_syncData.lock();

			localSyncData = syncManager->select(currentUser.login.toStdString(), &dbStatus);
			webSyncData = syncManager->selectWeb(currentUser.login.toStdString(), &dbStatus);

			syncUser();
			syncJob();

			lock_syncData.unlock();
		}

		timer += 1s;
		std::this_thread::sleep_for(1s);
	}

	resetManagers();
}

void Synchronizer::initManagers()
{
	webDatabase = std::make_shared<WebDatabaseManager>(domain.c_str());
	database = std::make_shared<SqliteDatabaseManager>(dbPath.c_str());
	syncManager = std::make_shared<SyncManagement>(*database, webDatabase);
	userManager = std::make_shared<UserManagement>(*database, webDatabase);
	//	jobManager = std::make_shared<JobManagement>(*database, webDatabase);
}

void Synchronizer::resetManagers()
{
	//	jobManager.reset();
	userManager.reset();
	syncManager.reset();
	database.reset();
	webDatabase.reset();
}
void Synchronizer::syncUser()
{
	DBStatus::StatusType dbStatus;
	auto localData = userManager->selectAll(&dbStatus);
	auto webData = userManager->selectAllWeb(&dbStatus);

	VecResult<User> result;
	bool successUpdate = false;

	if(localSyncData.userSync > webSyncData.userSync) {
		result = compareRecords<User, QString>(&User::login, localData, webData);
		successUpdate = updateRecords<User, std::shared_ptr<UserManagement>>(userManager, &User::login, result, true);
	} else if(localSyncData.userSync < webSyncData.userSync) {
		result = compareRecords<User, QString>(&User::login, webData, localData);
		successUpdate = updateRecords<User, std::shared_ptr<UserManagement>>(userManager, &User::login, result, false);
	} else {
		successUpdate = false;
	}

	if(successUpdate) {
		qDebug() << "Sync USER!";
		mergeSyncTimestamp(&Sync::userSync);
		publishSync<Publisher<IUserSync>>();
	}
}

void Synchronizer::syncJob()
{
	DBStatus::StatusType dbStatus;
	//	auto localData = jobManager->selectAll(&dbStatus);
	//	auto webData = jobManager->selectAllWeb(&dbStatus);

	VecResult<JobHistory> result;
	bool successUpdate = false;

	//	if(localSyncData.jobSync > webSyncData.jobSync) {
	//		result = compareRecords<JobHistory, QString>(&JobHistory::login_inTimestamp, localData, webData);
	//		successUpdate = updateRecords<JobHistory, std::shared_ptr<JobManagement>>(jobManager, &JobHistory::login_inTimestamp, result, true);
	//	}else if(localSyncData.jobSync < webSyncData.jobSync) {
	//		result = compareRecords<JobHistory, QString>(&JobHistory::login_inTimestamp, webData, localData);
	//		successUpdate = updateRecords<JobHistory, std::shared_ptr<JobManagement>>(jobManager, &JobHistory::login_inTimestamp, result, false);
	//	}else {
	//		successUpdate = false;
	//	}

	if(successUpdate) {
		qDebug() << "Sync JOB!";
		mergeSyncTimestamp(&Sync::jobSync);
		publishSync<Publisher<IJobSync>>();
	}
}

void Synchronizer::updateLocalSyncTimestamp(long long Sync::*syncModule)
{
	DBStatus::StatusType dbStatus;

	std::lock_guard<std::mutex> lock(mutex_syncData);
	localSyncData.*syncModule = currentTimestamp();
	anyLocalUpdates = true;
}

void Synchronizer::mergeSyncTimestamp(long long Sync::*syncModule)
{
	DBStatus::StatusType dbStatus;

	auto currTimestamp = currentTimestamp();
	localSyncData.*syncModule = currTimestamp;
	webSyncData.*syncModule = currTimestamp;

	syncManager->update(localSyncData, &dbStatus);
	syncManager->updateWeb(webSyncData, &dbStatus);
}

template<typename Obj, typename KeyObj>
Synchronizer::VecResult<Obj> Synchronizer::compareRecords(const KeyObj Obj::*keyObj, const std::vector<Obj> &keyVector, const std::vector<Obj> &checkVector)
{
	VecResult<Obj> result;

	for(auto &key: keyVector) {
		bool updated = false;
		for(auto &check: checkVector) {
			if(check.*keyObj == key.*keyObj) {
				updated = true;
				if(check != key) {
					result.toUpdate.push_back(key);
				}
				break;
			}
		}
		if(updated == false) {
			result.toInsert.push_back(key);
		}
	}

	for(auto &check: checkVector) {
		bool matched = false;
		for(auto &key: keyVector) {
			if(key.*keyObj == check.*keyObj) {
				matched = true;
				break;
			}
		}
		if(matched == false) {
			result.toRemove.push_back(check);
		}
	}

	return result;
}

template<typename Obj, typename ManagerType, typename KeyObj>
bool Synchronizer::updateRecords(ManagerType &dbManager, const KeyObj Obj::*keyObj, const Synchronizer::VecResult<Obj> &vecResult, const bool &updateWeb)
{
	DBStatus::StatusType dbStatus = DBStatus::OK;

	for(auto &record: vecResult.toUpdate) {
		if(updateWeb) {
			dbManager->updateWeb(record, &dbStatus);
		} else {
			dbManager->update(record, &dbStatus);
		}
	}

	for(auto &record: vecResult.toInsert) {
		if(updateWeb) {
			dbManager->insertWeb(record, &dbStatus);
		} else {
			dbManager->insert(record, &dbStatus);
		}
	}

	for(auto &record: vecResult.toRemove) {
		if(updateWeb) {
			dbManager->removeWeb(record, &dbStatus);
		} else {
			dbManager->remove(record, &dbStatus);
		}
	}

	//	if(dbStatus == DBStatus::OK) {
	return true;
	//	}
}

template<typename _Publisher>
void Synchronizer::publishSync()
{
	for(auto &listener: _Publisher::listeners) {
		if(!listener.expired()) {
			listener.lock()->onSynced();
		}
	}
}
