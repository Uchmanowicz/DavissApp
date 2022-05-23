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

#include "Resources/DatabaseManager.h"
#include "Resources/PhpApiCrud/WebDatabaseManager.h"
#include "Resources/Sqlite/SqliteDatabaseManager.h"

#include "Managements/LocalManagement.h"
#include "Managements/WebManagement.h"

#include "Controllers/AppController.h"
#include "Controllers/UserController.h"
#include "Controllers/ModulesController.h"
#include "Controllers/JobController.h"
#include "Controllers/Depot/DepotController.h"

//#include "Services/Synchronizer.h"

struct ManagementPack
{
	std::shared_ptr<AppManagement> appManager;
	std::shared_ptr<UserManagement> userManager;
	std::shared_ptr<JobManagement> jobManager;
	std::shared_ptr<Managers::DepotManager> depotManager;

	//	std::shared_ptr<SyncManagement> syncManager;
};

struct ControllerPack
{
	std::shared_ptr<AppController> appController;
	std::shared_ptr<UserController> userController;
	std::shared_ptr<ModulesController> modulesController;
	std::shared_ptr<JobController> jobController;
	std::shared_ptr<Controllers::DepotController> depotController;
};

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
	std::shared_ptr<DatabaseManager> database;
	std::shared_ptr<WebDatabaseManager> webDatabase;

	std::shared_ptr<LocalManagement> localManagement;
	std::shared_ptr<WebManagement> webManagement;

	ManagementPack managementPack;
	ControllerPack controllerPack;

	//	std::shared_ptr<Synchronizer> synchronizer;
};
#endif
