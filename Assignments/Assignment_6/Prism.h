#ifndef PRISM_H
#define PRISM_H

#include "Shape3D.h"
#include "Shape2D.h"
#include "Rectangle.h"

class Prism : public Shape3D
{
public:
	Prism() = default;
	Prism(Shape2D* prism_base, const double prism_depth);
	~Prism() {};

	double area() const override;
	double volume() const override;
	void info() const override;

protected:
	Shape2D* base{nullptr};
	double depth{0};
};

#endif