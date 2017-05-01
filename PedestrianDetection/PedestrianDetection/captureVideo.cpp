#include "stdafx.h"
#include "convexHull.h"

struct CroppedImage;

CaptureVideo::CaptureVideo()
{
}

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
	std::vector<std::vector<cv::Rect>> found_filtered;
	MOGDetection detector;
	HOGDetection hogDetect;
	for (; ;)
	{
		capture >> frame;
		if (frame.empty())
			break;
		cv::Mat blured = frame.clone();
		
		cv::blur(frame, blured, cv::Size(10, 10));
		frameMog = detector.detect(blured);
		src_gray = frameMog.clone();
		cv::blur(src_gray, src_gray, cv::Size(10,10));
		ConvexHull *ch = new ConvexHull(frame, src_gray, 0);
		rect = ch->thresh_callback(0, 0);
		std::vector<cv::Mat> croppedMats;
		std::vector<CroppedImage> croppedImages;
		if(rect.size() != 0)
			for (int j = 0; j < rect.size(); j++) {
				for (int i = 0; i < rect[j].size(); i++)
				{
					cv::Mat croppedMat = frame.clone();
 					croppedImages.push_back(createStruct(frame, rect[j][i]));
				}
			}
	found_filtered = hogDetect.detect(croppedImages);
		for (int j = 0; j < found_filtered.size(); j++) {
			for (int i = 0; i < found_filtered[j].size(); i++)
			{
				cv::Rect r = found_filtered[j][i];
				r.x += cvRound(croppedImages[j].offsetX);
				r.width = cvRound(croppedImages[j].croppedImg.cols);
				r.y += cvRound(croppedImages[j].offsetY);
				r.height = cvRound(croppedImages[j].croppedImg.rows);
				rectangle(frame, r.tl(), r.br(), cv::Scalar(0, 255, 0), 3);
			}
		}
	//	cv::imshow("mog2", frameMog);
		cv::imshow("source", frame);
		cv::waitKey(30);
		frame.release();
	}
}

CroppedImage CaptureVideo::createStruct(cv::Mat frame, cv::Rect cropping)
{
	CroppedImage cis;
	cis.croppedImg = frame(cropping);
	cis.id = id++;
	cis.defaultSize = cv::Size(frame.cols, frame.rows);
	cis.offsetX = cropping.x;
	cis.offsetY = cropping.y;
	return cis;
};