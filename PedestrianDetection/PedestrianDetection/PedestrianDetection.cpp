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
		"../long_vga.mp4", 
		"../long_hd.mp4", 
		"../short_vga.mp4", 
		"../short_hd.mp4", 
		"../video/cctv1.mp4",
		"../video/cctv2.mp4",
		"../video/cctv3.mp4",
		"../video/cctv4.mp4",
		"../video/cctv5.mp4",
	};
	if (argv[1] != NULL) {
		std::cout << "Opening " << argv[1] << std::endl;
		captureVid = CaptureVideo(argv[1]);
	}
	else
		captureVid = CaptureVideo(filenames[10]);

	captureVid.processVideo();
	std::cout << "ENDE";
	cv::waitKey(0);
	return 0;
}