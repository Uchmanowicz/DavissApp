#pragma once

namespace Sync
{
	class Entities
	{
		struct UpdateFlags
		{
			long long localTimestamp = 0;
			long long webTimestamp = 0;

			bool operator==(const UpdateFlags &other) const
			{
				return localTimestamp == other.localTimestamp
					   && webTimestamp == other.webTimestamp;
			}
		};

	public:
		Entities() = default;
		//	Sync(const long long &localTimestamp_, const long long &webTimestamp_)
		//		: localTimestamp(localTimestamp_), webTimestamp(webTimestamp_) {}
		~Entities() = default;

		long long userSync = -1;
		long long jobSync = -1;

		bool operator==(const Entities &other) const
		{
			return userSync == other.userSync
				   && jobSync == other.jobSync;
		}

		bool operator!=(const Entities &other) const
		{
			return userSync != other.userSync
				   || jobSync != other.jobSync;
		}
	};
}
