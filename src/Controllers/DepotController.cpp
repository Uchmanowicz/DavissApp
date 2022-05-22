#include "DepotController.h"

DepotController::DepotController(const std::shared_ptr<DepotManager> &_depotManager,
								 QObject *parent)
	: QObject(parent), depotManager(_depotManager)
{
}

void DepotController::loadDepotItems()
{
	DBStatus::StatusType dbStatus;
	auto items = depotManager->selectAll(&dbStatus);
	depotItems = QVector<DepotItem>::fromStdVector(items);

	emitDepotChanged();
}

void DepotController::onUserChanged(const User &user)
{
	loadDepotItems();
}

void DepotController::emitDepotChanged()
{
	for(auto &listener: Publisher<IDepotListener>::listeners) {
		if(!listener.expired()) {
			listener.lock().get()->onDepotChanged(depotItems);
		}
	}

	emit depotChanged();
}
