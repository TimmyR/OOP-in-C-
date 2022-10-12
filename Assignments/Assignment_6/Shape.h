#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>

class Shape
	// Abstract base class for 2D and 3D shapes.
{
public:
	virtual ~Shape() {}

	virtual double perimeter() const = 0;
	virtual double area() const = 0;
	virtual double volume() const = 0;
	virtual void info() const = 0;
};

#endif
