#pragma once

class Sync
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
	Sync() {}
//	Sync(const long long &localTimestamp_, const long long &webTimestamp_)
//		: localTimestamp(localTimestamp_), webTimestamp(webTimestamp_) {}


	long long userSync = -1;
	long long jobSync = -1;

	bool operator==(const Sync &other) const
	{
		return userSync == other.userSync
				&& jobSync == other.jobSync;
	}

	bool operator!=(const Sync &other) const
	{
		return userSync != other.userSync
				|| jobSync != other.jobSync;
	}
};
