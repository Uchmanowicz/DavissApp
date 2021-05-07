#pragma once

#include <QString>
#include <QDebug>

#include <string>
#include <sstream>
#include <chrono>
#include <ctime>

//template <typename Out>
//void split(const std::string &string, const char &delimeter, Out &result) {
//	std::istringstream iss(string);
//	std::string element;
//	while(std::getline(iss, element, delimeter)) {
//		if(!element.empty()) {
//			result.
//		}
//	}
//}

//std::vector<std::string> split(const std::string &string, const char &delimeter)
//{
//	std::vector<std::string> list;
//}

inline long long currentTimestamp()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

inline std::string timestampToDate(const long long &timestamp, const std::string &format)
{
	return "";
//		auto date = std::chrono::system_clock::to_time_t(std::chrono::time_point timestamp);
//		auto d = date


//	QString trainingDate = QDateTime::fromMSecsSinceEpoch(training->timestamp).toString(Qt::ISODate).replace('T', ' ');
//	duration_cast<std::chrono::y>(std::chrono::seconds(timestamp)).count();
//	duration_cast<std::chrono::hours>(std::chrono::seconds(timestamp)).count();
//	duration_cast<std::chrono::hours>(std::chrono::seconds(timestamp)).count();
}

template<typename Type>
inline Type map(const Type &value, const Type &in_min, const Type &in_max, const Type &out_min, const Type &out_max)
{
	return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
