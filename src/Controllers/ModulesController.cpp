#include "ModulesController.h"

using namespace Listeners;
using namespace Person;
using namespace Modules;

namespace Controllers
{
	ModulesController::ModulesController(const std::vector<Module> &modules_,
										 const std::shared_ptr<UserController> &userController_,
										 QObject *parent)
		: QObject(parent), modules(QVector<Module>(modules_.begin(), modules_.end())), userController(userController_)
	{
	}

	ModulesController::~ModulesController()
	{
	}

	void ModulesController::onUserChanged(const User &user)
	{
		for(auto it = user.modulesEnabled.begin(); it != user.modulesEnabled.end(); ++it) {
			for(auto &mod: modules) {
				if(mod.id == it.key()) {
					mod.isEnabled = it.value();
					break;
				}
			}
		}

		emit modulesChanged();
	}

	// void ModulesController::init()
	//{
	//	userController.get()->addListener(shared_from_this());
	// }

}
