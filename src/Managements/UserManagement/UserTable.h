#pragma once

struct UserTable final
{
	static constexpr char const *TABLE_NAME = "Users";
	static constexpr char const *LOGIN = "Login";
	static constexpr char const *PASSWORD = "Password";
	static constexpr char const *NAME = "Name";
	static constexpr char const *ROLE = "Role";
	static constexpr char const *AVATAR = "Avatar";
	static constexpr char const *MODULES = "Modules";
static constexpr char const *IS_BLOCKED = "IsBlocked";

	static constexpr char const *IsAlwaysLogged = "IsAlwaysLogged";

};
