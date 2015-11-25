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

double Particle::GetWeight()
{
	return weight;
}

void Particle::SetWeight(double w)
{
	weight = w;
}

char* Particle::ToString()
{
	return "Particle";
}

Particle::~Particle()
{
}
