#ifndef SHAPE3D_H
#define SHAPE3D_H

#include "Shape.h"

#include <iostream>

class Shape3D : public Shape
	// Abstract base class for 3D shapes.
{
public:
	virtual ~Shape3D() {}

	double perimeter() const
	{
		std::cout << "Cannot calculate perimeter of 3D shape.\n";
		return 0;
	}
};

#endif