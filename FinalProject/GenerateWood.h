#pragma once
#include <math.h>
#include <time.h>
#include <Windows.h>
#include "Image.h"
#include "Simplex.h"

Image* GenerateWood(int width, int height){

	// Initialize Variables:
	Image *terrain = new Image(width, height); // Output Map
	double xValue, yValue, turb, distValue, sineValue;
	int value;
	const double PI = 3.141592653589793238463;

	double xyFactor = 10.0;
	double turbFactor = 1.0 / 800.0;
	double turbPower = 0.05;
	int octaves = 10;


	// Initialize Simplex Generator:
	srand(time(0) ^ rand()); // Initialize Random Seed
	Simplex generator = Simplex();

	// Loops through all the pixels
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			xValue = (x - width / 2)/((double)width);
			yValue = (y - height / 2) / ((double)height);
			turb = turbPower*generator.Turbulence(x*turbFactor, y*turbFactor, octaves);
			distValue = (sqrt(xValue * xValue + yValue * yValue) + turb);
			sineValue = 128*fabs(sin(2*distValue*PI*xyFactor));
			

			// Convert the 0.0 to 1.0 noise value to a 0 to 255 RGB value:
			value = int(sineValue);
			if (value > 255)
				value = 255;
			else if (value < 0)
				value = 0;

			// Output heightmap to image:
			(*terrain)[y][x].red = 80+value;
			(*terrain)[y][x].green = 30+value;
			(*terrain)[y][x].blue = 30;
		}
	}

	return terrain;
}