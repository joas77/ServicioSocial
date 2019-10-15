#include "Window.h"



Window::Window(cv::String winName, int frameHeight, int frameWidth, int winRows, int winColumns):
	mWinName(winName),
	mFrameHeight(frameHeight),
	mFrameWidth(frameWidth),
	mRows(winRows),
	mColumns(winColumns)
{
}

Window::~Window()
{
}
