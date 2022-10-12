#include "Angle_derived.h"

#include <cmath>
#include <iostream>

// RightAscension members
// Constructors
RightAscension::RightAscension(const double angle, const std::string format) : Angle(angle, format)
{
	check_limits();
}

RightAscension::RightAscension(std::vector<double> angle, const std::string format) : Angle(angle, format)
{
	check_limits();
}

RightAscension::RightAscension(const Angle& copied_angle) : Angle(copied_angle)
{
	check_limits();
}

RightAscension::RightAscension(Angle&& moved_angle) noexcept : Angle(moved_angle)
{
	check_limits();
}

// Member functions
void RightAscension::check_limits()
	// Used to make sure right ascension is between 0 and 360 degrees.
{
	if (angle_rad < 0 || angle_rad > 8 * atan(1)) {
		std::cout << "Error: right ascension must be between hms 0 and hms 24.\n";
		angle_rad = std::nan("");
	}
}

void RightAscension::iostream_output_body(std::ostream& os) const
	// Outputs the default format for RightAscension: hours minutes seconds.
{
	if (angle_rad != angle_rad) {
		os << "nan";

	} else {
		int hours, minutes;
		double seconds;

		hours = int(angle_rad * 3 / atan(1));
		minutes = int((angle_rad * 3 / atan(1) - hours) * 60);
		seconds = ((angle_rad * 3 / atan(1) - hours) * 60 - minutes) * 60;

		os << "hms " << hours << " " << minutes << " " << seconds;
	}
}


//Declination members
//Constructors
Declination::Declination(const double angle, const std::string format) : Angle(angle, format)
{
	check_limits();
}

Declination::Declination(std::vector<double> angle, const std::string format) : Angle(angle, format)
{
	check_limits();
}

Declination::Declination(const Angle& copied_angle) : Angle(copied_angle)
{
	check_limits();
}

Declination::Declination(Angle&& moved_angle) noexcept : Angle(moved_angle)
{
	check_limits();
}


// Member functions
void Declination::check_limits()
	// Used to make sure declination is between -90 and 90 degrees.
{
	if (angle_rad < -2 * atan(1) || angle_rad > 2 * atan(1)) {
		std::cout << "Error: declination must be between d -90 and d 90.\n";
		angle_rad = std::nan("");
	}
}


void Declination::iostream_output_body(std::ostream& os) const
	// Outputs the default format for Declination: degrees minutes seconds.
{
	if (angle_rad != angle_rad) {
		os << "nan";

	} else {
		int degrees, minutes;
		double seconds;

		degrees = int(angle_rad * 45 / atan(1));
		minutes = int((angle_rad * 45 / atan(1) - degrees) * 60);
		seconds = ((angle_rad * 45 / atan(1) - degrees) * 60 - minutes) * 60;

		os << "dms " << degrees << " " << minutes << " " << seconds;
	}
}
