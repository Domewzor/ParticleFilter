// VideoTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <random>
#include <stdio.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\opencv.hpp>
#include "Particle.h"

float distance(Particle, cv::Vec3b, int, int);
float probability(float);
float normal_pdf(float, float, float);

// TODO Rozdelany rozdil histogramu

int main(int argc, char* argv[])
{
	int N = 100;
	//float arr[200];
	//float *p = new float[N];
	Particle *particles = new Particle[N];
	bool *acceptableP = new bool[N];
	int t = 75;	
	
	cv::Mat src_img1;

	//src_img1 = cv::imread("square30_2.jpg", 1);
	//src_img1 = cv::imread("snapshot1.jpg", 1);
	src_img1 = cv::imread("test1.jpg", 1);

	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	//std::normal_distribution<double> distrX(315, 50);
	//std::normal_distribution<double> distrY(160, 50);
	std::normal_distribution<double> distrX(265, 100);
	std::normal_distribution<double> distrY(225, 100);

	//std::uniform_int_distribution<> distrX(0, 640 - 1);
	//std::uniform_int_distribution<> distrY(0, 480 - 1);

	int k = 0, x = 0, y = 0;
	int width = src_img1.cols;
	int height = src_img1.rows;
	int objH = 160;
	int objW = 160;
	float wSum = 0, dSum = 0;

	/*/// Separate the image in 3 places ( B, G and R )
	std::vector<cv::Mat> bgr_planes;
	cv::split(src_img1, bgr_planes);

	/// Establish the number of bins
	int histSize = 64;

	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 };
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	cv::Mat b_hist, g_hist, r_hist;
	cv::Mat b_histTemplate, g_histTemplate, r_histTemplate;
	cv::Mat mask(height, width, CV_8UC1);
	cv::Mat maskTemplate = cv::Mat::zeros(height, width, CV_8UC1);
	
	for (int i = 186; i <= 346; i++)
	{
		for (int j = 143; j <= 303; j++)
		{
			maskTemplate.at<uchar>(i, j) = 1;
		}
	}

	/// Compute the histograms:
	cv::calcHist(&bgr_planes[0], 1, 0, maskTemplate, b_histTemplate, 1, &histSize, &histRange, uniform, accumulate);
	cv::calcHist(&bgr_planes[1], 1, 0, maskTemplate, g_histTemplate, 1, &histSize, &histRange, uniform, accumulate);
	cv::calcHist(&bgr_planes[2], 1, 0, maskTemplate, r_histTemplate, 1, &histSize, &histRange, uniform, accumulate);*/

	// Iterating through all generated particles
	for (int i = 0; i < N; i++)
	{		
		float prob = 0;
		// Sets properties of particles, uses uniform distribution across the picture		
		int x = distrX(generator);
		int y = distrY(generator);

		if (x < 0) x = 0;
		if (x > width) x = width - 1;
		if (y < 0) y = 0;
		if (y > height) y = height - 1;

		particles[i].SetProps(x, y, 1 / N);
				
		//printf("test1; x: %d, y: %d\n", x, y);

		/*mask = cv::Mat::zeros(height, width, CV_8UC1);

		for (int j = y - objH / 2; j < y + objH / 2; j++)
		{
			for (int i = x - objW / 2; i < x + objW / 2; i++)
			{
				if (j < 0 || i < 0 || j >= height || i >= width)
					continue;

				mask.at<uchar>(j, i) = 1;
			}
		}

		
		/// Compute the histograms:
		cv::calcHist(&bgr_planes[0], 1, 0, mask, b_hist, 1, &histSize, &histRange, uniform, accumulate);
		cv::calcHist(&bgr_planes[1], 1, 0, mask, g_hist, 1, &histSize, &histRange, uniform, accumulate);
		cv::calcHist(&bgr_planes[2], 1, 0, mask, r_hist, 1, &histSize, &histRange, uniform, accumulate);*/

		// Gets color of pixel where particle is
		cv::Vec3b particleColor = src_img1.at<cv::Vec3b>(y, x);
		
		//printf("test2\n");

		float colorDist = distance(particles[i], particleColor, src_img1.cols, src_img1.rows);

		prob = probability(colorDist);
		
		
		//double pR = cv::compareHist(r_hist, r_histTemplate, CV_COMP_BHATTACHARYYA);
		//double pG = cv::compareHist(g_hist, g_histTemplate, CV_COMP_BHATTACHARYYA);
		//double pB = cv::compareHist(b_hist, b_histTemplate, CV_COMP_BHATTACHARYYA);

		//prob = sqrt(pR * pR + pG * pG + pB * pB);
		wSum += prob;
		

		particles[i].SetWeight(prob);
		
	}

	std::sort(particles, particles + N, [](Particle & a, Particle & b) -> bool { return a.GetWeight() < b.GetWeight(); });

	for (int i = 0; i < N; i++)
	{
		x = particles[i].GetX();
		y = particles[i].GetY();
		particles[i].SetWeight(particles[i].GetWeight() / wSum);
		std::cout << i << ": " << x << ", " << y;
		std::cout << "; " << particles[i].GetWeight() << std::endl;

		//printf("test3\n");
		// draws a bigger dot for a particle
		if (particles[i].GetWeight() > 0)
		{
			cv::circle(src_img1, cv::Point(x, y), 2, cv::Scalar(255, 0, 0), -1, 8, 0);
		}
		else
			cv::circle(src_img1, cv::Point(x, y), 2, cv::Scalar(255, 255, 0), -1, 8, 0);
		
	}

	std::cout << wSum;
	
	printf("\n");

	//// Draw the histograms for B, G and R
	//int hist_w = 512; int hist_h = 400;
	//int bin_w = cvRound((double)hist_w / histSize);

	//cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));

	///// Normalize the result to [ 0, histImage.rows ]
	//normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
	//normalize(g_hist, g_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
	//normalize(r_hist, r_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());

	///// Draw for each channel
	//for (int i = 1; i < histSize; i++)
	//{
	//	line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
	//		cv::Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
	//		cv::Scalar(255, 0, 0), 2, 8, 0);
	//	line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
	//		cv::Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
	//		cv::Scalar(0, 255, 0), 2, 8, 0);
	//	line(histImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
	//		cv::Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
	//		cv::Scalar(0, 0, 255), 2, 8, 0);
	//}

	///// Display
	//cv::namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
	//cv::imshow("calcHist Demo", histImage);

	cv::imshow("SOURCE", src_img1);
	cv::waitKey(0);

	delete[] particles;
	delete[] acceptableP;
	
	return 0;
}

