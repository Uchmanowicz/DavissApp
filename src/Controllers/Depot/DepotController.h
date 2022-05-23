#pragma once

#include <QDebug>
#include <functional>
#include <QSet>

#include "Templates/Publisher.h"
//#include "Templates/SynchronizerHandler.h"
#include "Common/UserSession.h"
#include "Managements/Depot/DepotManager.h"
#include "Resources/DatabaseStatus.h"

using namespace Depot;
using namespace Managers;

namespace Listeners
{
	class IDepotListener
	{
	public:
		virtual ~IDepotListener() {};
		virtual void onDepotChanged(const QVector<Depot::Item> &depotItems) = 0;
	};
}

namespace Controllers
{

	class DepotController : public QObject, public Publisher<Listeners::IDepotListener>, public IUserListener
	{
		Q_OBJECT

	public:
		Q_PROPERTY(QVector<Depot::Item> ui_depotItems MEMBER depotItems NOTIFY depotChanged)
		Q_PROPERTY(QVariantMap ui_categoriesLevelMap MEMBER categoriesLevelMap NOTIFY depotChanged)

		explicit DepotController(const std::shared_ptr<DepotManager> &_depotManager,
								 QObject *parent = nullptr);
		~DepotController() = default;

		virtual void onUserChanged(const User &user) override;

		Q_INVOKABLE void addItem(const QString &name, const QString &category);

		QVector<Depot::Item> depotItems;
		QVariantMap categoriesLevelMap;

	signals:
		void depotChanged();

	private:
		std::shared_ptr<DepotManager> depotManager;

		void loadDepotItems();
		void emitDepotChanged();
	};
}