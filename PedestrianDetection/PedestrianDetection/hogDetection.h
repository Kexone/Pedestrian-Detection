#pragma once
class HOGDetection {

public:
	HOGDetection();
	~HOGDetection();
	std::vector<std::vector<cv::Rect>> detect(std::vector<cv::Mat>& hulls);
private:
	cv::HOGDescriptor hog;
};