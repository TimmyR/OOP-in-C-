#include "Sphere.h"

#include <iostream>

// Member functions
void Sphere::info() const
{
	std::cout << "Sphere:\n";
	std::cout << "	Radius= " << semiaxis_1 << std::endl;
	std::cout << "	Surface area= " << area() << std::endl;
	std::cout << "	Volume= " << volume() << std::endl;
}