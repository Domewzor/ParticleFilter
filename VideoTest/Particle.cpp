#include "stdafx.h"
#include "Particle.h"
#include <stdio.h>
#include <string.h>

Particle::Particle() : Particle(0, 0)
{
}

Particle::Particle(int xPos, int yPos) : x{ xPos }, y{ yPos }
{
	weight = 0;
}

Particle::Particle(int xPos, int yPos, int w) : x{ xPos }, y{ yPos }, weight{ w }
{
}

void Particle::SetProps(int xPos, int yPos, int w)
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

char* Particle::ToString()
{
	return "Particle";
}

Particle::~Particle()
{
}
