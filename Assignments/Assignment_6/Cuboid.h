#ifndef CUBOID_H
#define CUBOID_H

#include "Shape3D.h"

class Cuboid : public Shape3D
{
public:
	Cuboid() = default;
	Cuboid(const double side_a, const double side_b, const double side_c);
	~Cuboid() {};

	double area() const override;
	double volume() const override;
	void info() const override;

protected:
	double side_1{0};
	double side_2{0};
	double side_3{0};
};

#endif