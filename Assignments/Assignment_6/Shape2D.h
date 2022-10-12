#ifndef SHAPE2D_H
#define SHAPE2D_H

#include "Shape.h"

#include <iostream>

class Shape2D : public Shape
	// Abstract base class for 2D shapes
{
public:
	virtual ~Shape2D() {}

	double volume() const override
	{
		std::cout << "Cannot calculate volume of 2D shape.\n";
		return 0;
	}
};

#endif