#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include "Image.h"
#include "GenerateTerrain.h"
#include "GenerateMarble.h"
#include "GenerateClouds.h"
#include "GenerateSand.h"
#include "GenerateBlot.h"
#include "GenerateWood.h"

using namespace std;



int main() {
	string input;
	int width = 1024, height = 1024;

	cout << "Enter Width (default = " << width << "): ";

	getline(cin, input);
	if (!input.empty()) {
		istringstream stream(input);
		stream >> width;
	}
	if (width < 12) width = 12;
	else if (width > 4096) width = 4096;

	cout << "Enter Height (default = " << height << "): ";
	getline(cin, input);
	if (!input.empty()) {
		istringstream stream(input);
		stream >> height;
	}
	if (height < 12) height = 12;
	else if (height > 4096) height = 4096;

	clock_t startClock = clock(); // Measure the CPU clock cycles since last boot
	Image *map = GenerateWood(width, height);
	clock_t endClock = clock(); // Measure the CPU clock cycles since last boot

	double executionSeconds = double(endClock - startClock) / CLOCKS_PER_SEC;
	cout << "It took " << executionSeconds << " seconds to generate!" << endl;

	string filename = "heightmap.bmp";
	cout << "Enter filename (default = " << filename << "): ";
	getline(cin, input);
	if (!input.empty()) {
		istringstream stream(input);
		stream >> filename;
	}

	map->Save(filename);
	delete map;
	system("PAUSE");

	return 0;
}