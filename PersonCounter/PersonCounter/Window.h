#ifndef WINDOW_H
#define WINDOW_H

#include <opencv2/opencv.hpp> //TODO: add specific opencv h files

class Window
{
public:
	Window(cv::String winName, int frameHeight, int frameWidth, int rows=1, int columns=1);
	~Window();

private:
	int mFrameHeight;
	int mFrameWidth;
	int mRows;
	int mColumns;
	cv::String mWinName;

};

#endif WINDOW_H

