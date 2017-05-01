#include "stdafx.h"
HOGDetection::HOGDetection() {
	hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
}
HOGDetection::~HOGDetection() {

}

cv::Mat HOGDetection::resizeImage(const cv::Mat img, cv::Size target_size)
{
	cv::Mat image = img.clone();
	int width = img.cols,
		height = img.rows;
	int border = 2;
	float ratio = (float)img.cols / (float)target_size.height;
	if(ratio < 1.6)
	{
		ratio = (float)img.rows / (float)target_size.width;
	}
	int nWidth = width / ratio;
	int nHeight = height / ratio;
	std::cout << "height:" << nHeight << " width:" << nWidth << std::endl;
	resize(img, image, cv::Size(nWidth, nHeight));
	cv::Mat square = cv::Mat::zeros(target_size.height, target_size.width, img.type());
	for (int j = 0; j < image.cols; j++) {
		for (int i = 0; i < image.rows; i++)
		{
			square.at<double>(i,j) = image.at<double>(i,j);
		}
	}
	//std::cout << square.rows << " " << square.cols << std::endl;
	cv::imshow("dfs", square);
	return square;
}

std::vector<std::vector<cv::Rect>> HOGDetection::detect(std::vector<CroppedImage>& frames) {

	//cv::namedWindow("output", 1);
	std::vector<std::vector<cv::Rect>> found_filtered(frames.size());
	if (frames.empty())
		return found_filtered;
		fflush(stdout);
		for (int x = 0; x < frames.size(); x++) {
			std::vector<cv::Rect> rRect;
			std::vector<cv::Rect> found;
			cv::Mat test  = frames[x].croppedImg;
			cv::Size size(64, 128);
			resize(frames[x].croppedImg, test, size);

			//cv::Mat test = resizeImage(frames[x].croppedImg, cv::Size(64, 128));
			//hog.detectMultiScale(test, found, 0, cv::Size(6, 6), cv::Size(32, 32), 1.05, 2);
			hog.detectMultiScale(test, found, 0, cv::Size(4, 4), cv::Size(32,32), 1.05, 2);
			
			if (found.empty()) {
			//	frames._Pop_back_n(x);
				continue;
			}
			//std::cout << "Nalezeno: " << found.size() << std::endl;
			//cv::imshow("test", test);
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