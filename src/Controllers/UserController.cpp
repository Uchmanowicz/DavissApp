#include "UserController.h"

using namespace Managers;
using namespace Listeners;
using namespace Person;

namespace Controllers
{
	UserController::UserController(const std::shared_ptr<UserManagement> &userManagement_,
								   QObject *parent)
		: QObject(parent), userManager(userManagement_)
	{
		addGuestUser();
	}

	UserController::~UserController()
	{
	}

	void UserController::onSynced()
	{
		DB::Status dbStatus;
		auto replyUser = userManager->select(currentUser.login.toStdString(), &dbStatus);

		if(dbStatus == DB::Status::OK) {
			if(replyUser.isBlocked) {
			}

			replyUser.isAlwaysLogged = currentUser.isAlwaysLogged;
			currentUser = replyUser;
			UserSession::getInstance().setUser(currentUser);

			for(auto &listener: Publisher<IUserListener>::listeners) {
				if(!listener.expired()) {
					listener.lock().get()->onUserChanged(currentUser);
				}
			}

			emit userChanged();
		}
	}

	bool UserController::isLogged()
	{
		return currentUser.isLogged();
	}

	void UserController::signIn(const QString &login, const QString &password, const bool &alwaysLogged, const bool &isHashedPassword)
	{
		std::string hashedPassword;

#ifdef PROTECTOR
		Cryptographic crypto;
		if(!isHashedPassword) {
			hashedPassword = crypto.convertToHash(password.toStdString());
		} else {
			hashedPassword = password.toStdString();
		}
#else
		hashedPassword = "null";
#endif

		DB::Status dbStatus = DB::Status::OK;
		User user = userManager.get()->select(login.toStdString(), &dbStatus);

		if(user.login.isEmpty()) {
			UserSession::getInstance().setUser(User(login, hashedPassword.c_str(), ""));
			user = userManager.get()->selectWeb(login.toStdString(), &dbStatus);
			if(dbStatus == DB::Status::OK && validateUserCredentails(hashedPassword, user.password.toStdString())) {
				signOutGusetUser();
				user.isAlwaysLogged = alwaysLogged;
				currentUser = user;
				userManager->insert(currentUser, &dbStatus);
			}
		} else if(!validateUserCredentails(hashedPassword, user.password.toStdString())) {
			dbStatus = DB::Status::ERR_USER_WRONG;
		} else {
			signOutGusetUser();
			user.isAlwaysLogged = alwaysLogged;
			currentUser = user;
			userManager->update(currentUser, &dbStatus);
		}

		emitUserChanged();
		emitUserStatus(dbStatus, std::bind(&UserController::signInResult, this, std::placeholders::_1));
	}

	void UserController::signOut()
	{
		DB::Status dbStatus;
		currentUser.isAlwaysLogged = false;
		userManager.get()->update(currentUser, &dbStatus);
		signInGusetUser();

		UserSession::getInstance().deActivate();
		emitUserChanged();
	}

	void UserController::changeAlwaysSigned(const bool &enabled)
	{
		if(!isLogged()) {
			return;
		}

		DB::Status dbStatus;
		currentUser.isAlwaysLogged = enabled;
		userManager->update(currentUser, &dbStatus);
		emitUserChanged();
	}

	void UserController::changePassword(const QString &password)
	{
		if(!isLogged()) {
			return;
		}

		std::string hashedPassword;

#ifdef PROTECTOR
		Cryptographic crypto;
		hashedPassword = crypto.convertToHash(password.toStdString());
#else
		hashedPassword = "null";
#endif

		DB::Status dbStatus;
		User newUser = currentUser;
		newUser.password = hashedPassword.c_str();
		userManager->updateWeb(newUser, &dbStatus);

		emitUserStatus(dbStatus, std::bind(&UserController::userPasswordChanged, this, std::placeholders::_1));

		if(dbStatus == DB::Status::OK) {
			currentUser = newUser;
			userManager->update(currentUser, &dbStatus);
			emitUserChanged();
		}
	}

