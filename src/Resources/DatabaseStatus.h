#pragma once

#include <map>
#include <string>

namespace DB
{
	enum class Status
	{
		OK = 0,
		ERR_DATABASE_INTERNAL,
		ERR_DATABASE_SYNTAX,

		ERR_PARAMETERS_WRONG,

		ERR_USER_WRONG,
		ERR_USER_BLOCKED,

		ERR_NETWORK_NOT_CONNECTED,

		ERR_UNKNOWN
	};

	class StatusStringParser final
	{
	public:
		static std::map<Status, std::string> statuses;

	private:
		static constexpr char const *OK_ = "OK";

		static constexpr char const *ERR_DATABASE_INTERNAL_ = "ERR_DATABASE_INTERNAL";
		static constexpr char const *ERR_DATABASE_SYNTAX_ = "ERR_DATABASE_SYNTAX";

		static constexpr char const *ERR_PARAMETERS_WRONG_ = "ERR_PARAMETERS_WRONG";

		static constexpr char const *ERR_USER_WRONG_ = "ERR_USER_WRONG";
		static constexpr char const *ERR_USER_BLOCKED_ = "ERR_USER_BLOCKED";

		static constexpr char const *ERR_NETWORK_NOT_CONNECTED_ = "ERR_NETWORK_NOT_CONNECTED";

		static constexpr char const *ERR_UNKNOWN_ = "ERR_UNKNOWN";
	};
}
