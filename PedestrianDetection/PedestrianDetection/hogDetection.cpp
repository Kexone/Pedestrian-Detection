#include "stdafx.h"

HOGDetection::HOGDetection() {
	hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
}
HOGDetection::~HOGDetection() {

}

std::vector<std::vector<cv::Rect>> HOGDetection::detect(std::vector<cv::Mat>& hulls) {

	//cv::namedWindow("output", 1);
	std::vector<cv::Rect> found;
	std::vector<std::vector<cv::Rect>> found_filtered(hulls.size());
	if (hulls.empty())
		return found_filtered;
		fflush(stdout);
		for (int x = 0; x < hulls.size(); x++) {
			
			//std::vector<cv::Rect>filteredHulls = (cv::Rect) hulls[x];
			std::vector<cv::Rect> rRect;
			std::cout << "Nalezeno: " << found.size() << std::endl;
			
			hog.detectMultiScale(hulls[x], found, 0, cv::Size(4, 4), cv::Size(2, 2), 1, 1);
			size_t i, j;
			if (found.size() != 0) 
			for (i = 0; i<found.size(); i++)
			{
				cv::Rect r = found[i];
				for (j = 0; j<found.size(); j++)
					if (j != i && (r & found[j]) == r)
						break;
				if (j == found.size())
					found_filtered[x].push_back(r);
			}
		}
		return found_filtered;
}