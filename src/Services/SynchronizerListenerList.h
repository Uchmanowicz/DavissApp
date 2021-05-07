#pragma once

#include "Templates/SynchronizerHandler.h"
#include "Models/JobHistory.h"
#include "Models/User.h"
#include "Controllers/AppController.h"

struct SynchronizerListenerList : public IAppListener, public ILocalSyncUpdates<JobHistory>, public ILocalSyncUpdates<User>
{
	virtual ~SynchronizerListenerList() {};
	virtual void onAppChanged(const App &app) = 0;
	virtual void onLocalUpdates(const JobHistory &jobHistory) = 0;
	virtual void onLocalUpdates(const User &user) = 0;
};


