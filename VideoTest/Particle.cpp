#include "stdafx.h"
#include "Particle.h"


Particle::Particle() : Particle(0, 0)
{
}

Particle::Particle(int xPos, int yPos) : x{ xPos }, y{ yPos }
{
	weight = 0;
}

Particle::Particle(int xPos, int yPos, double w) : x{ xPos }, y{ yPos }, weight{ w }
{
}

void Particle::SetProps(int xPos, int yPos, double w)
{
	x = xPos;
	y = yPos;
	weight = w;
}

int Particle::GetX()
{
	return x;
}

int Particle::GetY()
{
	return y;
}

cv::Point Particle::GetPoint()
{
	return cv::Point(x, y);
}

float Particle::GetWeight()
{
	return weight;
}

void Particle::SetWeight(float w)
{
	weight = w;
}

float Particle::getColorDist()
{
	return colorDist;
}

void Particle::setColorDist(float cDist)
{
	colorDist = cDist;
}

void Particle::SetHist(cv::Mat histMatR, cv::Mat histMatG, cv::Mat histMatB)
{
	histR = histMatR;
	histG = histMatG;
	histB = histMatB;
}

cv::Mat Particle::GetHistR()
{
	return histR;
}

cv::Mat Particle::GetHistG()
{
	return histG;
}

cv::Mat Particle::GetHistB()
{
	return histB;
}

char* Particle::ToString()
{
	return "Particle";
}

Particle::~Particle()
{
}
