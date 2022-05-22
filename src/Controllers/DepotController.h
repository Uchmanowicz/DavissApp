#pragma once

#include <QDebug>
#include <functional>

#include "Templates/Publisher.h"
//#include "Templates/SynchronizerHandler.h"
//#include "Common/AndroidUtils.h"
//#include "Common/Cryptographic_PROTECTED.h"
//#include "Common/ImageConverter.h"
#include "Common/UserSession.h"
#include "Managements/DepotManager/DepotManager.h"
#include "Resources/DatabaseStatus.h"

class IDepotListener
{
public:
	virtual ~IDepotListener() {};
	virtual void onDepotChanged(const QVector<DepotItem> &depotItems) = 0;
};

class DepotController : public QObject, public Publisher<IDepotListener>, public IUserListener
{
	Q_OBJECT

public:
	Q_PROPERTY(QVector<DepotItem> ui_depotItems MEMBER depotItems NOTIFY depotChanged)

	explicit DepotController(const std::shared_ptr<DepotManager> &_depotManager,
							 QObject *parent = nullptr);
	~DepotController() = default;

	virtual void onUserChanged(const User &user) override;

	QVector<DepotItem> depotItems;

signals:
	void depotChanged();

private:
	std::shared_ptr<DepotManager> depotManager;

	void loadDepotItems();
	void emitDepotChanged();
};
