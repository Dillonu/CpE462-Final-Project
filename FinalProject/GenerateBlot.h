#pragma once
#include <time.h>
#include <Windows.h>
#include "Image.h"
#include "Simplex.h"

template <class T>
T sqr(T x) {
	return x*x;
}

Image* GenerateBlot(int width, int height, double zoom = 400.0, double persistance = 0.50, int octaves = 4) {
	// Initialize Variables:
	Image *terrain = new Image(width, height); // Output Map
	double noise, invZoom = 1.0 / zoom; // Calculation Variables
	double maxDistance = min(width, height)*0.5;
	int value;

	// Initialize Simplex Generator:
	srand(time(0) ^ rand()); // Initialize Random Seed
	Simplex generator = Simplex();

	// Loops through all the pixels
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			double xdis = sqr(x - width / 2);
			double ydis = sqr(y - height / 2);
			double distance = sqrt(xdis + ydis);
			noise = generator.Turbulence(x*invZoom, y*invZoom, octaves, persistance);

			// Convert from -1.0 to 1.0 to be 0.0 to 4.0:
			noise = (noise + 1.0) / 0.5;

			// Make sure the blot is in the middle of the image:
			noise = noise*(maxDistance - distance) / maxDistance;

			// Convert to black and white:
			if (noise > 0.6) value = 0;
			else value = 255;

			// Output heightmap to image:
			(*terrain)[y][x].red = value;
			(*terrain)[y][x].green = value;
			(*terrain)[y][x].blue = value;
		}
	}

	return terrain;
}