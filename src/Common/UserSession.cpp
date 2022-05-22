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
	emitUserChanged();
}

bool UserSession::isActive() const
{
	return currentUser.has_value();
}

void UserSession::deActivate()
{
	currentUser.reset();
	emitUserChanged();
}

void UserSession::emitUserChanged() const
{
	for(auto &listener: Publisher<IUserListener>::listeners) {
		if(!listener.expired()) {
			listener.lock().get()->onUserChanged(*currentUser);
		}
	}
}
