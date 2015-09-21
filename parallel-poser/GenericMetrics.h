#include "opencv2\highgui\highgui.hpp"

#pragma once
class GenericMetrics
{
public:
	GenericMetrics();
	~GenericMetrics();

	double EuclideanDistance(cv::Point p1, cv::Point p2);
	cv::Scalar BitwiseAndSilhouetteDistance(cv::Mat binaryImage1, cv::Mat binaryImage2);
	cv::Scalar RbySilhouetteDistance(cv::Mat binaryImage1, cv::Mat binaryImage2);
};

