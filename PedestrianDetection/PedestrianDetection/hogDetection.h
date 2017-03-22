#pragma once
class HOGDetection {

public:
	HOGDetection();
	~HOGDetection();
	std::vector<cv::Rect> detect(cv::Mat &frame);
private:
	cv::HOGDescriptor hog;
};