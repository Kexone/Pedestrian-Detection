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
	CaptureVideo captureVid =  CaptureVideo("\Debug\SJCM0001.mp4");
	captureVid.processVideo();
	//std::thread first(runMOG);
	//std::thread second(runHOG);
	//first.join();
	//second.join();
	return 0;
}
