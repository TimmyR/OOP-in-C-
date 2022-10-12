#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Shape2D.h"

class Ellipse : public Shape2D
{
public:
	Ellipse() = default;
	Ellipse(const double semiaxis_1, const double semiaxis_2);
	~Ellipse() {};

	double perimeter() const override;
	double area() const override;
	void info() const override;

protected:
	double semiaxis_1{0};
	double semiaxis_2{0};
};

#endif