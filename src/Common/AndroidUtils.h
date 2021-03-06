#pragma once

#include <QDebug>

#ifdef ANDROID
#include <QAndroidJniObject>
#include <QtAndroid>
#include <QStandardPaths>
#endif


class AndroidUtils
{
public:
	static std::string getRealFilePath(const std::string &path);
};

