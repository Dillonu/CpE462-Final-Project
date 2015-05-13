#pragma once
#include <time.h>
#include <Windows.h>
#include "Image.h"
#include "Simplex.h"

Image* GenerateClouds(int width, int height, double zoom = 150.0, double persistance = 0.50, int octaves = 6) {
	// Initialize Variables:
	Image *terrain = new Image(width, height); // Output Map
	double noise, invZoom = 1.0 / zoom; // Calculation Variables
	int value;

	// Initialize Simplex Generator:
	srand(time(0) ^ rand()); // Initialize Random Seed
	Simplex generator = Simplex();

	// Loops through all the pixels
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			noise = generator.Turbulence(x*invZoom, y*invZoom, octaves, persistance);

			// Convert the -1.0 to 1.0 noise value to a 0 to 127 RGB value:
			value = int(noise * 64) + 64;
			if (value > 127) value = 127;
			if (value < 0) value = 0;

			// Output heightmap to image:
			(*terrain)[y][x].red = value + 128;
			(*terrain)[y][x].green = value + 128;
			(*terrain)[y][x].blue = 255;
		}
	}

	return terrain;
}