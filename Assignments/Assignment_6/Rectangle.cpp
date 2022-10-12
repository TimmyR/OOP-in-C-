#include "Rectangle.h"

#include <iostream>

// Parametrised constructor
Rectangle::Rectangle(const double side_a, const double side_b)
{
	if (side_a < 0 || side_b < 0) {
		std::cout << "Cannot initialise shape (rectangle or square) with dimensions of size less then 0.\n";
		side_1 = 0;
		side_2 = 0;
	} else {
		side_1 = side_a;
		side_2 = side_b;
	}
}

// Member functions
double Rectangle::perimeter() const
{
	return 2 * side_1 + 2 * side_2;
}

double Rectangle::area() const
{
	return side_1 * side_2;
}

void Rectangle::info() const
{
	std::cout << "Rectangle:\n";
	std::cout << "	Side lengths= " << side_1 << " and " << side_2 << std::endl;
	std::cout << "	Perimeter= " << perimeter() << std::endl;
	std::cout << "	Area= " << area() << std::endl;
}