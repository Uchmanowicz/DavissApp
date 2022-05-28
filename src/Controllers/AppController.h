#pragma once

#include <QDebug>
#include <functional>

#include "Templates/Publisher.h"
#include "Templates/SynchronizerHandler.h"
#include "Common/AndroidUtils.h"
#include "Managements/AppManagement/AppManagement.h"
#include "Resources/DatabaseStatus.h"

namespace Listeners
{
	struct IAppListener
	{
		virtual ~IAppListener() { }
		virtual void onAppChanged(const App::Settings &app) = 0;
	};
}

namespace Controllers
{
	class AppController : public QObject, public Templates::Publisher<Listeners::IAppListener>
	{
		Q_OBJECT

	public:
		Q_PROPERTY(App::Settings ui_app MEMBER currentApp NOTIFY appChanged)

		explicit AppController(const std::shared_ptr<Managers::AppManagement> &appManagement_,
							   QObject *parent = nullptr);
		~AppController();

		Q_INVOKABLE void changeAppearance(const App::Settings::Appearance &appearance);
		Q_INVOKABLE void changeSynchronizing(const bool &enabled);

		void loadAppSettings();

		App::Settings currentApp;

	signals:
		void appChanged();

	private:
		std::shared_ptr<Managers::AppManagement> manager;

		void setDefaultSettingsOnFirstLaunch();
		void emitAppChanged();
	};
}
