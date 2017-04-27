#pragma once
#include "CroppedImage.h"

class HOGDetection {

public:
	HOGDetection();
	~HOGDetection();
	std::vector<std::vector<cv::Rect>> detect(std::vector<CroppedImage>& frame);
	cv::Mat resizeImage(const cv::Mat img, cv::Size target_size);
private:
	cv::HOGDescriptor hog;
};
