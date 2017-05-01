#include "stdafx.h"

int main(int argc, char* argv[])
{
	CaptureVideo captureVid;
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
	if (argv[1] != NULL) {
		std::cout << "Opening " << argv[1] << std::endl;
		captureVid = CaptureVideo(argv[1]);
	}
	else
		captureVid = CaptureVideo(filenames[1]);

	captureVid.processVideo();
	cv::waitKey(0);
	return 0;
}