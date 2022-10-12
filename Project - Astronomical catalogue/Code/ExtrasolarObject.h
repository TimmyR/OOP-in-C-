#ifndef EXTRASOLAROBJECT_H
#define EXTRASOLAROBJECT_H

#include "Angle.h"
#include "Angle_derived.h"
#include "CelestialObject.h"
#include "Date.h"

#include <iostream>
#include <string>

class ExtrasolarObject : public CelestialObject
	// Abstract base class for objects outside the solar system.
{
public:
	ExtrasolarObject() { use_count++; }
	virtual ~ExtrasolarObject() { use_count--; };

	static size_t get_use_count();

protected:
	std::string constellation{"NA"};
	std::string type{"NA"};
	Angle ra_yearly_change;
	Angle dec_yearly_change;

	void set_data(const std::string p_name, const std::string p_experiment, const std::string p_constellation, const std::string p_type, const double p_app_magnitude, const double p_mass, const double p_distance_pc, const Date p_observational_epoch, const RightAscension p_ra, const Angle p_ra_year_change, const Declination p_dec, const Angle p_dec_year_change);

	void iostream_input_body(std::istream& is) override;
	void iostream_output_body(std::ostream& os) const override;


private:
	static size_t use_count;
};

#endif