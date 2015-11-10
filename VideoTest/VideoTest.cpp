// VideoTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <random>
#include <stdio.h>
#include <iostream>
//#include <opencv2/highgui/highgui.hpp>
#include "Particle.h"

int main(int argc, char* argv[])
{
	int N = 50;
	float arr[200];
	//float *p = new float[N];
	Particle *p = new Particle[N];
	int pos = 58;
	int t = 75;

	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<int>  distr(0, 200);
	
	int k = 0;

	for (int i = 0; i < N; i++)
	{
		p[i].SetProps(distr(generator), 0, 0);		
		//printf("%d, %s", p[i].GetX(), p[i].ToString());
		std::cout << p[i].GetX() << std::endl;
		//p[i] = k;
	}
		


	printf("\n");
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