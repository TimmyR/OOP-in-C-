#include "Ellipsoid.h"

#include <cmath>
#include <iostream>

// Parametrised constructor
Ellipsoid::Ellipsoid(const double semiaxis_a, const double semiaxis_b, const double semiaxis_c)
{
	if (semiaxis_a < 0 || semiaxis_b < 0 || semiaxis_c < 0) {
		std::cout << "Cannot initialise shape (ellipsoid or sphere) with dimensions of size less then 0.\n";
		semiaxis_1 = 0;
		semiaxis_2 = 0;
		semiaxis_3 = 0;
	} else {
		semiaxis_1 = semiaxis_a;
		semiaxis_2 = semiaxis_b;
		semiaxis_3 = semiaxis_c;
	}
}

// Member functions
double Ellipsoid::area() const
	// Approximate surface area from https://en.wikipedia.org/wiki/Ellipsoid#Surface_area.
	// Simplifies to 4*pi*radius^2 for radius == semiaxis_1 == semiaxis_2 == semiaxis_3.
{
	const double p{1.6075};
	double inside_root{(std::pow(semiaxis_1 * semiaxis_2, p) + std::pow(semiaxis_1 * semiaxis_3, p) + std::pow(semiaxis_2 * semiaxis_3, p)) / 3};
	return 4*(atan(1)*4) * std::pow( inside_root, 1/p);
}

double Ellipsoid::volume() const
{
	return (4.0/3) * (atan(1)*4) * semiaxis_1 * semiaxis_2 * semiaxis_3;
}

void Ellipsoid::info() const
{
	std::cout << "Ellipsoid:\n";
	std::cout << "	Semiaxes= " << semiaxis_1 << " and " << semiaxis_2 << " and " << semiaxis_3 << std::endl;
	std::cout << "	Surface area= " << area() << std::endl;
	std::cout << "	Volume= " << volume() << std::endl;
}