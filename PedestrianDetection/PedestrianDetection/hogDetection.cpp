#include "stdafx.h"

HOGDetection::HOGDetection() {

}
HOGDetection::~HOGDetection() {

}
void HOGDetection::detect() {
	cv::Mat frame;
	cv::HOGDescriptor hog;
	hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
	cv::namedWindow("output", 1);
	//cv::VideoCapture cap;
	cv::VideoCapture &cap = CaptureVideo::getInstance();
	// open the default camera, use something different from 0 otherwise;
	// Check VideoCapture documentation.
	if (!cap.open(0))
		return;
		//return 0;

	// the camera will be closed automatically upon exit
	//cap.close();
	for (;;)
	{
		//if (!frame.data)
			//continue;

		fflush(stdout);
		std::vector<cv::Rect> found, found_filtered;
		double t = (double)cv::getTickCount();
		
		cap >> frame;
		//frame = img;
		if (frame.empty()) break; // end of video stream
		cv::imshow("input", frame);

		//hog.detectMultiScale(frame, found, 0, cv::Size(4, 4), cv::Size(2, 2), 1, 1);
		hog.detectMultiScale(frame, found, 0, cv::Size(4, 4), cv::Size(0, 0), 1.2, 1);
		t = (double)cv::getTickCount() - t;
		printf("tdetection time = %gms\n", t*1000. / cv::getTickFrequency());
		size_t i, j;
		for (i = 0; i < found.size(); i++)
		{
			cv::Rect r = found[i];
			for (j = 0; j < found.size(); j++)
				if (j != i && (r & found[j]) == r)
					break;
			if (j == found.size())
				found_filtered.push_back(r);
		}
		for (i = 0; i < found_filtered.size(); i++)
		{
			cv::Rect r = found_filtered[i];
			r.x += cvRound(r.width*0.1);
			r.width = cvRound(r.width*0.8);
			r.y += cvRound(r.height*0.07);
			r.height = cvRound(r.height*0.8);
			rectangle(frame, r.tl(), r.br(), cv::Scalar(0, 255, 0), 3);
		}
		//cv::Mat test;
		//resize(frame, test, cv::Size(frame.cols/2, frame.rows/2));//resize image
		cv::imshow("output", frame);
		//imshow("people deteccctor", frame);
		//int c = cv::waitKey(0) & 255;
		//if (c == 'q' || c == 'Q')
		//break;
		if (cv::waitKey(1) == 27) break; // stop capturing by pressing ESC 
	}
}