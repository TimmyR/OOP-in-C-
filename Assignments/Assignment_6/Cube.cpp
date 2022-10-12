#include "Cube.h"

#include <iostream>


// Member functions
void Cube::info() const
{
	std::cout << "Cube:\n";
	std::cout << "	Side lengths= " << side_1 << std::endl;
	std::cout << "	Surface area= " << area() << std::endl;
	std::cout << "	Volume= " << volume() << std::endl;
}