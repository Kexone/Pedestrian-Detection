#pragma once
class HOGDetection {

public:
	HOGDetection();
	~HOGDetection();
	std::vector<cv::Rect> detect(std::vector<std::vector<cv::Point>> &hulls);
private:
	cv::HOGDescriptor hog;
};