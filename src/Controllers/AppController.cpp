#include "AppController.h"

AppController::AppController(const std::shared_ptr<AppManagement> &appManagement_,
															 QObject *parent)
	: QObject(parent), manager(appManagement_)
{
	setDefaultSettingsOnFirstLaunch();
}

AppController::~AppController()
{
}

void AppController::changeAppearance(const App::Appearance &appearance)
{
	DBStatus::StatusType dbStatus;
	currentApp.appearance = appearance;

	manager->update(currentApp, &dbStatus);
	emitAppChanged();
}

void AppController::changeSynchronizing(const bool &enabled)
{
	DBStatus::StatusType dbStatus;
	currentApp.sync = enabled;

	manager->update(currentApp, &dbStatus);
	emitAppChanged();
}


void AppController::emitAppChanged()
{
	for(auto &listener: Publisher::listeners) {
		if(!listener.expired()) {
			listener.lock()->onAppChanged(currentApp);
		}
	}

	emit appChanged();
}

void AppController::loadAppSettings()
{
	DBStatus::StatusType dbStatus;
	currentApp = manager->select("", &dbStatus);
	emitAppChanged();
}

void AppController::setDefaultSettingsOnFirstLaunch()
{
	DBStatus::StatusType dbStatus;

	auto records = manager->selectAll(&dbStatus);

	if(records.size()) {
		return;
	}

	manager->insert(App(), &dbStatus);
}
