#include "stdafx.h"
#include "convexHull.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


ConvexHull::ConvexHull()
{
}

ConvexHull::ConvexHull(cv::Mat src, cv::Mat src_gray, int thresh) {
	src.copyTo(this->src);
	src_gray.copyTo(this->src_gray);
	this->thresh = thresh;
	int max_thresh = 255;
	//cv::createTrackbar(" Threshold:", "Source", &thresh, max_thresh, thresh_callback);

}

ConvexHull::~ConvexHull()
{
}


/** @function thresh_callback */
std::vector<std::vector<cv::Point>> ConvexHull::thresh_callback(int, void*)
{
	cv::RNG rng(12345);
	cv::Mat src_copy = src.clone();
	cv::Mat orig = src.clone();
	cv::Mat threshold_output;
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;

	/// Detect edges using Threshold
	threshold(src_gray, threshold_output, thresh, 255, cv::THRESH_BINARY);

	/// Find contours
	findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));

	/// Find the convex hull object for each contour
	std::vector<std::vector<cv::Point> >hull(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		convexHull(cv::Mat(contours[i]), hull[i], false);
	}

	std::vector<std::vector<cv::Point>>filteredHulls;
	int minThresholdArea = 50 * 50 , maxThresholdArea = 80 * 60;

	for (int i = 0; i < hull.size(); i++) {
		int minX = INT_MAX, minY = INT_MAX, maxY = 0, maxX = 0;

		for (auto &p : hull[i]) {
			if (p.x <= minX) minX = p.x;
			if (p.y <= minY) minY = p.y;
			if (p.x >= maxX) maxX = p.x;
			if (p.y >= maxY) maxY = p.y;
		}

		// Vypoèítej obsah
		if ((maxX - minX) * (maxY - minY) > minThresholdArea)
			 {
			filteredHulls.push_back(hull[i]);
		}
	}


	/// Draw contours + hull results
	cv::Mat drawing = cv::Mat::zeros(threshold_output.size(), CV_8UC3);
	for (int i = 0; i < filteredHulls.size(); i++)
	{
		cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		//drawContours(drawing, contours, i, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
		drawContours(orig, filteredHulls, i, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
		//drawContours(drawing, filteredHulls, i, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
	}

	/// Show in a window
	cv::namedWindow("Hull demo", CV_WINDOW_AUTOSIZE);
	imshow("Hull demo", orig);
	return filteredHulls;
}