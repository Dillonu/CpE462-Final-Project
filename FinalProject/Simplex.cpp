#include "CpE462-Project.h"

//(3.0-sqrt(3.0))/6.0
#define G2 (0.21132486540518711774542560974902)

int grad3[12][3] = {{1, 1, 0}, {-1, 1, 0}, {1, -1, 0},
{-1, -1, 0}, {1, 0, 1}, {-1, 0, 1},
{1, 0, -1}, {-1, 0, -1}, {0, 1, 1},
{0, -1, 1}, {0, 1, -1}, {0, -1, -1}};

double dot(int g[], double x, double y) {
	return g[0] * x + g[1] * y;
}


Simplex::Simplex() {
	perm = new int[512];
	for (int i = 0; i < 256; i++) {
		perm[i] = rand() % 256;
		perm[i + 256] = perm[i];
	}
}


Simplex::~Simplex() {
	delete perm;
}

double Simplex::Noise(double xin, double yin) {
	//double n0, n1, n2; // Noise contributions from the three corners
	// Skew the input space to determine which simplex cell we're in
	//double F2 = 0.5*(sqrt(3.0)-1.0);//0.36602540378443864676372317075294
	double s = (xin + yin)*0.36602540378443864676372317075294; // Hairy factor for 2D
	int i = int(xin + s);//floor(xin+s)
	int j = int(yin + s);//floor(yin+s)
	double t = (i + j)*G2;
	double X0 = i - t; // Unskew the cell origin back to (x,y) space
	double Y0 = j - t;
	double x0 = xin - X0; // The x,y distances from the cell origin
	double y0 = yin - Y0;
	// For the 2D case, the simplex shape is an equilateral triangle.
	// Determine which simplex we are in.
	int i1, j1; // Offsets for second (middle) corner of simplex in (i,j) coords
	if (x0>y0) { i1 = 1; j1 = 0; } // lower triangle, XY order: (0,0)->(1,0)->(1,1)
	else { i1 = 0; j1 = 1; } // upper triangle, YX order: (0,0)->(0,1)->(1,1)
	// A step of (1,0) in (i,j) means a step of (1-c,-c) in (x,y), and
	// a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
	// c = (3-sqrt(3))/6
	double x1 = x0 - i1 + G2; // Offsets for middle corner in (x,y) unskewed coords
	double y1 = y0 - j1 + G2;
	double x2 = x0 - 1.0 + 2.0 * G2; // Offsets for last corner in (x,y) unskewed coords
	double y2 = y0 - 1.0 + 2.0 * G2;
	// Work out the hashed gradient indices of the three simplex corners
	int ii = i & 255;
	int jj = j & 255;
	int gi0 = perm[ii + perm[jj]] % 12;
	int gi1 = perm[ii + i1 + perm[jj + j1]] % 12;
	int gi2 = perm[ii + 1 + perm[jj + 1]] % 12;
	// Calculate the contribution from the three corners
	double t0 = 0.5 - x0*x0 - y0*y0;
	if (t0<0) t0 = 0.0;
	else {
		t0 *= t0;
		t0 *= t0 * dot(grad3[gi0], x0, y0);
		//n0 = t0 * t0 * dot(grad3[gi0], x0, y0); // (x,y) of grad3 used for 2D gradient
	}
	double t1 = 0.5 - x1*x1 - y1*y1;
	if (t1<0) t1 = 0.0;
	else {
		t1 *= t1;
		t1 *= t1 * dot(grad3[gi1], x1, y1);
		//n1 = t1 * t1 * dot(grad3[gi1], x1, y1);
	}
	double t2 = 0.5 - x2*x2 - y2*y2;
	if (t2<0) t2 = 0.0;
	else {
		t2 *= t2;
		t2 *= t2 * dot(grad3[gi2], x2, y2);
		//n2 = t2 * t2 * dot(grad3[gi2], x2, y2);
	}
	// Add contributions from each corner to get the noise value.
	// The result is scaled to return values in the interval [-1,1].
	return 70.0 * (t0 + t1 + t2);
}

double Simplex::Turbulence(double xpos, double ypos, int octaves, double persistance) {
	double noise = 0.0;
	double amplitude = 1.0;
	int frequency = 1;

	for (int a = octaves; a; a--) {
		noise += this->Noise(frequency*xpos, frequency*ypos)*amplitude;
		amplitude *= persistance;
		frequency = frequency << 1;
	}

	return noise;
}