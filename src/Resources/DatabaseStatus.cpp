#include "DatabaseStatus.h"

namespace DB
{
	std::map<Status, std::string> StatusStringParser::statuses = {{Status::OK, OK_},
																	  {Status::ERR_DATABASE_INTERNAL, ERR_DATABASE_INTERNAL_},
																	  {Status::ERR_DATABASE_SYNTAX, ERR_DATABASE_SYNTAX_},
																	  {Status::ERR_PARAMETERS_WRONG, ERR_PARAMETERS_WRONG_},
																	  {Status::ERR_USER_WRONG, ERR_USER_WRONG_},
																	  {Status::ERR_USER_BLOCKED, ERR_USER_BLOCKED_},
																	  {Status::ERR_NETWORK_NOT_CONNECTED, ERR_NETWORK_NOT_CONNECTED_},
																	  {Status::ERR_UNKNOWN, ERR_UNKNOWN_}};
}
