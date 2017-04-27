#include "stdafx.h"
#include "convexHull.h"

struct CroppedImage;

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
		//cv::cvtColor(frameMog, src_gray, CV_BGR2GRAY);
		cv::blur(src_gray, src_gray, cv::Size(10,10));
		ConvexHull *ch = new ConvexHull(frame, src_gray, 0);
		rect = ch->thresh_callback(0, 0);
		std::vector<cv::Mat> croppedMats;
		std::vector<CroppedImage> croppedImages;
		if(rect.size() != 0)
			for (int j = 0; j < rect.size(); j++) {
				for (int i = 0; i < rect[j].size(); i++)
				{
				//	std::cout << "RECT" << rect.size() << "   RECT[0] " << rect[0].size() << std::endl;
					cv::Mat croppedMat = frame.clone();
				//	std::cout << "Before:" << croppedMat.rows << " x " << croppedMat.cols << std::endl;
 					croppedImages.push_back(createStruct(frame, rect[j][i]));
					//croppedMat = croppedMat(rect[j][i]);
					//cv::imshow("test", croppedMat);
					//if (croppedMat.cols / croppedMat.rows >= 1.5) {
						//croppedMats.push_back(croppedMat.clone());
						//if(croppedMat.cols != 0)
						//std::cout << "After: " << croppedMat.rows << " x " << croppedMat.cols << std::endl;
						//std::cout << "Crop:" << rect.size() << std::endl;
					//}
					//croppedMat.release();
				}
			}
	//	std::cout << "_cropped mats per cyclus: " << croppedMats.size() << std::endl;
	found_filtered = hogDetect.detect(croppedImages);
		//std::cout << "__detect on mats: " << found_filtered.size() << std::endl;
		//found_filtered = hogDetect.detect(hulls);
		for (int j = 0; j < found_filtered.size(); j++) {
			for (int i = 0; i < found_filtered[j].size(); i++)
			{
				cv::Rect r = found_filtered[j][i];
				r.x += cvRound(croppedImages[j].offsetX);
				//r.x += cvRound(r.width*0.1);
				//r.width = cvRound(r.width*0.8);
				r.width = cvRound(croppedImages[j].croppedImg.cols);
				r.y += cvRound(croppedImages[j].offsetY);
				//r.y += cvRound(r.height*0.07);
				//r.height = cvRound(r.height*0.8);
				r.height = cvRound(croppedImages[j].croppedImg.rows);
				rectangle(frame, r.tl(), r.br(), cv::Scalar(0, 255, 0), 3);
			}
		}
		cv::imshow("mog2", frameMog);
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