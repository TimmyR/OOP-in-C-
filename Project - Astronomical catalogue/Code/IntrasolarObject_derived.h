#ifndef INTRASOLAROBJECT_DERIVED_H
#define INTRASOLAROBJECT_DERIVED_H

#include "Angle_derived.h"
#include "Date.h"
#include "IntrasolarObject.h"

#include <iostream>
#include <string>


class Sun : public IntrasolarObject
	// Class for the Sun.
{
public:
	Sun() { use_count++; };
	Sun(const std::string name, const std::string experiment, const double app_magnitude, const double mass, const double distance_pc, const Date obs_epoch, const RightAscension ra, const Declination dec);
	~Sun() { use_count--; };

	static std::string get_object_type();
	std::string get_class_name() const override;

	static size_t get_use_count();

private:
	static size_t use_count;
};


class Planet : public IntrasolarObject
	// Class for planets.
{
public:
	Planet() { use_count++; };
	Planet(const std::string name, const std::string experiment, const double app_magnitude, const double mass, const double distance_pc, const Date obs_epoch, const RightAscension ra, const Declination dec);
	~Planet() { use_count--; };

	static std::string get_object_type();
	std::string get_class_name() const override;

	static size_t get_use_count();

private:
	static size_t use_count;
};


class Comet : public IntrasolarObject
	// Class for stars excluding the Sun.
{
public:
	Comet() { use_count++; };
	Comet(const std::string name, const std::string experiment, const double app_magnitude, const double mass, const double distance_pc, const Date obs_epoch, const RightAscension ra, const Declination dec);
	~Comet() { use_count--; };

	static std::string get_object_type();
	std::string get_class_name() const override;

	static size_t get_use_count();

private:
	static size_t use_count;
};


class Asteroid : public IntrasolarObject
	// Class for asteroids.
{
public:
	Asteroid() { use_count++; };
	Asteroid(const std::string name, const std::string experiment, const double app_magnitude, const double mass, const double distance_pc, const Date obs_epoch, const RightAscension ra, const Declination dec);
	~Asteroid() { use_count--; };

	static std::string get_object_type();
	std::string get_class_name() const override;

	static size_t get_use_count();

private:
	static size_t use_count;
};

#endif