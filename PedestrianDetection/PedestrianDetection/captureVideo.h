#pragma once
class CaptureVideo {
private:
	
	CaptureVideo() { };
public:
	~CaptureVideo() { }
	static cv::VideoCapture& getInstance() {
		static cv::VideoCapture capture;
		if(!capture.open(0))
			return capture;
		return capture;
	}

};