#include "stdafx.h"
#include "convexHull.h"

CaptureVideo::CaptureVideo(std::string filename)
{ 
	capture.open(filename); 
	
	std::cout << capture.grab() << std::endl;
	capture.set(CV_CAP_PROP_FOURCC, CV_FOURCC('H', '2', '6', '4'));
};

void CaptureVideo::processVideo()
{
	cv::Mat frame, frameMog, src_gray;
	
	if (!capture.isOpened()) {
		std::cout << "Could not open reference " << std::endl;
		return;
	}
	std::vector<std::vector<cv::Point>>hulls;
	std::vector<std::vector<cv::Rect>> rect;
	MOGDetection detector;
	HOGDetection hogDetect;
	std::vector<cv::Rect> found_filtered;
	for (; ;)
	{
		capture >> frame;
		if (frame.empty())
			capture.set(1,0.0);
			//break;
		frameMog = detector.detect(frame);
		src_gray = frameMog.clone();
		//cv::cvtColor(frameMog, src_gray, CV_BGR2GRAY);
		
		cv::blur(src_gray, src_gray, cv::Size(4, 4));
		ConvexHull *ch = new ConvexHull(frame, src_gray, 0);
		rect = ch->thresh_callback(0, 0);
		std::vector<cv::Mat> croppedMats;
		if(rect.size() != 0)
		for (int i = 0; i < rect[0].size(); i++)
		{
			cv::Mat croppedMat = frame.clone();
			std::cout << "Before:" << croppedMat.rows << " x " << croppedMat.cols << std::endl;

			croppedMat = croppedMat(rect[0][i]);

			croppedMats.push_back(croppedMat.clone());
			//if(croppedMat.cols != 0)
			std::cout << "After: " << croppedMat.rows << " x " << croppedMat.cols << std::endl;
			std::cout << "Crop:" << rect.size() << std::endl;
			cv::imshow("test", croppedMat);
			//croppedMat.release();
		}
		for(int i = 0; i < croppedMats.size(); i++)
		{
			found_filtered.push_back(hogDetect.detect(croppedMats.pop_back()));

		}
		//found_filtered = hogDetect.detect(hulls);
		for (int i = 0; i < found_filtered.size(); i++)
		{
			cv::Rect r = found_filtered[i];
			r.x += cvRound(r.width*0.1);
			r.width = cvRound(r.width*0.8);
			r.y += cvRound(r.height*0.07);
			r.height = cvRound(r.height*0.8);
			rectangle(frame, r.tl(), r.br(), cv::Scalar(0, 255, 0), 3);
		}
		cv::imshow("mog2", frameMog);
		cv::imshow("source", frame);
		cv::waitKey(30);
		frame.release();
	}
}
