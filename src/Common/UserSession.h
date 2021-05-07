#pragma once

#include <optional>
#include "Templates/Singleton.h"
#include "Models/User.h"

class UserSession : public Singleton<UserSession>
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
};
