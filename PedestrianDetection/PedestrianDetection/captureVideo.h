#pragma once
#include "CroppedImage.h"

class CaptureVideo {
private:
	cv::VideoCapture capture;
public:
	CaptureVideo();
	CaptureVideo(std::string filename);
	CroppedImage createStruct(cv::Mat frame, cv::Rect cropping);
	~CaptureVideo() { }
	void processVideo();

private:
	int id = 0;
};
