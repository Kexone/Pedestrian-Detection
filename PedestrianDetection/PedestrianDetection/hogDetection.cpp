#include "stdafx.h"
HOGDetection::HOGDetection() {
	hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
}
HOGDetection::~HOGDetection() {

}

std::vector<std::vector<cv::Rect>> HOGDetection::detect(std::vector<CroppedImage>& frames) {

	//cv::namedWindow("output", 1);
	std::vector<std::vector<cv::Rect>> found_filtered(frames.size());
	if (frames.empty())
		return found_filtered;
		fflush(stdout);
		for (int x = 0; x < frames.size(); x++) {
			//std::vector<cv::Rect>filteredHulls = (cv::Rect) hulls[x];
			std::vector<cv::Rect> rRect;
			std::vector<cv::Rect> found;
			cv::Mat test  = frames[x].croppedImg;
		//	cvResize(&hulls[x], &test, CV_INTER_LINEAR);
			cv::Size size(64, 128);//the dst image size,e.g.100x100
			cv::Mat dst;//dst image
			cv::Mat src;//src image
			resize(frames[x].croppedImg, test, size);
			hog.detectMultiScale(test, found, 0, cv::Size(4, 4), cv::Size(2, 2), 1, 1);
			std::cout << "Nalezeno: " << found.size() << std::endl;
			cv::imshow("test", test);
			if (found.empty()) {
				frames._Pop_back_n(x);
				continue;
			}
			size_t i, j;
			for (i = 0; i<found.size(); i++)
			{
				cv::Rect r = found[i];
				for (j = 0; j<found.size(); j++)
					if (j != i && (r & found[j]) == r)
						break;
				if (j == found.size())
					found_filtered[x].push_back(r);
			}
			found.clear();
		}
		return found_filtered;
}