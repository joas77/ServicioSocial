#pragma once
#ifndef OPENNI_WRAPPER
#define OPENNI_WRAPPER

#include <OpenNI.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <array>

using std::cout;
using std::endl;

// TODO: fill class
namespace openni_wrapper 
{
	class Kinect 
	{
	public:
		Kinect();
		void getRGB(cv::Mat& camRgb);
		void getDepth(cv::Mat& camDepth);
		bool open();
		bool isValid();
		void close();
		~Kinect();

	private:
		static bool mIsInitialized;
		openni::VideoFrameRef mDepthFrame, mColorFrame;
		openni::VideoMode mParamvideo;
		openni::VideoStream mDepth, mColor;
		openni::Status mStatus;
		openni::Device mDevice;
		std::array<openni::VideoStream*, 2> mVideoStream;
	};

	bool HandleStatus(openni::Status status);
	void printStatus(openni::Status status);

	
}

#endif // !OPENNI_WRAPPER
