#include "Cuboid.h"

#include <iostream>

// Parametrised constructor
Cuboid::Cuboid(const double side_a, const double side_b, const double side_c)
{
	if (side_a < 0 || side_b < 0 || side_c < 0) {
		std::cout << "Cannot initialise shape (cuboid or cube) with dimensions of size less then 0.\n";
		side_1 = 0;
		side_2 = 0;
		side_3 = 0;
	} else {
		side_1 = side_a;
		side_2 = side_b;
		side_3 = side_c;
	}
}

// Member functions
double Cuboid::area() const
{
	return 2*(side_1*side_2 + side_1*side_3 + side_2*side_3);
}

double Cuboid::volume() const
{
	return side_1 * side_2 * side_3;
}

void Cuboid::info() const
{
	std::cout << "Cuboid:\n";
	std::cout << "	Side lengths= " << side_1 << " and " << side_2 << " and " << side_3 << std::endl;
	std::cout << "	Surface area= " << area() << std::endl;
	std::cout << "	Volume= " << volume() << std::endl;
}