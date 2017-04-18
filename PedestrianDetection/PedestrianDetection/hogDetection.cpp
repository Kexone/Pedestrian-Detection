#include "stdafx.h"

HOGDetection::HOGDetection() {
	hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
}
HOGDetection::~HOGDetection() {

}

std::vector<std::vector<cv::Rect>> HOGDetection::detect(std::vector<cv::Mat>& hulls) {

	//cv::namedWindow("output", 1);
	std::vector<std::vector<cv::Rect>> found_filtered(hulls.size());
	if (hulls.empty())
		return found_filtered;
		fflush(stdout);
		for (int x = 0; x < hulls.size(); x++) {
			//std::vector<cv::Rect>filteredHulls = (cv::Rect) hulls[x];
			std::vector<cv::Rect> rRect;
			std::vector<cv::Rect> found;
			cv::Mat test  = hulls[x];
		//	cvResize(&hulls[x], &test, CV_INTER_LINEAR);
			cv::Size size(128, 256);//the dst image size,e.g.100x100
			cv::Mat dst;//dst image
			cv::Mat src;//src image
			resize(hulls[x], test, size);
			hog.detectMultiScale(test, found, 0, cv::Size(4, 4), cv::Size(2, 2), 1, 1);
			std::cout << "Nalezeno: " << found.size() << std::endl;
			cv::imshow("test", test);
			if (found.empty()) continue;

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