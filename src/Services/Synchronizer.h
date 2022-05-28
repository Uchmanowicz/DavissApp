#pragma once

#include <QDebug>
#include <thread>
#include <memory>
#include <chrono>

#include "Controllers/AppController.h"
#include "Controllers/UserController.h"

#include "Resources/Sqlite/SqliteDbExecutor.h"
#include "Resources/Mysql/WebMySqlDbExecutor.h"

#include "Managements/SyncManagement/SyncManagement.h"
//#include "Managements/UserManagement/UserManagement.h"
#include "Managements/JobManagement/JobManagement.h"

#include "Templates/SynchronizerHandler.h"
#include "SynchronizerPublisherList.h"
#include "SynchronizerListenerList.h"

/// @brief Database cachce parameters for easier synchornizing local and web databases.
struct DatabaseCacheParameters
{
	bool isLocalUpdates = true;
	bool isWebUpdates = false;
	std::vector<std::string> keys;

	DatabaseCacheParameters() {};
};

namespace Services
{
	class Synchronizer : public Sync::SynchronizerPublisherList, public Sync::SynchronizerListenerList
	{
	public:
		explicit Synchronizer(const std::string &dbPath_, const std::string &domain_, const std::shared_ptr<Controllers::AppController> &appController_, const std::shared_ptr<Controllers::UserController> &userController_);
		~Synchronizer();

		void startSynchronizing();
		void stopSynchronizing();

		//	void onUserChanged(const User &user) override;
		void onAppChanged(const App::Settings &app) override;
		void onLocalUpdates(const Job::JobHistory &jobHistory) override;
		void onLocalUpdates(const Person::User &user) override;

	signals:

	private:
		std::thread thread;
		std::mutex mutex_syncData;
		bool stopFlag = true;
		void synchronizing();
		void initManagers();
		void resetManagers();

		void reset();

		std::string dbPath;
		std::string domain;
		std::shared_ptr<DB::ILocalDbExecutor> database;
		std::shared_ptr<DB::IWebDbExecutor> webDatabase;

		Person::User currentUser;
		App::Settings currentApp;

		Sync::Entities localSyncData;
		Sync::Entities webSyncData;

		/// @brief Chache for matching database and thier parameters
		/// @param First - ptr on handler for database manager.
		/// @param Second - database chache parameters.
		//	std::map<std::weak_ptr<SynchronizerHandler>, DatabaseCacheParameters> cacheDatabases;

		//	std::shared_ptr<SynchronizerHandler> syncHandler;
		std::shared_ptr<Controllers::AppController> appController;
		std::shared_ptr<Controllers::UserController> userController;

		std::shared_ptr<Managers::SyncManagement> syncManager;
		std::shared_ptr<Managers::UserManagement> userManager;
		std::shared_ptr<Managers::JobManagement> jobManager;

		void syncUser();
		void syncJob();

		template<typename Obj>
		struct VecResult
		{
			std::vector<Obj> toUpdate;
			std::vector<Obj> toInsert;
			std::vector<Obj> toRemove;
		};

		bool anyLocalUpdates = false;
		void updateLocalSyncTimestamp(long long Sync::Entities::*syncModule);
		void mergeSyncTimestamp(long long Sync::Entities::*syncModule);

		template<typename _Publisher>
		void publishSync();

		template<typename Obj, typename KeyObj>
		VecResult<Obj> compareRecords(const KeyObj Obj::*keyObj, const std::vector<Obj> &keyVector, const std::vector<Obj> &checkVector);

		template<typename Obj, typename ManagerType, typename KeyObj>
		bool updateRecords(ManagerType &dbManager, const KeyObj Obj::*keyObj, const VecResult<Obj> &vecResult, const bool &updateWeb);

		//	ManagementPack managementPack;
	};
}
