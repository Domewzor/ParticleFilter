#include <stdio.h>
#include <string.h>
#include <opencv2/highgui/highgui.hpp>

#pragma once
class Particle
{
private:
	int x, y;
	double weight;
public:
	Particle();
	Particle(int, int);
	Particle(int, int, double);
	void SetProps(int, int, double);
	int GetX();
	int GetY();
	cv::Point GetPoint();
	double GetWeight();
	void SetWeight(double);
	char* ToString();
	virtual ~Particle();
};

