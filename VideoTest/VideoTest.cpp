// VideoTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <random>
#include <stdio.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "Particle.h"

double probability(Particle, cv::Vec3b, int, int);
double normal_pdf(double, double, double);

int main(int argc, char* argv[])
{
	int N = 100;
	//float arr[200];
	//float *p = new float[N];
	Particle *p = new Particle[N];
	int pos = 58;
	int t = 75;

	
	
	cv::Mat src_img1;

	src_img1 = cv::imread("square30_1.jpg", 1);

	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<int>  distrX(0, src_img1.cols - 1);
	std::uniform_int_distribution<int>  distrY(0, src_img1.rows - 1);

	int k = 0, x = 0, y = 0;

	// Iterating through all generated particles
	for (int i = 0; i < N; i++)
	{
		// Sets properties of particles, uses uniform distribution across the picture
		p[i].SetProps(distrX(generator), distrY(generator), 0);	
		x = p[i].GetX();
		y = p[i].GetY();
		std::cout << i << ": " << x << ", " << y;

		// Gets color of pixel where particle is
		cv::Vec3b particleColor = src_img1.at<cv::Vec3b>(y, x);

		p[i].SetWeight(probability(p[i], particleColor, src_img1.cols, src_img1.rows));
		std::cout << "; " << p[i].GetWeight() << std::endl;

		// Visualization of particles
		// makes a white dot for a particle 
		/*cv::Point3_<uchar>* p = src_img1.ptr<cv::Point3_<uchar> >(y, x);
		p->x = 255;
		p->y = 255;
		p->z = 255;*/

		// draws a bigger dot for a particle
		cv::circle(src_img1, cv::Point(x, y), 2, cv::Scalar(0, 0, 255), -1, 8, 0);
		
	}
	
	printf("\n");

	cv::imshow("SOURCE", src_img1);
	cv::waitKey(0);
	
	return 0;
}

double probability(Particle p, cv::Vec3b particleColor, int imgWidth, int imgHeight)
{
	cv::Scalar referenceColor = { 1, 240, 253 };
	cv::Scalar distanceVector = { 255, 255, 255 };
	cv::Point loc = p.GetPoint();

	if (loc.x >= 0 && loc.x < imgWidth && loc.y >= 0 && loc.y < imgHeight)
	{
		distanceVector = { referenceColor[0] - particleColor[0],
			referenceColor[1] - particleColor[1],
			referenceColor[2] - particleColor[2] };
	}

	double distance = sqrt(distanceVector[0] * distanceVector[0] + distanceVector[1] * distanceVector[1] + distanceVector[2] * distanceVector[2]);

	//printf(" distance: %f", distance);

	int mean = 0;
	int stdDev = 1;

	double probability = normal_pdf(distance, mean, stdDev);

	return probability;
}

double normal_pdf(double x, double m, double s)
{
	static const double inv_sqrt_2pi = 0.3989422804014327;
	double a = (x - m) / s;

	return inv_sqrt_2pi / s * std::exp(-0.5f * a * a);
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