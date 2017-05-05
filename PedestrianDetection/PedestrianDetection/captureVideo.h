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
	int totalFrames = 0;
	double startTime = 0;
	double endTime = 0;
	double fps = 0;
};
