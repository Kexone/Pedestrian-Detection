#pragma once
class MOGDetection {

public:
	MOGDetection();
	~MOGDetection();
	cv::Mat detect(cv::Mat &frame);
private:
	cv::Ptr<cv::BackgroundSubtractor> pMOG; //MOG Background subtractor
	cv::Ptr<cv::BackgroundSubtractor> pMOG2;
};