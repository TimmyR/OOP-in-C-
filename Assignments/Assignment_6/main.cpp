// Object-Oriented Programming in C++
// Assignment 6 - a class hierarchy for 2D and 3D shapes
// Timothe Rhein - 25/4/2022

#include "Circle.h"
#include "Cube.h"
#include "Cuboid.h"
#include "Ellipse.h"
#include "Ellipsoid.h"
#include "Prism.h"
#include "Rectangle.h"
#include "Shape.h"
#include "Sphere.h"
#include "Square.h"

#include <iostream>
#include <vector>


int main() 
{
	std::vector<Shape*> shapes;
	
	// Add 2D shapes
	shapes.push_back(new Square(5));
	shapes.push_back(new Rectangle(4, 6));
	shapes.push_back(new Circle(9));
	shapes.push_back(new Ellipse(1,5));
	// Add 3D shapes
	shapes.push_back(new Cube(4.3));
	shapes.push_back(new Cuboid(3, 4, 5));
	shapes.push_back(new Sphere(5));
	shapes.push_back(new Ellipsoid(8, 3, 6));
	// Add prism
	Square base{2};
	shapes.push_back(new Prism(&base, 6));

	// Output shape info
	std::cout << "Shape info:\n\n";
	for (auto i{shapes.begin()}; i < shapes.end(); i++) {
		(*i)->info();
		delete* i;
	}

	return 0;
}