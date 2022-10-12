#include "Ellipse.h"

#include <cmath>
#include <iostream>

// Parametrised constructor
Ellipse::Ellipse(const double semiaxis_a, const double semiaxis_b)
{
	if (semiaxis_a < 0 || semiaxis_b < 0) {
		std::cout << "Cannot initialise shape (ellipse or circle) with dimensions of size less then 0.\n";
		semiaxis_1 = 0;
		semiaxis_2 = 0;
	} else {
		semiaxis_1 = semiaxis_a;
		semiaxis_2 = semiaxis_b;
	}
}

// Member functions
double Ellipse::perimeter() const
	// Calculated from approximation given by Srinivasa Ramanujan. 
	// Simplifies to 2*pi*radius for radius == semiaxis_1 == semiaxis_2.
{
	return (atan(1)*4) * ( 3*(semiaxis_1+semiaxis_2) - std::sqrt( (3*semiaxis_1 + semiaxis_2)*(semiaxis_1 + 3*semiaxis_2)));
}

double Ellipse::area() const
{
	return (atan(1)*4) * semiaxis_1 * semiaxis_2;
}

void Ellipse::info() const
{
	std::cout << "Ellipse:\n";
	std::cout << "	Semiaxes= " << semiaxis_1 << " and " << semiaxis_2 << std::endl;
	std::cout << "	Circumference= " << perimeter() << std::endl;
	std::cout << "	Area= " << area() << std::endl;
}