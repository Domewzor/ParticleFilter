#include <stdio.h>
#include <string.h>
#include <opencv2/highgui/highgui.hpp>

#pragma once
class Particle
{
private:
	int x, y;
	float weight;
	float colorDist;
	cv::Mat histR;
	cv::Mat histG;
	cv::Mat histB;
public:
	Particle();
	Particle(int, int);
	Particle(int, int, double);
	void SetProps(int, int, double);
	int GetX();
	int GetY();
	cv::Point GetPoint();
	float GetWeight();
	void SetWeight(float);
	float getColorDist();
	void setColorDist(float);
	void SetHist(cv::Mat, cv::Mat, cv::Mat);
	cv::Mat GetHistR();
	cv::Mat GetHistG();
	cv::Mat GetHistB();
	char* ToString();
	virtual ~Particle();
};

