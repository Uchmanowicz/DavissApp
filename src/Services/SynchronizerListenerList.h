#pragma once

#include "Templates/SynchronizerHandler.h"
#include "Models/JobHistory.h"
#include "Models/User.h"
#include "Controllers/AppController.h"

namespace Sync
{
	struct SynchronizerListenerList : public Listeners::IAppListener, public Listeners::ILocalSyncUpdates<Job::JobHistory>, public Listeners::ILocalSyncUpdates<Person::User>
	{
		virtual ~SynchronizerListenerList() {};
		virtual void onAppChanged(const App::Settings &app) = 0;
		virtual void onLocalUpdates(const Job::JobHistory &jobHistory) = 0;
		virtual void onLocalUpdates(const Person::User &user) = 0;
	};
}
