#include "stdafx.h"

HOGDetection::HOGDetection() {
	hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
}
HOGDetection::~HOGDetection() {

}
std::vector<cv::Rect> HOGDetection::detect(cv::Mat &frame) {

	//cv::namedWindow("output", 1);
	std::vector<cv::Rect> found, found_filtered;

	if (frame.empty())
		return found_filtered;
		fflush(stdout);
		hog.detectMultiScale(frame, found, 0, cv::Size(4, 4), cv::Size(2, 2), 1, 1);
		size_t i, j;
		for (i = 0; i < found.size(); i++)
		{
			cv::Rect r = found[i];
			for (j = 0; j < found.size(); j++)
				if (j != i && (r & found[j]) == r)
					break;
			if (j == found.size())
				found_filtered.push_back(r);
		}
		return found_filtered;
}