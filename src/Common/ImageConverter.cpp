#include "ImageConverter.h"

const std::map<ImageConverter::ImageFormat, std::string> ImageConverter::formatStringMapper = {{ImageConverter::ImageFormat::JPEG, ".jpg"}, {ImageConverter::ImageFormat::PNG, ".png"}};

std::string ImageConverter::convertToBLOB(const std::string &imageName, const ImageConverter::ImageFormat &targetFormat, const long &maxSize_KB)
{
	if(!imageName.size()) {
		return "";
	}

	auto mat = cv::imread(imageName, cv::IMREAD_UNCHANGED);
	auto fileSize_KB = getImageSize_KB(imageName);

	std::vector<uchar> imgVec = {};
	std::vector<int> compressParams = {};

	if(fileSize_KB > maxSize_KB) {
		int compressLevel = 0;

		switch(targetFormat) {
		case ImageConverter::ImageFormat::JPEG:
			compressLevel = map<long>((maxSize_KB*100)/fileSize_KB, 0, 100, 45, 100);
			compressParams = {cv::IMWRITE_JPEG_QUALITY, compressLevel};
			break;
		case ImageConverter::ImageFormat::PNG:
			compressLevel = map<long>((maxSize_KB*100)/fileSize_KB, 0, 100, 9, 0);
			compressParams = {cv::IMWRITE_PNG_COMPRESSION, compressLevel};
			break;
		}
		qDebug() << "Compressed lvl: " << compressLevel;
	}

	auto blob = convertToBLOB(mat, targetFormat, compressParams);

	qDebug() << "Compressed BLOB: " << blob.c_str();

	return blob;
}

std::string ImageConverter::convertToBLOB(const cv::Mat &image, const ImageConverter::ImageFormat &targetFormat, const std::vector<int> &params)
{
	if(image.empty()) {
		return "";
	}

	std::vector<uchar> imgVec;
	cv::imencode(ImageConverter::formatStringMapper.at(targetFormat), image, imgVec, params);
	auto byteArr = QByteArray::fromRawData(reinterpret_cast<char*>(imgVec.data()), imgVec.size());
	return byteArr.toBase64().toStdString();
}

cv::Mat ImageConverter::compresImage(const cv::Mat &image)
{
	return cv::Mat();
}

long long ImageConverter::getImageSize_KB(const std::string &imagePath)
{
	QFile file(imagePath.c_str());
	return static_cast<long long>(file.size());

	// NOT WORKING ON ANDROID
	//	std::filesystem::path file{imagePath};
	//	return static_cast<long long>(std::filesystem::file_size(file)/1000);
}

