#pragma once

#include <fstream>
#include <sstream>

#include <QDebug>
#include <QString>
#include <QByteArray>
#include <QFile>

#include "Utility.h"

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs.hpp"

class ImageConverter
{
public:
	enum ImageFormat
	{
		JPEG,
		PNG
	};

//		explicit ImageConverter();
//		~ImageConverter();

	static std::string convertToBLOB(const std::string &imageName, const ImageFormat &targetFormat, const long &maxSize_KB);

private:
	static inline long long getImageSize_KB(const std::string &imagePath);
	static std::string convertToBLOB(const cv::Mat &image, const ImageFormat &targetFormat, const std::vector<int> &params);
	static cv::Mat compresImage(const cv::Mat &imagePath);
	static const std::map<ImageFormat, std::string> formatStringMapper;

};
