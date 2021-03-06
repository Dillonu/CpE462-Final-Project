#include "CpE462-Project.h"

Image* GenerateMarble(int width, int height) {
	double xFactor = 5.0 / 1000.0; 
	double yFactor = 12.0 / 1000.0;
	double turbFactor = 1.0 / 800.0; 
	double turbPower = 3.0;
	int octaves = 10;
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
			double xyValue = x*xFactor + y*yFactor + turbPower*generator.Turbulence(x*turbFactor, y*turbFactor, octaves);
			noise = fabs(sin(xyValue*PI));

			// Convert the 0.0 to 1.0 noise value to a 0 to 255 RGB value:
			value = int(noise * 256);
			if (value > 255) value = 255;
			if (value < 0) value = 0;

			// Output heightmap to image:
			(*terrain)[y][x].red = value;
			(*terrain)[y][x].green = value;
			(*terrain)[y][x].blue = value;
		}
	}

	return terrain;
}