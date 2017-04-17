#pragma once
class ConvexHull
{
public:
	ConvexHull();
	ConvexHull(cv::Mat src, cv::Mat src_gray, int thresh);
	~ConvexHull();
	std::vector<std::vector<cv::Rect>> thresh_callback(int, void*);

private:
	cv::Mat src;
	cv::Mat src_gray;
	int thresh;
};

