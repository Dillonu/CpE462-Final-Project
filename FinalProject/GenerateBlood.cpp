#include "CpE462-Project.h"

Image* GenerateBlood(int width, int height) {
	// Initialize Variables:
	double zoom = 400.0;
	double persistance = 0.50;
	int octaves = 4;
	Image *terrain = new Image(width, height); // Output Map
	double noise, invZoom = 1.0 / zoom; // Calculation Variables
	double maxRadius = min(width, height)*0.5;
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

			// Convert from -1.0 to 1.0 to be 0.0 to 1.0:
			noise = (noise + 1.0) * 0.5;

			// Make sure the blot is in the middle of the image:
			noise = noise*(maxRadius - distance) / maxRadius;

			if (noise > 0.15) {
				// Output heightmap to image:
				(*terrain)[y][x].red = int((noise - 0.15) / 0.85*64.0) + 64;
				(*terrain)[y][x].green = 0;
				(*terrain)[y][x].blue = 0;
			} else{
				// Output heightmap to image:
				(*terrain)[y][x].red = 255;
				(*terrain)[y][x].green = 255;
				(*terrain)[y][x].blue = 255;
			}
		}
	}

	return terrain;
}