#pragma once

namespace Job
{
	struct JobHistoryTable final
	{
		static constexpr char const *TABLE_NAME = "JobHistory";
		static constexpr char const *LOGIN_TIMESTAMP = "Login_InTimestamp";
		static constexpr char const *OUT_TIMESTAMP = "OutTimestamp";
		static constexpr char const *DURATION = "Duration";
		static constexpr char const *LOGIN = "Login";
	};
}
