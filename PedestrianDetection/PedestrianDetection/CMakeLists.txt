cmake_minimum_required(VERSION 1.6)
project(SP)

set(OPENCV "/media/56da5220-35b4-4144-9320-d10ca434d276_/opencv")

#set(OPENCV_DIR "/media/56da5220-35b4-4144-9320-d10ca434d276_/opencv")
#find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui bgsegm)

set(CMAKE_CXX_COMPILER "g++-4.8")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} - debug")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} - release")
include_directories(${OPENCV}/include)
link_directories(${OPENCV}/lib)

add_executable(SP PedestrianDetection.cpp hogDetection.cpp mogDetection.cpp captureVideo.cpp CroppedImage.cpp)
target_link_libraries(SP opencv_core opencv_highgui opencv_bgsegm
opencv_imgproc opencv_video opencv_videoio opencv_objdetect)
