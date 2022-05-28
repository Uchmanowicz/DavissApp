#include "AppController.h"

using namespace Managers;
using namespace App;
using namespace DB;

namespace Controllers
{
	AppController::AppController(const std::shared_ptr<AppManagement> &appManagement_,
								 QObject *parent)
		: QObject(parent), manager(appManagement_)
	{
		setDefaultSettingsOnFirstLaunch();
	}

	AppController::~AppController()
	{
	}

	void AppController::changeAppearance(const Settings::Appearance &appearance)
	{
		Status dbStatus;
		currentApp.appearance = appearance;

		manager->update(currentApp, &dbStatus);
		emitAppChanged();
	}

	void AppController::changeSynchronizing(const bool &enabled)
	{
		Status dbStatus;
		currentApp.sync = enabled;

		manager->update(currentApp, &dbStatus);
		emitAppChanged();
	}

	void AppController::emitAppChanged()
	{
		for(auto &listener: listeners) {
			if(!listener.expired()) {
				listener.lock()->onAppChanged(currentApp);
			}
		}

		emit appChanged();
	}

	void AppController::loadAppSettings()
	{
		Status dbStatus;
		currentApp = manager->select("", &dbStatus);
		emitAppChanged();
	}

	void AppController::setDefaultSettingsOnFirstLaunch()
	{
		Status dbStatus;

		auto records = manager->selectAll(&dbStatus);

		if(records.size()) {
			return;
		}

		manager->insert(Settings(), &dbStatus);
	}
}
