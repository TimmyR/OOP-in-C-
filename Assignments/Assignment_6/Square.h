#ifndef SQUARE_H
#define SQUARE_H

#include "Rectangle.h"

class Square : public Rectangle
{
public:
	Square() = default;
	Square(const double side) : Rectangle(side, side) {};
	~Square() {};

	void info() const override;
};

#endif
