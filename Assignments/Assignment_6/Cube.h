#ifndef CUBE_H
#define CUBE_H

#include "Cuboid.h"

class Cube : public Cuboid
{
public:
	Cube() = default;
	Cube(const double side) : Cuboid(side, side, side) {};
	~Cube() {};

	void info() const override;
};

#endif