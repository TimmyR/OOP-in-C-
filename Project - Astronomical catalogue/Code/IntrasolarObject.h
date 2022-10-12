#ifndef INTRASOLAROBJECT_H
#define INTRASOLAROBJECT_H

#include "Angle.h"
#include "Angle_derived.h"
#include "CelestialObject.h"

#include <iostream>
#include <string>

class IntrasolarObject : public CelestialObject
	// Abstract base class for objects inside the solar system.
{
public:
	IntrasolarObject() { use_count++; }
	virtual ~IntrasolarObject() { use_count--; };

	static size_t get_use_count();

protected:
	void set_data(const std::string p_name, const std::string p_experiment, const double p_app_magnitude, const double p_mass, const double p_distance_pc, const Date p_observational_epoch, const RightAscension p_ra, const Declination p_dec);

	void iostream_input_body(std::istream& is) override;
	void iostream_output_body(std::ostream& os) const override;

private:
	static size_t use_count;
};

#endif