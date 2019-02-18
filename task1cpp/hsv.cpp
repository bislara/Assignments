#include <opencv2/opencv.hpp> //Include file for every supported OpenCV function
#include "iostream"
using namespace std;
using namespace cv;

 int rhup=0,rhlo=0,rsup=0,rslo=0,rvup=0,rvlo=0;
 int bhup=0,bhlo=0,bsup=0,bslo=0,bvup=0,bvlo=0;
 int yhup=0,yhlo=0,ysup=0,yslo=0,yvup=0,yvlo=0;

int main( int argc, char** argv ) {

	Mat img,frame_HSV,red,blue,yellow,element,mask;
	img=imread("image.png");
	namedWindow( "original", WINDOW_AUTOSIZE );
	namedWindow( "red color", WINDOW_AUTOSIZE );
	namedWindow( "blue color", WINDOW_AUTOSIZE );
	namedWindow( "yellow color", WINDOW_AUTOSIZE );
	
	cvtColor(img,frame_HSV, CV_BGR2HSV);
	 rhup=18;rhlo=0;rsup=255;rslo=55;rvup=255;rvlo=0;
	 bhup=133;bhlo=79;bsup=255;bslo=171;bvup=255;bvlo=83;
	 yhup=60;yhlo=22;ysup=255;yslo=60;yvup=255;yvlo=200;
	
	 inRange(frame_HSV, Scalar(rhlo,rslo,rvlo), Scalar(rhup,rsup,rvup),red);
	 inRange(frame_HSV, Scalar(bhlo,bslo,bvlo), Scalar(bhup,bsup,bvup),blue);
	 inRange(frame_HSV, Scalar(yhlo,yslo,yvlo), Scalar(yhup,ysup,yvup),yellow);

	element = getStructuringElement(MORPH_CROSS,
                  Size(2 * 2 + 1, 2 * 2 + 1),
                  Point(-1, -1) );

        dilate(red,red,element);
	dilate(blue,blue,element);
	dilate(yellow,yellow,element);

	bitwise_and(img,img,red,mask=red);
        bitwise_and(img,img,blue,mask=blue);
        bitwise_and(img,img,yellow,mask=yellow);

	
	imshow("original",img);
	imshow("red color",red);
	imshow("blue color",blue);
	imshow("yellow color",yellow);

	int k=waitKey(0);
	if(k==27)
	{destroyAllWindows();}

}

