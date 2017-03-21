#pragma once
class CaptureVideo {
private:
	cv::VideoCapture capture;
public:
	CaptureVideo(std::string filename);
	~CaptureVideo() { }
	void processVideo();

};