	void UserController::changeName(const QString &name)
	{
		if(!isLogged()) {
			return;
		}

		DB::Status dbStatus;
		User newUser = currentUser;
		newUser.name = name;

		userManager->update(newUser, &dbStatus);
		userManager->updateWeb(newUser, &dbStatus);
		currentUser = newUser;
		emitUserStatus(dbStatus, std::bind(&UserController::userNameChanged, this, std::placeholders::_1));
		emitUserChanged();
	}

	QString UserController::loadAvatar(const QString &filename)
	{
		std::string realPath = filename.toStdString();

#ifdef ANDROID
		realPath = AndroidUtils::getRealFilePath(realPath);
#endif

		auto blob = ImageConverter::convertToBLOB(realPath, ImageConverter::JPEG, 1000);
		return blob.c_str();
	}

	void UserController::changeAvatar(const QString &avatar)
	{
		if(!isLogged()) {
			return;
		}

		DB::Status dbStatus;
		User newUser = currentUser;
		newUser.avatar = avatar;
		userManager->update(newUser, &dbStatus);
		currentUser = newUser;
		emitUserStatus(dbStatus, std::bind(&UserController::userAvatarChanged, this, std::placeholders::_1));
		emitUserChanged();
	}

	QString UserController::convertPasswordToHash(const QString &password)
	{
		std::string hashedPassword;

#ifdef PROTECTOR
		Cryptographic crypto;
		hashedPassword = crypto.convertToHash(password.toStdString());
#else
		hashedPassword = "null";
#endif

		return hashedPassword.c_str();
	}

	void UserController::signInUserIfExists()
	{
		DB::Status dbStatus;
		auto users = userManager->selectAll(&dbStatus);

		for(const auto &userDB: users) {
			if(userDB.isAlwaysLogged && userDB.userRole != User::UserRole::Guest) {
				signIn(userDB.login, userDB.password, userDB.isAlwaysLogged, true);
				return;
			}
		}

		signInGusetUser();
	}

	void UserController::addGuestUser()
	{
		DB::Status dbStatus;
		User user = userManager->select("Guest", &dbStatus);

		if(user.login.isEmpty()) {
			user = User("Guest", "Guest", "Guest", User::UserRole::Guest, false, "", true);
			userManager.get()->insert(user, &dbStatus);
		}
	}

	void UserController::signInGusetUser()
	{
		DB::Status dbStatus;
		User guestUser = userManager->select("Guest", &dbStatus);
		guestUser.isAlwaysLogged = true;
		userManager->update(guestUser, &dbStatus);
		currentUser = guestUser;

		emitUserChanged();
	}

	void UserController::signOutGusetUser()
	{
		DB::Status dbStatus;
		User guestUser = userManager->select("Guest", &dbStatus);
		guestUser.isAlwaysLogged = false;
		userManager->update(guestUser, &dbStatus);
	}

	void UserController::userBlockedNotification()
	{
	}

	bool UserController::validateUserCredentails(const std::string &correctPass, const std::string &userPass)
	{
		return correctPass == userPass;
	}

	void UserController::emitUserChanged()
	{
		UserSession::getInstance().setUser(currentUser);

		for(auto &listener: Publisher<IUserListener>::listeners) {
			if(!listener.expired()) {
				listener.lock().get()->onUserChanged(currentUser);
			}
		}

		for(auto &listener: Publisher<ILocalSyncUpdates<User>>::listeners) {
			if(!listener.expired()) {
				listener.lock().get()->onLocalUpdates(currentUser);
			}
		}

		emit userChanged();
	}

	void UserController::emitUserStatus(const DB::Status &dbStatus, std::function<void(const UserController::Status &)> callback)
	{
		switch(dbStatus) {
		case DB::Status::OK:
			emit callback(Status::OK);
			break;
		case DB::Status::ERR_USER_WRONG:
			emit callback(Status::WRONG_USER);
			break;
		case DB::Status::ERR_USER_BLOCKED:
			emit callback(Status::BLOCKED);
			break;
		case DB::Status::ERR_NETWORK_NOT_CONNECTED:
			emit callback(Status::NOT_CONNECTION);
			break;
		default:
			emit callback(Status::NOT_KNOWN);
			break;
		}
	}
}
