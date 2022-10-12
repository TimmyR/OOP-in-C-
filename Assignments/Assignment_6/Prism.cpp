#include "Prism.h"

#include <iostream>

// Parametrised constructor
Prism::Prism(Shape2D* prism_base, const double prism_depth)
{
	if (prism_depth < 0) {
		std::cout << "Cannot initialise shape (prism) with dimensions of size less then 0.\n";
		base =  nullptr;
		depth = 0;
	} else {
		base = prism_base;
		depth = prism_depth;
	}
}

// Member functions
double Prism::area() const
{
	if (base != nullptr) {
		return 2 * base->area() + base->perimeter() * depth;
	} else {
		return 0;
	}
}

double Prism::volume() const
{
	if (base != nullptr) {
		return base->area() * depth;
	} else {
		return 0;
	}
}

void Prism::info() const
{
	if (base != nullptr) {
		std::cout << "Prism:\n";
		std::cout << "	Base info-- ";
		base->info();
		std::cout << "\n	Prism depth= " << depth << std::endl;
		std::cout << "	Surface area= " << area() << std::endl;
		std::cout << "	Volume= " << volume() << std::endl;
	} else {
		std::cout << "Prism: not initialised.\n";
	}
}