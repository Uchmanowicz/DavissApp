#include "Application.h"

Application::Application(int &argc, char **argv)
	: QGuiApplication(argc, argv)
{
	setOrganizationName("Daviss");
}

void Application::init()
{
	initUITypes();

	createRepositories();
	//	createSynchronizer();
	createManagers();

	createAppController();
	createUserController();
	createModulesController();
	createJobController();

	initUIEngine();
	assignListeners();
	initStartUpSettings();

	controllerPack.jobController->fake();
}

void Application::createRepositories()
{
#ifdef PROTECTOR
	Cryptographic crypto;
	domain = crypto.getDomain();
#else
	domain = "null";
#endif

	localDatabasePath = QString(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/Daviss.db")
							.toStdString();

	qDebug() << "Database LOCALIZATION: "
			 << QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/Daviss.db";

	webDatabase = std::make_shared<WebDatabaseManager>(domain.c_str());
	database = std::make_shared<SqliteDatabaseManager>(localDatabasePath.c_str());
}

void Application::createSynchronizer()
{
	//	synchronizer = std::make_shared<Synchronizer>(localDatabasePath, domain, controllerPack.appController, controllerPack.userController);
}

void Application::createManagers()
{
	localManagement = std::make_shared<LocalManagement>(*database);
	webManagement = std::make_shared<WebManagement>(webDatabase);

	managementPack.appManager = std::make_shared<AppManagement>(*database);
	managementPack.userManager = std::make_shared<UserManagement>(*database, webDatabase);
	managementPack.jobManager = std::make_shared<JobManagement>(localManagement, webManagement);
	//	managementPack.syncManager = std::make_shared<SyncManagement>(*database, webDatabase);
}

void Application::createAppController()
{
	controllerPack.appController = std::make_shared<AppController>(managementPack.appManager, this);
	mqmlEngine.rootContext()->setContextProperty(
		"appController",
		controllerPack.appController.get());
}

void Application::createUserController()
{
	controllerPack.userController = std::make_shared<UserController>(managementPack.userManager, this);
	mqmlEngine.rootContext()->setContextProperty(
		"userController",
		controllerPack.userController.get());
}

void Application::createModulesController()
{
	std::vector<Module> modules;
	modules.push_back(Module("Job", "Job Timing1", true));
	modules.push_back(Module("Job", "Job Timing2", true));
	modules.push_back(Module("Job", "Job Timing3", true));
	modules.push_back(Module("Job", "Job Timing4", true));
	modules.push_back(Module("Job", "Job Timing5", true));
	modules.push_back(Module("Job", "Job Timing6", true));
	modules.push_back(Module("Job", "Job Timing7", true));

	controllerPack.modulesController = std::make_shared<ModulesController>(
		modules,
		controllerPack.userController,
		this);

	mqmlEngine.rootContext()->setContextProperty(
		"modulesController",
		controllerPack.modulesController.get());

	mqmlEngine.rootContext()->setContextProperty("APP_VERSION", APP_VERSION);
}

void Application::createJobController()
{
	controllerPack.jobController = std::make_shared<JobController>(managementPack.jobManager, this);

	mqmlEngine.rootContext()->setContextProperty(
		"jobController",
		controllerPack.jobController.get());
}

void Application::initUITypes()
{
	qRegisterMetaType<User>("User");
	qRegisterMetaType<App>("App");
	qRegisterMetaType<Time>("Time");
	//	qRegisterMetaType<User::UserRole>("User::UserRole");
	//	qRegisterMetaType<UserController::LoginStatus>("UserCOntroller::LoginStatus");

	qmlRegisterUncreatableType<User>("ui.types", 1, 0, "User", "Error during register type User");
	qmlRegisterUncreatableType<App>("ui.types", 1, 0, "App", "Error during register type User");
	qmlRegisterUncreatableType<UserController>(
		"ui.types",
		1,
		0,
		"UserController",
		"Error during register type UserController");
}

void Application::initUIEngine()
{
	const QUrl url(QStringLiteral("qrc:/main.qml"));
	QObject::connect(
		&mqmlEngine,
		&QQmlApplicationEngine::objectCreated,
		this,
		[url](QObject *obj, const QUrl &objUrl) {
			if(!obj && url == objUrl)
				QCoreApplication::exit(-1);
		},
		Qt::QueuedConnection);

	mqmlEngine.load(url);
}

void Application::assignListeners()
{
	//	controllerPack.appController->addListener(synchronizer);

	//	controllerPack.jobController->addListener(synchronizer);
	//	controllerPack.userController->addListener(synchronizer);

	//	synchronizer->addListener(controllerPack.jobController);
	//	synchronizer->addListener(controllerPack.userController);

	controllerPack.userController->addListener(controllerPack.modulesController);
}

void Application::initStartUpSettings()
{
	controllerPack.appController->loadAppSettings();
	controllerPack.userController->signInUserIfExists();

	initAndroid();

	controllerPack.jobController->update();
}

bool Application::initAndroid()
{
#ifdef ANDROID
	auto permissGranted = QtAndroid::requestPermissionsSync(
		{"android.permission.ACCESS_NETWORK_STATE", "android.permission.INTERNET", "android.permission.READ_EXTERNAL_STORAGE", "android.permission.WRITE_EXTERNAL_STORAGE"});

	for(const auto &permission: permissGranted) {
		if(permission == QtAndroid::PermissionResult::Denied) {
			qDebug() << "BRAK POZWOLENIA";
			return false;
		}
	}

	QtAndroid::hideSplashScreen();

#endif

	return true;
}
