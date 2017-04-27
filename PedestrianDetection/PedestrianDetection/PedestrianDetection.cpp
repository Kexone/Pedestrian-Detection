#include "stdafx.h"
#include "convexHull.h"

int main(int argc, char* argv[])
{
	/*cv::Mat src, src_gray;
	int thresh = 100;
	int max_thresh = 255;
	/// Load source image and convert it to gray
	src = cv::imread("../3.png", 1);

	/// Convert image to gray and blur it
	cv::cvtColor(src, src_gray, CV_BGR2GRAY);
	cv::blur(src_gray, src_gray, cv::Size(3, 3));

	/// Create Window
	char* source_window = "Source";
	cv::namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	cv::imshow(source_window, src);
	ConvexHull *ch = new ConvexHull(src, src_gray, thresh);
	ch->thresh_callback(0, 0);*/
	//CaptureVideo captureVid = CaptureVideo("../cctv3.mov");
	//CaptureVideo captureVid = CaptureVideo("../cctv2.mov");
	//CaptureVideo captureVid = CaptureVideo("../cctv1.mov");
	//CaptureVideo captureVid = CaptureVideo("../long_hd.mp4");
	//CaptureVideo captureVid = CaptureVideo("../long_vga.mp4");
	//CaptureVideo captureVid = CaptureVideo("../short_hd.mp4");
	CaptureVideo captureVid = CaptureVideo("../short_vga.mp4");

	captureVid.processVideo();
	cv::waitKey(0);
	return 0;
}
