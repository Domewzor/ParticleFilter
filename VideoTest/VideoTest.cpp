// VideoTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <random>
#include <stdio.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "Particle.h"

int main(int argc, char* argv[])
{
	int N = 100;
	//float arr[200];
	//float *p = new float[N];
	Particle *p = new Particle[N];
	int pos = 58;
	int t = 75;

	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<int>  distrX(0, 640);
	std::uniform_int_distribution<int>  distrY(0, 480);
	
	cv::Mat src_img1;

	src_img1 = cv::imread("square30_1.jpg", 1);

	int k = 0, x = 0, y = 0;

	for (int i = 0; i < N; i++)
	{
		p[i].SetProps(distrX(generator), distrY(generator), 0);		
		//printf("%d, %s", p[i].GetX(), p[i].ToString());
		x = p[i].GetX();
		y = p[i].GetY();
		std::cout << i << ": " << x << ", " << y << std::endl;
		cv::Point3_<uchar>* p = src_img1.ptr<cv::Point3_<uchar> >(y, x);
		p->x = 255;
		p->y = 255;
		p->z = 255;
		cv::circle(src_img1, cv::Point(x, y), 2, cv::Scalar(0, 0, 255), -1, 8, 0);
		//src_img1.at<cv::Vec3b>(cv::Point(x, y)) = color;
		//src_img1.at<uchar>(p[i].GetX(), p[i].GetY()) = static_cast<uchar>(255);
	}
	
	printf("\n");

	cv::imshow("SOURCE", src_img1);
	cv::waitKey(0);
	
	return 0;
}

// video usage
/*
cv::VideoCapture cap("square30.avi");

if (!cap.isOpened())  // if not success, exit program
{
printf("Cannot open the video file\n");
return -1;
}

//cap.set(CV_CAP_PROP_POS_MSEC, 300); //start the video at 300ms

double fps = cap.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video

printf("Frames per second : %f", fps);

cv::namedWindow("MyVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

while (1)
{
cv::Mat frame;

bool bSuccess = cap.read(frame); // read a new frame from video

if (!bSuccess) //if not success, break loop
{
printf("Cannot read the frame from video file");
break;
}

cv::imshow("MyVideo", frame); //show the frame in "MyVideo" window

if (cv::waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
{
printf("esc key is pressed by user");
break;
}
}
*/