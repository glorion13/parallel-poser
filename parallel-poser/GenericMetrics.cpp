#include <ctgmath>
#include "GenericMetrics.h"

GenericMetrics::GenericMetrics()
{
}


GenericMetrics::~GenericMetrics()
{
}

double GenericMetrics::EuclideanDistance(cv::Point p1, cv::Point p2)
{
	return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.x, 2));
}

cv::Scalar GenericMetrics::BitwiseAndSilhouetteDistance(cv::Mat binaryImage1, cv::Mat binaryImage2)
{
	// Normalised.
	// It either tries to make itself very small or very large.
	cv::Mat andImage;
	cv::bitwise_and(binaryImage1, binaryImage2, andImage);
	cv::Scalar imageSum = cv::sum(andImage);
	cv::Scalar normaliser = cv::sum(binaryImage1);
	return imageSum / normaliser;
}

cv::Scalar GenericMetrics::RbySilhouetteDistance(cv::Mat binaryImage1, cv::Mat binaryImage2)
{
	// Normalised
	cv::Scalar R, B, Y;
	cv::Mat rMatrix, bMatrix, yMatrix;
	cv::Mat inverseBinaryImage1, inverseBinaryImage2;

	cv::invert(binaryImage1, inverseBinaryImage1);
	cv::invert(binaryImage2, inverseBinaryImage2);

	cv::multiply(binaryImage1, inverseBinaryImage2, rMatrix);
	cv::multiply(binaryImage1, inverseBinaryImage1, bMatrix);
	cv::multiply(binaryImage1, binaryImage2, yMatrix);

	R = cv::sum(rMatrix);
	B = cv::sum(bMatrix);
	Y = cv::sum(yMatrix);

	double alpha = 1.0 / 2.0;
	cv::Scalar rbyDistance = (alpha * (Y / (B + Y))) + (alpha * (Y / (R + Y)));
	return 1 - rbyDistance[0];
}