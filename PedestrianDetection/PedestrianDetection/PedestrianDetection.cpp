#include "stdafx.h"

void runMOG() {
	//MOGDetection *mogDetect = new MOGDetection();
//	mogDetect->detect();
}

void runHOG() {
	//HOGDetection *hogDetect = new HOGDetection();
	//hogDetect->detect();
}

int main(int argc, char* argv[])
{
	//CaptureVideo captureVid = CaptureVideo("../JSCMTEST.mp4");
	//CaptureVideo captureVid = CaptureVideo("../test.mp4");
	CaptureVideo captureVid =  CaptureVideo("../test.mov");
	captureVid.processVideo();
	//std::thread first(runMOG);
	//std::thread second(runHOG);
	//first.join();
	//second.join();
	return 0;
}
