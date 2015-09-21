#include "GenericDescriptors.h"

GenericDescriptors::GenericDescriptors(void)
{
}

GenericDescriptors::~GenericDescriptors(void)
{

}

cv::Mat GenericDescriptors::ReadImageFromDisk(std::string imagePath)
{
	return cv::imread(imagePath, cv::IMREAD_COLOR);
}

cv::Mat GenericDescriptors::GetBinaryImage(cv::Mat imageMatrix, float threshold)
{
	cv::Mat binaryImageMatrix;
	cv::threshold(imageMatrix, binaryImageMatrix, threshold, 255.0, cv::THRESH_BINARY);
	return binaryImageMatrix;
}

cv::Mat GenericDescriptors::GetSilhouetteImage(cv::Mat imageMatrix)
{
	return GetBinaryImage(imageMatrix, 0.2);
}

cv::Mat GenericDescriptors::GetCannyImage(cv::Mat imageMatrix)
{
	cv::Mat cannyImageMatrix;
	cv::Canny(imageMatrix, cannyImageMatrix, 50.0, 50.0);
	return cannyImageMatrix;
}