#pragma once
class Particle
{
private:
	int x, y, weight;
public:
	Particle();
	Particle(int, int);
	Particle(int, int, int);
	void SetProps(int, int, int);
	int GetX();
	int GetY();
	int GetWeight();
	char* ToString();
	virtual ~Particle();
};

