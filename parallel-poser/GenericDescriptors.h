#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"

#pragma once
class GenericDescriptors
{
public:
	GenericDescriptors(void);
	~GenericDescriptors(void);

	cv::Mat ReadImageFromDisk(std::string imagePath);
	cv::Mat GetBinaryImage(cv::Mat imageMatrix, float threshold);
	cv::Mat GetSilhouetteImage(cv::Mat imageMatrix);
	cv::Mat GetCannyImage(cv::Mat imageMatrix);
};