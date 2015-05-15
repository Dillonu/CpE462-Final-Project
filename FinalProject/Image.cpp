#include "CpE462-Project.h"

Image::Image(int width, int height) {// : red(width, height), green(width, height), blue(width, height) {
	this->width = width;
	this->height = height;
	this->pixels = (Pixel**)malloc(height*sizeof(Pixel*));
	for (int y = 0; y < height; y++) {
		this->pixels[y] = (Pixel*)calloc(width, sizeof(Pixel));
	}
}
Image::~Image() {
	for (int y = 0; y < this->height; y++) {
		free(this->pixels[y]);
	}
	free(this->pixels);
}

Pixel* Image::operator[](int y) {
	return this->pixels[y];
}


void Image::Save(string name) {
	// Initialize BMP Header:
	int size = (this->width)*(this->height + 1) * 3 + 0x36;
	char *bmp = (char*)malloc(size);
	bmp[0] = 'B';
	bmp[1] = 'M';
	(*(unsigned long int*)(bmp + 0x6)) = 0x0;
	(*(unsigned long int*)(bmp + 0xA)) = 0x36;
	(*(unsigned long int*)(bmp + 0xE)) = 0x28;
	(*(unsigned long int*)(bmp + 0x12)) = this->width;
	(*(unsigned long int*)(bmp + 0x16)) = this->height;
	(*(unsigned short int*)(bmp + 0x1A)) = 0x1;
	(*(unsigned short int*)(bmp + 0x1C)) = 0x18;
	(*(unsigned long int*)(bmp + 0x1E)) = 0x0;
	(*(unsigned long int*)(bmp + 0x26)) = 0x1712;
	(*(unsigned long int*)(bmp + 0x2A)) = 0x1712;
	(*(unsigned long int*)(bmp + 0x2E)) = 0x0;
	(*(unsigned long int*)(bmp + 0x32)) = 0x0;

	// Save Color Channels:
	int pos = 0x33, y = 0, x = 0;
	for (; y < this->height; y++) {
		for (x = 0; x < this->width; x++) {
			pos += 3;
			bmp[pos] = this->pixels[y][x].blue;
			bmp[pos + 1] = this->pixels[y][x].green;
			bmp[pos + 2] = this->pixels[y][x].red;
		}
	}

	// Finalize Header:
	(*(unsigned long int*)(bmp + 0x2)) = pos;
	(*(unsigned long int*)(bmp + 0x22)) = pos - 0x36;

	// Save Output to File:
	ofstream file;
	file.open(name.c_str(), ios::out | ios::binary | ios::trunc);
	if (file.is_open()) {
		file.write(bmp, size);
		file.close();
	} else {
		cout << "Failed to write to file " << name << "!" << endl;
	}

	// Free bmp memory:
	free(bmp);
}