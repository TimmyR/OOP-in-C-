#include "Angle_derived.h"
#include "Date.h"
#include "IntrasolarObject_derived.h"

#include <string>

//Define static member variables - all classes
size_t Sun::use_count{0};
size_t Planet::use_count{0};
size_t Comet::use_count{0};
size_t Asteroid::use_count{0};

// Sun class
Sun::Sun(const std::string name, const std::string experiment, const double app_magnitude, const double mass, const double distance_pc, const Date obs_epoch, const RightAscension ra, const Declination dec)
{
	set_data(name, experiment, app_magnitude, mass, distance_pc, obs_epoch, ra, dec);
	use_count++;
}

std::string Sun::get_object_type()
{
	return "Sun";
}

std::string Sun::get_class_name() const
{
	return get_object_type();
}

size_t Sun::get_use_count()
{
	return use_count;
}


// Planet class
Planet::Planet(const std::string name, const std::string experiment, const double app_magnitude, const double mass, const double distance_pc, const Date obs_epoch, const RightAscension ra, const Declination dec)
{
	set_data(name, experiment, app_magnitude, mass, distance_pc, obs_epoch, ra, dec);
	use_count++;
}

std::string Planet::get_object_type()
{
	return "planet";
}

std::string Planet::get_class_name() const
{
	return get_object_type();
}

size_t Planet::get_use_count()
{
	return use_count;
}


// Comet class
Comet::Comet(const std::string name, const std::string experiment, const double app_magnitude, const double mass, const double distance_pc, const Date obs_epoch, const RightAscension ra, const Declination dec)
{
	set_data(name, experiment, app_magnitude, mass, distance_pc, obs_epoch, ra, dec);
	use_count++;
}

std::string Comet::get_object_type()
{
	return "comet";
}

std::string Comet::get_class_name() const
{
	return get_object_type();
}

size_t Comet::get_use_count()
{
	return use_count;
}


// Asteroid
Asteroid::Asteroid(const std::string name, const std::string experiment, const double app_magnitude, const double mass, const double distance_pc, const Date obs_epoch, const RightAscension ra, const Declination dec)
{
	set_data(name, experiment, app_magnitude, mass, distance_pc, obs_epoch, ra, dec);
	use_count++;
}

std::string Asteroid::get_object_type()
{
	return "asteroid";
}

std::string Asteroid::get_class_name() const
{
	return get_object_type();
}

size_t Asteroid::get_use_count()
{
	return use_count;
}
