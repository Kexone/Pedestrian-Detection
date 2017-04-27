#pragma once
#include "CroppedImage.h"

class HOGDetection {

public:
	HOGDetection();
	~HOGDetection();
	std::vector<std::vector<cv::Rect>> detect(std::vector<CroppedImage>& frame);
private:
	cv::HOGDescriptor hog;
};
