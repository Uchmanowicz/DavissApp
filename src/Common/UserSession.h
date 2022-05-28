#pragma once

#include <optional>
#include "Templates/Singleton.h"
#include "Templates/Publisher.h"
#include "Models/User.h"

namespace Listeners
{
	class IUserListener
	{
	public:
		virtual ~IUserListener() {};
		virtual void onUserChanged(const Person::User &user) = 0;
	};
}

namespace Person
{
	class UserSession : public Templates::Singleton<UserSession>, public Templates::Publisher<Listeners::IUserListener>
	{
		friend class Singleton<UserSession>;

	public:
		const User &getUser() const;
		void setUser(const User &user);
		bool isActive() const;
		void deActivate();

	private:
		UserSession() = default;
		UserSession(const UserSession &other) = delete;
		void operator=(const UserSession &other) = delete;

		std::optional<User> currentUser;
		User dummyUser = User();

		void emitUserChanged() const;
	};
}
