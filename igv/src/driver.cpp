#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <igv/drivedata.h>
#include <cstring>
using namespace cv;
using namespace std;

int shp=3;

int iLowH = 0;int iHighH = 179;
int iLowS = 0;int iHighS = 255;
int iLowV = 0;int iHighV = 255;

int main(int argc, char** argv)
{
	  ros::init(argc, argv, "drive_pub");
	  ros::NodeHandle nh;

	  ros::Publisher pub = nh.advertise<igv::drivedata>("drive_pub", 1000);
	  
	  //VideoCapture cap("http://10.175.169.202:8080/videofeed?dummy=param.mjpg");
	  VideoCapture cap(1);

	  if ( !cap.isOpened() )
	    {
		 std::cout << "Cannot open the video file" << std::endl;
		 return -1;
	    }

  	  namedWindow("Raw Feed", CV_WINDOW_NORMAL);
	  namedWindow("Threshold feed", CV_WINDOW_NORMAL);
	  namedWindow("Tracking", CV_WINDOW_NORMAL);
	  namedWindow("Control", CV_WINDOW_NORMAL);

	  cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	  cvCreateTrackbar("HighH", "Control", &iHighH, 179);

	  cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	  cvCreateTrackbar("HighS", "Control", &iHighS, 255);

	  cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	  cvCreateTrackbar("HighV", "Control", &iHighV, 255);

	  int cx,cy;float ar;
	  char drv='k';

	  ros::Rate loop_rate(30);
	  while (nh.ok())
		{
		Mat frame;
        	bool bSuccess = cap.read(frame);
		if (!bSuccess)
        	{
             	std::cout << "Cannot read a frame from video stream" << std::endl;
             	break;
        	}
		
		Mat hsv,thresh;
		cvtColor(frame, hsv, CV_BGR2HSV);

		inRange(hsv, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), thresh);

		Rect bounding_rect;
		vector<vector<Point> > contours;
    		vector<Vec4i> hierarchy;
    		findContours( thresh, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
		vector<Point> approx;

		for (int i = 0; i < contours.size(); i++)
		{
			approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
			if (fabs(contourArea(contours[i])) < 100 || !isContourConvex(approx))
			continue;
			if (approx.size() == shp)
			{
				Moments mom = moments(contours[i]);
				cy=mom.m01/mom.m00,cx=mom.m10/mom.m00;ar=mom.m00;
				//cout<<"contour X "<<cx<<" contour Y "<<cy<<"contour area "<<mom.m00<<endl;
				bounding_rect=boundingRect(contours[i]);
			}
		}

		Mat dst=frame.clone();
		rectangle(dst, bounding_rect,  Scalar(255,0,0),2, 8,0);
		imshow( "Raw Feed", frame );
		imshow( "Threshold feed", thresh );
		imshow( "Tracking", dst );
		if (waitKey(30) == 27)
       		{
            		std::cout << "esc key is pressed by user" << std::endl;
            		break;
       		}

		if(cx>(0.75*frame.cols))
		drv='R';
		else if(cx<(0.25*frame.cols))
		drv='L';
		else if(ar>5000)
		drv='B';
		else if(ar<3000)
		drv='F';
		else
		drv='S';
                ROS_INFO("%c ",drv);
		igv::drivedata msg;
		msg.num1=cx;msg.num2=cy;msg.drive=drv;
		pub.publish(msg);

	    	ros::spinOnce();
	    	loop_rate.sleep();
	  	}
}
