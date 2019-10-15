#include "Kinect.h"
#include <string>

namespace openni_wrapper 
{
	bool HandleStatus(openni::Status status)
	{
		bool isOk = status == openni::Status::STATUS_OK;
		
		if (!isOk)
		{
			cout << "ERROR: #" << status << ", " << openni::OpenNI::getExtendedError() << endl;
		}
		return isOk;
	}
	
	void printStatus(openni::Status status)
	{
		if (status != openni::Status::STATUS_OK)
		{
			std::cout << "FAIL: " << std::string( openni::OpenNI::getExtendedError() )<< endl;
		}
	}


	bool Kinect::mIsInitialized = false;

	Kinect::Kinect()
	{
		//TODO: check status 
		if (!mIsInitialized)
		{
			mStatus = openni::OpenNI::initialize();
		}
		//TODO: check that device is correctle opened
		open();
		mStatus = mColor.create(mDevice, openni::SENSOR_COLOR);
		mStatus = mDepth.create(mDevice, openni::SENSOR_DEPTH);
		mColor.start();
		mDepth.start();

		const openni::SensorInfo * pSensorDepthInfo = mDevice.getSensorInfo(openni::SENSOR_DEPTH);
		const openni::SensorInfo * pSensorColorInfo = mDevice.getSensorInfo(openni::SENSOR_COLOR);

		const openni::Array<openni::VideoMode>& videoModsDepth = pSensorDepthInfo->getSupportedVideoModes();

		for (size_t i = 0; i < videoModsDepth.getSize(); i++)
		{
			cout << "Video Depth resolution = (" << videoModsDepth[i].getResolutionX() << ","
				<< videoModsDepth[i].getResolutionY() << ")" << endl;

			cout << "VideoDepth FPS = " << videoModsDepth[i].getFps() << endl;
			cout << "Pixel Format = " << videoModsDepth[i].getPixelFormat() << endl;

		}


		mParamvideo.setResolution(640, 480);
		mParamvideo.setFps(30);
		mParamvideo.setPixelFormat(openni::PIXEL_FORMAT_DEPTH_1_MM);
		mDepth.setVideoMode(mParamvideo);
		mParamvideo.setPixelFormat(openni::PIXEL_FORMAT_RGB888);
		mColor.setVideoMode(mParamvideo);

		// If the depth/color synchronisation is not necessary, start is faster :
	//device.setDepthColorSyncEnabled(false);

	// Otherwise, the streams can be synchronized with a reception in the order of our choice :
		mDevice.setDepthColorSyncEnabled(true);
		mDevice.setImageRegistrationMode(openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR);

		

		mVideoStream[0] = &mDepth;
		mVideoStream[1] = &mColor;
		cout << "Kinect initialization completed" << endl;

		// to initialise frames
		mDepth.readFrame(&mDepthFrame);
		mColor.readFrame(&mColorFrame);

	}
	void Kinect::getRGB(cv::Mat & camRgb)
	{
		mColor.readFrame(&mColorFrame);
		camRgb.data = (uchar*)mColorFrame.getData();
	}
	void Kinect::getDepth(cv::Mat & camDepth)
	{
		mDepth.readFrame(&mDepthFrame);
		camDepth.data = (uchar*)mDepthFrame.getData();
	}
	bool Kinect::open()
	{
		mStatus = mDevice.open(openni::ANY_DEVICE);
		return mStatus == openni::Status::STATUS_OK;
	}
	bool Kinect::isValid()
	{
		return mDevice.isValid();
	}
	
	void Kinect::close()
	{
		mDepth.stop();
		mDepth.destroy();
		mColor.stop();
		mColor.destroy();
	}

	Kinect::~Kinect()
	{
		//TODO
	}
}