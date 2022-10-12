#ifndef SPHERE_H
#define SPHERE_H

#include "Ellipsoid.h"

class Sphere : public Ellipsoid
{
public:
	Sphere() = default;
	Sphere(const double radius) : Ellipsoid(radius, radius, radius) {};
	~Sphere() {};

	void info() const override;
};

#endif