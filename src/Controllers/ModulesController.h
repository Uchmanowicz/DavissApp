#pragma once

#include <QDebug>
#include <QObject>

#include <memory>

#include "UserController.h"
#include "Models/Module.h"


class ModulesController : public QObject, public IUserListener, public std::enable_shared_from_this<ModulesController>
{
	Q_OBJECT

public:
	Q_PROPERTY(QVector<Module> ui_modules MEMBER modules NOTIFY modulesChanged);

	explicit ModulesController(const std::vector<Module> &modules_,
														 const std::shared_ptr<UserController> &userController_,
														 QObject *parent = nullptr);
	~ModulesController();

	virtual void onUserChanged(const User &user) override;

//	void init();

	QVector<Module> modules;

signals:
	void modulesChanged();


private:
	std::shared_ptr<UserController> userController;
};


