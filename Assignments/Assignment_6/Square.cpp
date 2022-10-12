#include "Square.h"

#include <iostream>

// Member functions
void Square::info() const
{
	std::cout << "Square:\n";
	std::cout << "	Side lengths= " << side_1 << std::endl;
	std::cout << "	Perimeter= " << perimeter() << std::endl;
	std::cout << "	Area= " << area() << std::endl;
}