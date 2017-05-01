#include "stdafx.h"

int main(int argc, char* argv[])
{
	std::string filenames[] = { 
		"../cctv1.mov", 
		"../cctv2.mov", 
		"../cctv3.mov", 
		"../cctv4.mov", 
		"../cctv5.mov", 
		"../long_sd.mp4", 
		"../long_hd.mp4", 
		"../short_sd.mp4", 
		"../short_hd.mp4", 
	};

	CaptureVideo captureVid = CaptureVideo(filenames[1]);

	captureVid.processVideo();
	cv::waitKey(0);
	return 0;
}