#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape2D.h"

class Rectangle : public Shape2D
{
public:
	Rectangle() = default;
	Rectangle(const double side_1, const double side_2);
	~Rectangle() {};

	double perimeter() const override;
	double area() const override;
	void info() const override;

protected:
	double side_1{0};
	double side_2{0};
};

#endif