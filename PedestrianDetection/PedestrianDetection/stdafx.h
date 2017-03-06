// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <sstream>
#include <thread>
//opencv
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/core/cvdef.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/video/tracking.hpp>
#include "opencv2/objdetect.hpp"
#include <opencv2/video/background_segm.hpp>
#include <opencv2/bgsegm.hpp>
// TODO: reference additional headers your program requires here


//own classes

#include "mogDetection.h"
#include "hogDetection.h"
#include "captureVideo.h"