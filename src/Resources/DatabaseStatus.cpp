#include "DatabaseStatus.h"

const DBStatus::Statuses DBStatus::statuses = {{DBStatus::OK, OK_},
											   {DBStatus::ERR_DATABASE_INTERNAL, ERR_DATABASE_INTERNAL_},
											   {DBStatus::ERR_DATABASE_SYNTAX, ERR_DATABASE_SYNTAX_},
											   {DBStatus::ERR_PARAMETERS_WRONG, ERR_PARAMETERS_WRONG_},
											   {DBStatus::ERR_USER_WRONG, ERR_USER_WRONG_},
											   {DBStatus::ERR_USER_BLOCKED, ERR_USER_BLOCKED_},
											   {DBStatus::ERR_NETWORK_NOT_CONNECTED, ERR_NETWORK_NOT_CONNECTED_},
											   {DBStatus::ERR_UNKNOWN, ERR_UNKNOWN_}};
