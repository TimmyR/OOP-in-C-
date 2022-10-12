#include "Circle.h"

#include <iostream>

// Member functions
void Circle::info() const
{
	std::cout << "Circle:\n";
	std::cout << "	Radius= " << semiaxis_1 << std::endl;
	std::cout << "	Circumference= " << perimeter() << std::endl;
	std::cout << "	Area= " << area() << std::endl;
}