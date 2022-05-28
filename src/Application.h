#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#ifdef ANDROID
#include <QtAndroid>
#endif

#include "Common/Cryptographic_PROTECTED.h"

#include "Resources/ILocalDbExecutor.h"
#include "Resources/IWebDbExecutor.h"
#include "Resources/Mysql/WebMySqlDbExecutor.h"
#include "Resources/Sqlite/SqliteDbExecutor.h"

#include "Managements/LocalManagement.h"
#include "Managements/WebManagement.h"

#include "Controllers/AppController.h"
#include "Controllers/UserController.h"
#include "Controllers/ModulesController.h"
#include "Controllers/JobController.h"
#include "Controllers/Depot/DepotController.h"

//#include "Services/Synchronizer.h"

namespace Managers
{
	struct ManagementPack
	{
		std::shared_ptr<Managers::AppManagement> appManager;
		std::shared_ptr<Managers::UserManagement> userManager;
		std::shared_ptr<Managers::JobManagement> jobManager;
		std::shared_ptr<Managers::DepotManager> depotManager;

		//	std::shared_ptr<SyncManagement> syncManager;
	};
}

namespace Controllers
{
	struct ControllerPack
	{
		std::shared_ptr<Controllers::AppController> appController;
		std::shared_ptr<Controllers::UserController> userController;
		std::shared_ptr<Controllers::ModulesController> modulesController;
		std::shared_ptr<Controllers::JobController> jobController;
		std::shared_ptr<Controllers::DepotController> depotController;
	};
}

class Application : public QGuiApplication
{
	Q_OBJECT

public:
	explicit Application(int &argc, char **argv);
	void init();

private:
	void createRepositories();
	void createManagers();
	void createAppController();
	void createUserController();
	void createModulesController();
	void createJobController();
	void createDepotController();
	void createSynchronizer();

	void initUITypes();
	void initUIEngine();
	void initStartUpSettings();
	bool initAndroid();

	void assignListeners();

	QQmlApplicationEngine mqmlEngine;

	std::string localDatabasePath;
	std::string domain;
	std::shared_ptr<DB::ILocalDbExecutor> dbExecutor;
	std::shared_ptr<DB::IWebDbExecutor> webDbExecutor;

	std::shared_ptr<DB::LocalManagement> localManagement;
	std::shared_ptr<WebManagement> webManagement;

	Managers::ManagementPack managementPack;
	Controllers::ControllerPack controllerPack;

	//	std::shared_ptr<Synchronizer> synchronizer;
};
#endif