float distance(Particle p, cv::Vec3b particleColor, int imgWidth, int imgHeight)
{
	cv::Scalar referenceColor = { 0, 0, 255 };
	cv::Scalar distanceVector = { 255, 255, 255 };
	cv::Point loc = p.GetPoint();

	if (loc.x >= 0 && loc.x < imgWidth && loc.y >= 0 && loc.y < imgHeight)
	{
		distanceVector = { referenceColor[0] - particleColor[0],
			referenceColor[1] - particleColor[1],
			referenceColor[2] - particleColor[2] };
	}

	float distance = sqrt(distanceVector[0] * distanceVector[0] + distanceVector[1] * distanceVector[1] + distanceVector[2] * distanceVector[2]);

	return distance;
}

float probability(float distance)
{
	int mean = 128;
	int stdDev = 6;

	/*double constAddFactor = log(sqrt(2 * CV_PI) * stdDev);
	double constMulFactor = -1 / (2 * stdDev * stdDev);
	double probability = constAddFactor + constMulFactor * distance;*/

	float prob = normal_pdf(distance, mean, stdDev);

	prob *= 100 / 0.398422;

	return prob;
}

float normal_pdf(float x, float m, float s)
{
	static const float inv_sqrt_2pi = 0.3989422804014327;
	float a = (x - m) / s;

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