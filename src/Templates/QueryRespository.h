#pragma once

#include <vector>
#include <string>

namespace DB
{
	struct Query
	{
		enum Type
		{
			IDLE = 0,
			SELECT,
			INSERT,
			UPDATE,
			REMOVE
		};

		std::string query = "";
		std::string body = "";
		Type type = Type::IDLE;

		Query(const std::string &query_, const std::string &body_, const Type &type_ = Type::IDLE)
			: query(query_), body(body_), type(type_) { }
		Query() { }
	};
}
