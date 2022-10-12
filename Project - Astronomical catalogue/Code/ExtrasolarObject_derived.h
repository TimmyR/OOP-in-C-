#ifndef EXTRASOLAROBJECT_DERIVED_H
#define EXTRASOLAROBJECT_DERIVED_H

#include "Angle.h"
#include "ExtrasolarObject.h"

#include <iostream>
#include <string>


class Star : public ExtrasolarObject
	// Class for stars excluding the Sun.
{
public:
	Star() { use_count++; };
	Star(const std::string star_name, const std::string experiment, const std::string constellation, const std::string spectral_type, const double app_magnitude, const double stellar_mass, const double distance_pc, const Date obs_epoch, const RightAscension ra, const Angle ra_cent_change, const Declination dec, const Angle dec_cent_change);
	~Star() { use_count--; };

	static std::string get_object_type();
	std::string get_class_name() const override;

	static size_t get_use_count();

private:
	static size_t use_count;

};


class Galaxy : public ExtrasolarObject
	// Class for galaxies.
{
public:
	Galaxy() { use_count++; };
	Galaxy(const std::string name, const std::string experiment, const std::string constellation, const std::string hubble_type, const double app_magnitude, const double mass, const double distance_pc, const Date obs_epoch, const RightAscension ra, const Angle ra_cent_change, const Declination dec, const Angle dec_cent_change);
	~Galaxy() { use_count--; };

	static std::string get_object_type();
	std::string get_class_name() const override;

	static size_t get_use_count();

private:
	static size_t use_count;

};

#endif
