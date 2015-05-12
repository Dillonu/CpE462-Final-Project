#pragma once
#include <math.h>
#include <time.h>
#include <Windows.h>
#include "Image.h"
#include "Simplex.h"

Image* GenerateSand(int width, int height, double xFactor = 5.0 / 1000.0, double yFactor = 12.0 / 1000.0, double turbFactor = 1.0 / 800.0, double turbPower = 0.5, int turbSize = 10) {
	// Initialize Variables:
	Image *terrain = new Image(width, height); // Output Map
	double noise, amplitude; // Calculation Variables
	int value;
	const double PI = 3.141592653589793238463;

	// Initialize Simplex Generator:
	srand(time(0) ^ rand()); // Initialize Random Seed
	Simplex generator = Simplex();

	// Loops through all the pixels
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			double xyValue = x*xFactor + y*yFactor + turbPower*generator.Turbulence(x*turbFactor, y*turbFactor, turbSize);
			noise = fabs(sin(xyValue*PI)) + generator.Turbulence(x, y, turbSize)*0.05;
			noise = sqrt(1.0 - noise);
			/*if (noise < 0.5) {
				noise = 2.0*noise*noise;
			} else {
				noise = sqrt(2.0 * noise - 1.0)*0.5 + 0.5;
			}*/
			// Convert the 0.0 to 1.0 noise value to a 0 to 255 RGB value:
			value = int(noise * 50) + 90;
			if (value > 140) value = 140;
			if (value < 90) value = 90;

			// Output heightmap to image:
			(*terrain)[y][x].red = value * 1.57;
			(*terrain)[y][x].green = value * 1.35;
			(*terrain)[y][x].blue = value * 1;
		}
	}

	return terrain;
}