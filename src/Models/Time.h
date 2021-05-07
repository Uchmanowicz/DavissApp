#pragma once

#include <chrono>

#include <QObject>
#include <QString>
#include <QDateTime>

class Time
{   
public:
	Q_GADGET

public:

	Q_PROPERTY(int ui_timestamp MEMBER timestamp);
	Q_PROPERTY(int ui_year MEMBER year);
	Q_PROPERTY(int ui_month MEMBER month);
	Q_PROPERTY(int ui_day MEMBER day);
	Q_PROPERTY(int ui_hours MEMBER hours);
	Q_PROPERTY(int ui_minutes MEMBER minutes);
	Q_PROPERTY(int ui_seconds MEMBER seconds);


public:
	Time() {}
	Time(const long long &timestamp_)
		: timestamp(timestamp_)
	{
		expandTimestamp(timestamp);
	}

//	Time(const int &minutes_)
//		: minutes(minutes_)
//	{
//	}

	long long timestamp = 0;
	int year = 0;
	int month = 0;
	int day = 0;
	int hours = 0;
	int minutes = 0;
	int seconds = 0;

	void expandTimestamp(const long long &timestamp)
	{
//		QDateTime::fromMSecsSinceEpoch(training->timestamp).toString(Qt::ISODate).replace('T', ' ');
		QDateTime DT = QDateTime::fromMSecsSinceEpoch(timestamp);
		auto date = DT.date();
		year = date.year();
		month = date.month();
		day = date.day();

		auto time = DT.time();
		hours = time.hour();
		minutes = time.minute();
		seconds = time.second();
	}


	bool operator==(const Time &other) const
	{
		return timestamp == other.timestamp;
	}

	bool operator!=(const Time &other) const
	{
		return timestamp != other.timestamp;
	}
};
Q_DECLARE_METATYPE(Time)
