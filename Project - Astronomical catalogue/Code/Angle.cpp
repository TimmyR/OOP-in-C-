#include "Angle.h"

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

// Constructors
Angle::Angle(const double angle, const std::string format)
	// Input as either radian ("r") or degree ("d") defined by the format variable. 
{
	set_angle(angle, format);
}

Angle::Angle(std::vector<double> angle, const std::string format)
	// Input as either degrees minutes seconds ("dms") or hours minutes seconds ("hms") defined by the format variable. 
{
	set_angle(angle, format);
}

Angle::Angle(const Angle& copied_angle)
{
	angle_rad = copied_angle.angle_rad;
}

Angle::Angle(Angle&& moved_angle) noexcept
{
	angle_rad = moved_angle.angle_rad;
	moved_angle.angle_rad = 0;
}


// Overloaded operators
Angle& Angle::operator=(const Angle& copied_angle)
{
	if (this != &copied_angle) {
		angle_rad = copied_angle.angle_rad;
	}
	return *this;
}

Angle& Angle::operator=(Angle&& moved_angle) noexcept
{
	if (this != &moved_angle) {
		angle_rad = moved_angle.angle_rad;
		moved_angle.angle_rad = 0;
	}
	return *this;
}

bool Angle::operator==(const Angle& angle) const
{
	return angle_rad == angle.angle_rad;
}

bool Angle::operator!=(const Angle& angle) const
{
	return angle_rad != angle.angle_rad;
}

Angle Angle::operator+(const Angle& angle) const
{
	Angle temp{angle_rad + angle.angle_rad};
	return temp;
}

Angle Angle::operator-(const Angle& angle) const
{
	Angle temp{angle_rad - angle.angle_rad};
	return temp;
}

Angle Angle::operator*(const Angle& angle) const
{
	Angle temp{angle_rad * angle.angle_rad};
	return temp;
}

Angle Angle::operator*(const double scalar) const
{
	Angle temp{angle_rad * scalar};
	return temp;
}


// Overloaded friend functions
Angle operator*(double scalar, const Angle& angle)
{
	Angle temp{scalar * angle.angle_rad};
	return temp;
}


// Member functions
double Angle::get_angle(const std::string format) const
{
	if (format == "r") {
		return angle_rad;

	} else if (format == "d") {
		return angle_rad * (45.0 / atan(1));

	} else {
		std::cout << "Error: format must be either \"r\" or \"d\" for radians or degrees respectively.\n";
		return std::nan("");
	}
}

void Angle::set_angle(const double angle, const std::string format)
{
	if (format == "r") {
		angle_rad = angle;

	} else if (format == "d") {
		angle_rad = angle * (atan(1) / 45);

	} else {
		std::cout << "Error: format must be either \"r\" or \"d\" for radians or degrees respectively.\n";
	}
}

void Angle::set_angle(std::vector<double> angle, const std::string format)
{
	size_t defined_entries(angle.size());

	if (defined_entries < 1 || defined_entries > 3) {
		std::cout << "Error: could not read angle. There must be between 1 and 3 entries.\n";
		angle_rad = std::nan("");

	} else {
		// Make the vector into size 3.
		for (size_t i{0}; i < 3 - defined_entries; i++) {
			angle.push_back(0);
		}
		if (format == "dms") {
			set_angle(angle[0] + angle[1] / 60 + angle[2] / 3600, "d");

		} else if (format == "hms") {
			set_angle(angle[0] * 15 + angle[1] / 4 + angle[2] / 240, "d");

		} else {
			std::cout << "Error: format must be either \"dms\" or \"hms\".\n";
		}
	}
}


// iostream virtual body functions
void Angle::iostream_output_body(std::ostream& os) const
{
	if (angle_rad != angle_rad) {
		os << "nan";

	} else {
		os << "r " << angle_rad;
	}
}

void Angle::iostream_input_body(std::istream& is)
	// Can insert with 4 different format specifiers ("r", "d", "dms", "hms") specifying radians, degrees, degrees minutes seconds, or hours minutes seconds.
	// Enter first the format specifier, then the angle entries in doubles separated by spaces. The maximum number of entries is given by 
	// the number of characters in the format specifier. 
	// Example: for 10.5 degrees input -> "d 10.5" or "r 0.1833" or "dms 10 30" or "hms 0 42 0".
{
	std::string format;
	is >> std::ws;
	is >> format;

	if (format == "r" || format == "d") {
		double angle;
		is >> angle;
		set_angle(angle, format);

	} else if (format == "dms" || format == "hms") {
		std::vector<double> angle_entries;
		double entry;

		int loop_count{0}; // Prevent never-ending loop in case the format is incorrect.
		while (is.peek() != '\n' && is.peek() != ',' && !is.eof()) {
			is >> entry;
			angle_entries.push_back(entry);
			is >> std::ws;

			loop_count++;
			if (loop_count > 3) {
				break;
			}
		}
		if (angle_entries.size() < 1 || angle_entries.size() > 3) {
			std::cout << "Error: could not read angle. Please enter angle in format \"dd mm ss\".\n";

		} else {
			set_angle(angle_entries, format);
		}
	} else {
		std::cout << "Error: angle not read correctly. Please make sure you have the correct format specifier.\n";
		angle_rad = std::nan("");
	}
}
