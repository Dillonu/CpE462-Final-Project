#ifndef _CPE462PROJECT_H_
#define _CPE462PROJECT_H_
#include <algorithm>
#include <time.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <string>

using namespace std;

typedef unsigned char BYTE;

template <class T>
T sqr(T x) {
	return x*x;
}

struct Pixel {
	union {
		struct {
			BYTE red;
			BYTE green;
			BYTE blue;
		};
		BYTE data[3];
	};
};

class Image {
	int width;
	int height;
	Pixel **pixels;
public:

	Image(int width, int height);
	~Image();

	void Save(string name);

	Pixel* operator[](int y);
};

Image* GenerateBlood(int, int);
Image* GenerateBlot(int, int);
Image* GenerateClouds(int, int);
Image* GenerateMarble(int, int);
Image* GenerateSand(int, int);
Image* GenerateTerrain(int, int);
Image* GenerateWoodTop(int, int);
Image* GenerateWoodSide(int, int);


// Some of the code for this class was taken from: https://gist.github.com/Slipyx/2372043, and from http://webstaff.itn.liu.se/~stegu/simplexnoise/simplexnoise.pdf
// Specifically the Noise function. Everything else are custom edits (init, dealloc, turbulence).
class Simplex {
	int *perm;
public:
	Simplex();
	~Simplex();

	double Noise(double xpos, double ypos); // Taken from simplexnoise.pdf
	double Turbulence(double xpos, double ypos, int octaves, double persistance = 0.5);
};
#endif