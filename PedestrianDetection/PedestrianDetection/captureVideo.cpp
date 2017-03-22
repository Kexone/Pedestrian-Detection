#include "stdafx.h"

CaptureVideo::CaptureVideo(std::string filename)
{ 
	capture.open(filename); 
	
	std::cout << capture.grab() << std::endl;
	capture.set(CV_CAP_PROP_FOURCC, CV_FOURCC('H', '2', '6', '4'));
};

void CaptureVideo::processVideo()
{
	cv::Mat frame, frameMog;
	
	if (!capture.isOpened()) {
		std::cout << "Could not open reference " << std::endl;
		return;
	}

	MOGDetection detector;
	HOGDetection hogDetect;
	std::vector<cv::Rect> found_filtered;
	for (; ;)
	{
		capture >> frame;
		if (frame.empty())
			break;
		frameMog = detector.detect(frame);
		found_filtered = hogDetect.detect(frameMog);
		for (int i = 0; i < found_filtered.size(); i++)
		{
			cv::Rect r = found_filtered[i];
			r.x += cvRound(r.width*0.1);
			r.width = cvRound(r.width*0.8);
			r.y += cvRound(r.height*0.07);
			r.height = cvRound(r.height*0.8);
			rectangle(frame, r.tl(), r.br(), cv::Scalar(0, 255, 0), 3);
		}
		cv::imshow("source", frame);
		cv::waitKey(1);
		frame.release();
	}
}
