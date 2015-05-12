#pragma once
#include <math.h>
#include <Windows.h>

// Some of the code for this class was taken from: https://gist.github.com/Slipyx/2372043, and from http://webstaff.itn.liu.se/~stegu/simplexnoise/simplexnoise.pdf
// Specifically the Noise function. Everything else are custom edits (init, dealloc, turbulence).
class Simplex {
	int *perm;
public:
	Simplex();
	~Simplex();

	double Noise(double xpos, double ypos); // Taken from simplexnoise.pdf
	double Turbulence(double xpos, double ypos, int octaves, double persistance=0.5);
};
