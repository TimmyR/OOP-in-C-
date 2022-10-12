#ifndef CELESTIALOBJECT_H
#define CELESTIALOBJECT_H

#include "Angle_derived.h"
#include "Date.h"

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

class CelestialObject
	// Abstract base class for celestial objects.
{
public:
	CelestialObject() { use_count++; }
	virtual ~CelestialObject() { use_count--; };

	bool operator==(const CelestialObject& object) const;
	bool operator<(const CelestialObject& object) const;

	friend std::ostream& operator<<(std::ostream& os, const CelestialObject& object);
	friend std::istream& operator>>(std::istream& is, CelestialObject& object);

	std::string get_name();
	std::string get_experiment();
	virtual std::string get_class_name() const = 0;
	Date get_date();
	bool invalid_state();

	static size_t get_use_count();

protected:
	std::string name;
	std::string experiment;			
	double apparent_magnitude{std::nan("")};
	double mass{std::nan("")};	// in solar masses
	double distance{std::nan("")};	// in parsecs
	Date observation_epoch;
	RightAscension ra_observed;
	Declination dec_observed;

	bool incorrect_read{false};

	// iostream virtual body functions
	virtual void iostream_output_body(std::ostream& os) const = 0;
	virtual void iostream_input_body(std::istream& is) = 0;

private:
	static size_t use_count;
};

// Virtual friend functions implementation.
inline std::ostream& operator<<(std::ostream& os, const CelestialObject& object)
{
	object.iostream_output_body(os);
	return os;
}

inline std::istream& operator>>(std::istream& is, CelestialObject& object)
{
	object.iostream_input_body(is);
	return is;
}

#endif