#pragma once

#include <QDebug>
#include <functional>

#include "Templates/Publisher.h"
#include "Templates/SynchronizerHandler.h"
#include "Common/AndroidUtils.h"
#include "Common/Cryptographic_PROTECTED.h"
#include "Common/ImageConverter.h"
#include "Common/UserSession.h"
#include "Managements/UserManagement/UserManagement.h"
#include "Resources/DatabaseStatus.h"
#include "Models/User.h"

namespace Listeners
{
	// class IUserListener
	//{
	// public:
	//	virtual ~IUserListener() {};
	//	virtual void onUserChanged(const User &user) = 0;
	// };
}

namespace Controllers
{
	class UserController : public QObject, public Templates::Publisher<Listeners::IUserListener>, Templates::Publisher<Listeners::ILocalSyncUpdates<Person::User>>, public Listeners::IUserSync
	{
		Q_OBJECT

	public:
		Q_PROPERTY(Person::User ui_currentUser MEMBER currentUser NOTIFY userChanged)
		Q_PROPERTY(bool ui_isLogged READ isLogged NOTIFY userChanged)

		using Publisher<Listeners::IUserListener>::addListener;
		using Publisher<Listeners::ILocalSyncUpdates<Person::User>>::addListener;

		enum Status
		{
			OK,
			WRONG_USER,
			BLOCKED,
			USER_EXISTS,
			NOT_CONNECTION,
			NOT_KNOWN
		};
		Q_ENUM(Status)

		explicit UserController(const std::shared_ptr<Managers::UserManagement> &userManagement_,
								QObject *parent = nullptr);
		~UserController();

		void onSynced() override;

		bool isLogged();
		void signInUserIfExists();

		Q_INVOKABLE void signIn(const QString &login, const QString &password, const bool &alwaysLogged, const bool &isHashedPassword);
		Q_INVOKABLE void signOut();
		Q_INVOKABLE void changeAlwaysSigned(const bool &enabled);
		Q_INVOKABLE void changePassword(const QString &password);
		Q_INVOKABLE void changeName(const QString &name);
		Q_INVOKABLE QString loadAvatar(const QString &filename);
		Q_INVOKABLE void changeAvatar(const QString &filename);

		Q_INVOKABLE QString convertPasswordToHash(const QString &password);

		Person::User currentUser;

	signals:
		void signInResult(const UserController::Status &status);
		void signOutResult(const UserController::Status &status);
		void signUpResult(const UserController::Status &status);

		void userNameChanged(const UserController::Status &status);
		void userPasswordChanged(const UserController::Status &status);
		void userAvatarChanged(const UserController::Status &status);

		void userChanged();

	private:
		std::shared_ptr<Managers::UserManagement> userManager;

		void addGuestUser();
		void signInGusetUser();
		void signOutGusetUser();
		void userBlockedNotification();
		bool validateUserCredentails(const std::string &correctPass, const std::string &userPass);

		void emitUserChanged();
		void emitUserStatus(const DB::Status &dbStatus, std::function<void(const UserController::Status &)> callback);
	};
}
