#pragma once
#include <math.h>
#include <Windows.h>

class Simplex {
	int *perm;
public:
	Simplex();
	~Simplex();

	double Noise(double xpos, double ypos);
	double Turbulence(double xpos, double ypos, int octaves, double persistance=0.5);
};
