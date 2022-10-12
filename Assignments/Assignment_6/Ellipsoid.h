#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include "Shape3D.h"

class Ellipsoid : public Shape3D
{
public:
	Ellipsoid() = default;
	Ellipsoid(const double semiaxis_a, const double semiaxis_b, const double semiaxis_c);
	~Ellipsoid() {};

	double area() const override;
	double volume() const override;
	void info() const override;

protected:
	double semiaxis_1{0};
	double semiaxis_2{0};
	double semiaxis_3{0};
};

#endif