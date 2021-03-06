#include "CpE462-Project.h"

int main() {
	string input;
	Image *map;
	int width = 1024, height = 1024;
	int choice = 1;

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

	cout << "Generate:\n";
	cout << "1: Marble\n";
	cout << "2: Terrain\n";
	cout << "3: Clouds\n";
	cout << "4: Sand\n";
	cout << "5: Blot\n";
	cout << "6: Blood\n";
	cout << "7: Wood - Top Grain\n";
	cout << "8: Wood - Side Grain\n";
	getline(cin, input);
	if (!input.empty()) {
		istringstream stream(input);
		stream >> choice;
	}
	
	clock_t startClock = clock(); // Measure the CPU clock cycles since last boot
	
	switch (choice){
	case 1:
		map = GenerateMarble(width, height);
		break;
	case 2:
		map = GenerateTerrain(width, height);
		break;
	case 3:
		map = GenerateClouds(width, height);
		break;
	case 4:
		map = GenerateSand(width, height);
		break;
	case 5:
		map = GenerateBlot(width, height);
		break;
	case 6:
		map = GenerateBlood(width, height);
		break;
	case 7:
		map = GenerateWoodTop(width, height);
		break;
	case 8:
		map = GenerateWoodSide(width, height);
		break;
	default:
		cout << "Try Again";
		return 1;
		break;

	}
	
	
	
	
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

	map->Save(filename.c_str());
	delete map;
	
	// The following code pauses the exe before exiting:
	cout << "Press any button to exit...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	return 0;
}