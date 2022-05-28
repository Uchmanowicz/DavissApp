#include "DepotController.h"

using namespace Depot;
using namespace Managers;
using namespace Person;
using namespace DB;

namespace Controllers
{
	DepotController::DepotController(const std::shared_ptr<DepotManager> &_depotManager,
									 QObject *parent)
		: QObject(parent), depotManager(_depotManager)
	{
	}

	void DepotController::loadDepotItems()
	{
		Status dbStatus;
		auto items = depotManager->selectAll(&dbStatus);
		depotItems = QVector<Depot::Item>::fromStdVector(items);

		QMap<int, QSet<QString>> tmp;
		for(const auto &item: depotItems) {
			auto catList = item.category.split("/");
			int levelCounter = 0;
			for(const auto &subCat: catList) {
				tmp[levelCounter].insert(subCat);
				levelCounter++;
			}
		}

		int levelCounter = 0;
		for(const auto &i: tmp) {
			QVariantList list;
			for(const auto &j: i) {
				list.push_back(j);
			}
			categoriesLevelMap.insert(QString::number(levelCounter), list);
			levelCounter++;
		}

		emitDepotChanged();
	}

	void DepotController::onUserChanged(const User &user)
	{
		loadDepotItems();
	}

	void DepotController::addItem(const QString &name, const QString &category)
	{
		auto user = UserSession::getInstance().getUser();
		auto item = Depot::Item(user.login, category, 1, "pcs", "", {});

		Status dbStatus;
		depotManager->insert(item, &dbStatus);
		loadDepotItems();
		emitDepotChanged();
	}

	void DepotController::emitDepotChanged()
	{
		for(auto &listener: Publisher<Listeners::IDepotListener>::listeners) {
			if(!listener.expired()) {
				listener.lock().get()->onDepotChanged(depotItems);
			}
		}

		emit depotChanged();
	}
}
