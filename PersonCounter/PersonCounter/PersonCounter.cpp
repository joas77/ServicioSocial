// PersonCounter.cpp : Defines the entry point for the console application.
//
#include <OpenNI.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <cstdlib>
#include <iostream>
#include <array>

#include "Kinect.h"
#include "Window.h"

using namespace openni;
//using namespace cv;
using namespace openni_wrapper;
using std::cout;
using std::endl;
using std::string;

enum windowTitles {
	TITLE_RGB,
	TITLE_GRAY,
	TITLE_DEPTH,
	TITLE_THRES,
	TITLE_WALL
};

void createVirtualWall(cv::InputArray binIm, cv::InputArray colorIm, cv::OutputArray dst)
{
	//TODO: iterate for each pixel an set to G if binIm(i,j) == 0
	/*pseudocode:
	for each pixel in binIm{
		if pixel == 0 then pixel of colorIm = G
	}
	*/
}

int main()
{
	// TODO: add waitkey functionality
	char waitkey = 0;
	
	Kinect kinect;

	//TODO: get size from kinect object
	cv::Mat frameColor(cv::Size(640, 480), CV_8UC3);
	cv::Mat frameGray(cv::Size(640, 480), CV_8UC1);
	cv::Mat frameDepth(cv::Size(640, 480), CV_16UC1);
	cv::Mat frameThres(cv::Size(640, 480), CV_8UC1);
	cv::Mat frameWall(cv::Size(640, 480), CV_8UC1);

	cout << "Flag CV_8UC3 = " << CV_8UC3 << endl;
	cout << "Flag CV_16UC1 = " << CV_16UC1 << endl;
	cout << "Flag CV_8UC1 = " << CV_8UC1 << endl;


	const std::string windowNames[] = {
										"RGB",
										"Gray scale",
										"Depth", 
										"Threshold",
										"Virtual Wall"
	};

	cv::namedWindow(windowNames[TITLE_RGB], cv::WINDOW_AUTOSIZE);
	cv::namedWindow(windowNames[TITLE_GRAY], cv::WINDOW_AUTOSIZE);
	cv::namedWindow(windowNames[TITLE_DEPTH], cv::WINDOW_AUTOSIZE);
	cv::namedWindow(windowNames[TITLE_THRES], cv::WINDOW_AUTOSIZE);
	cv::namedWindow(windowNames[TITLE_WALL], cv::WINDOW_AUTOSIZE);

	while (kinect.isValid()&& waitkey != 'q' )
	{

		kinect.getDepth(frameDepth);
		cv::imshow(windowNames[TITLE_RGB], frameDepth);

		cv::threshold(frameDepth, frameThres, 50, (2 << 16) - 1, cv::THRESH_BINARY_INV);
	
		cv::imshow(windowNames[TITLE_DEPTH], frameDepth);
		cv::imshow(windowNames[TITLE_THRES], frameThres);
		

		kinect.getRGB(frameColor);
		
		cv::cvtColor(frameColor, frameColor, cv::COLOR_BGR2RGB);
		cv::cvtColor(frameColor, frameGray, cv::COLOR_RGB2GRAY);
		
		frameGray.convertTo(frameGray, CV_8UC1);
		frameThres.convertTo(frameThres, CV_8UC1);

		frameWall = frameThres & frameGray;
	

		cv::imshow(windowNames[TITLE_GRAY], frameGray);
		cv::imshow(windowNames[TITLE_WALL], frameWall);
		cv::imshow(windowNames[TITLE_RGB], frameColor);

			
		waitkey = (char) cv::waitKey(1);

			
	}

	cv::destroyAllWindows();
	
	cout << "Shutdown kinect" << endl;
	
	kinect.close();
	OpenNI::shutdown();

    return EXIT_SUCCESS;
}

