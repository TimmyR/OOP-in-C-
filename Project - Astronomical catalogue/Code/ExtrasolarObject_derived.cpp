#include "Angle.h"
#include "Angle_derived.h"
#include "Date.h"
#include "ExtrasolarObject_derived.h"

#include <iostream>
#include <string>

//Define static member variables - all classes
size_t Star::use_count{0};
size_t Galaxy::use_count{0};


// Star class
// Constructor
Star::Star(const std::string star_name, const std::string experiment, const std::string constellation, const std::string spectral_type, const double app_magnitude, const double stellar_mass, const double distance_pc, const Date obs_epoch, const RightAscension ra, const Angle ra_cent_change, const Declination dec, const Angle dec_cent_change)
{
	set_data(star_name, experiment, constellation, spectral_type, app_magnitude, stellar_mass, distance_pc, obs_epoch, ra, ra_cent_change, dec, dec_cent_change);
	use_count++;
}

std::string Star::get_object_type()
{
	return "star";
}

// Member functions
std::string Star::get_class_name() const
{
	return get_object_type();
}

size_t Star::get_use_count()
{
	return use_count;
}



// Galaxy class
// Constructor
Galaxy::Galaxy(const std::string name, const std::string experiment, const std::string constellation, const std::string hubble_type, const double app_magnitude, const double mass, const double distance_pc, const Date obs_epoch, const RightAscension ra, const Angle ra_cent_change, const Declination dec, const Angle dec_cent_change)
{
	set_data(name, experiment, constellation, hubble_type, app_magnitude, mass, distance_pc, obs_epoch, ra, ra_cent_change, dec, dec_cent_change);
	use_count++;
}

std::string Galaxy::get_object_type()
{
	return "galaxy";
}

// Member functions
std::string Galaxy::get_class_name() const
{
	return get_object_type();
}

size_t Galaxy::get_use_count()
{
	return use_count;
}
