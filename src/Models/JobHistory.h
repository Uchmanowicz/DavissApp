#pragma once

#include <QObject>
#include <QString>

namespace Job
{
	/// @brief
	///
	/// Class is template for all modules (main features)
	class JobHistory
	{
	public:
		Q_GADGET

	public:
		Q_PROPERTY(QString ui_login_inTimestamp MEMBER login_inTimestamp);
		Q_PROPERTY(long long ui_inTimestamp MEMBER inTimestamp);
		Q_PROPERTY(long long ui_outTimestamp MEMBER outTimestamp);
		Q_PROPERTY(long ui_duration MEMBER duration);

	public:
		JobHistory() { }

		/// @brief
		///
		/// Default constructor to create Module
		/// @param id_ Specific id for module
		/// @param name_ Module name which is displayed
		/// @param isEnabled_ State of enabled (visible) module
		JobHistory(const QString &login_inTimestamp_, const long long &outTimestamp_)
			: login_inTimestamp(login_inTimestamp_), outTimestamp(outTimestamp_)
		{
			auto stringList = login_inTimestamp.split("_");
			inTimestamp = stringList.at(1).toLongLong();
			duration = outTimestamp - inTimestamp;
		}

		QString login_inTimestamp = "";
		long long inTimestamp = -1;
		long long outTimestamp = -1;
		long duration = -1;

		bool operator==(const JobHistory &other) const
		{
			return login_inTimestamp == other.login_inTimestamp
				   && inTimestamp == other.inTimestamp
				   && outTimestamp == other.outTimestamp
				   && duration == other.duration;
		}

		bool operator!=(const JobHistory &other) const
		{
			return login_inTimestamp != other.login_inTimestamp
				   || inTimestamp != other.inTimestamp
				   || outTimestamp != other.outTimestamp
				   || duration != other.duration;
		}
	};
}
Q_DECLARE_METATYPE(Job::JobHistory)
