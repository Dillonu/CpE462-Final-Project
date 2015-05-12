#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

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