#ifndef CIRCLE_H
#define CIRCLE_H

#include "Ellipse.h"

class Circle : public Ellipse
{
public:
	Circle() = default;
	Circle(const double radius) : Ellipse(radius, radius) {};
	~Circle() {};

	void info() const override;
};

#endif