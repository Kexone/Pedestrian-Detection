#include "stdafx.h"

CaptureVideo::CaptureVideo(std::string filename)
{ 
	capture.open(filename); 
	
	std::cout << capture.grab() << std::endl;
	capture.set(CV_CAP_PROP_FOURCC, CV_FOURCC('H', '2', '6', '4'));
};

void CaptureVideo::processVideo()
{
	cv::Mat frame;
	
	if (!capture.isOpened()) {
		std::cout << "Could not open reference " << std::endl;
		return;
	}

//	cv::namedWindow("source", 1);
	for (; ;)
	{
		capture >> frame;
		if (frame.empty())
			break;
		cv::imshow("source", frame);
	}
}
