#include "UserSession.h"

const User &UserSession::getUser() const
{
	if(isActive()) {
		return *currentUser;
	}

	return dummyUser;
}

void UserSession::setUser(const User &user)
{
	currentUser = user;
}

bool UserSession::isActive() const
{
	return currentUser.has_value();
}

void UserSession::deActivate()
{
	currentUser.reset();
}
