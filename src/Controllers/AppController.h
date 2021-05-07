#pragma once

#include <QDebug>
#include <functional>

#include "Templates/Publisher.h"
#include "Templates/SynchronizerHandler.h"
#include "Common/AndroidUtils.h"
#include "Managements/AppManagement/AppManagement.h"
#include "Resources/DatabaseStatus.h"

struct IAppListener
{
	virtual ~IAppListener() {}
	virtual void onAppChanged(const App &app) = 0;
};

class AppController : public QObject, public Publisher<IAppListener>
{
	Q_OBJECT

public:
	Q_PROPERTY(App ui_app MEMBER currentApp NOTIFY appChanged)

	explicit AppController(const std::shared_ptr<AppManagement> &appManagement_,
													QObject *parent = nullptr);
	~AppController();

	Q_INVOKABLE void changeAppearance(const App::Appearance &appearance);
	Q_INVOKABLE void changeSynchronizing(const bool &enabled);

	void loadAppSettings();

	App currentApp;

signals:
	void appChanged();

private:
	std::shared_ptr<AppManagement> manager;

	void setDefaultSettingsOnFirstLaunch();
	void emitAppChanged();
};


