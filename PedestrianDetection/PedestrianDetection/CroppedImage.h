#pragma once

struct CroppedImage
{
	int id;
	cv::Mat croppedImg;
	cv::Size defaultSize;
	int offsetX;
	int offsetY;
};
