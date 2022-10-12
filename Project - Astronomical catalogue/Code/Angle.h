#ifndef ANGLE_H
#define ANGLE_H

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

class Angle
	// Base class to store and manipulate angles.
{
public:
	Angle() = default;
	Angle(const double angle, const std::string format="r");
	Angle(std::vector<double> angle, const std::string format = "dms");
	Angle(const Angle& copied_angle);
	Angle(Angle&& moved_angle) noexcept;
	virtual ~Angle() {};

	Angle& operator=(const Angle& copied_angle);
	Angle& operator=(Angle&& moved_angle) noexcept;
	bool operator==(const Angle& angle) const;
	bool operator!=(const Angle& angle) const;
	Angle operator+(const Angle& angle) const;
	Angle operator-(const Angle& angle) const;
	Angle operator*(const Angle& angle) const;
	Angle operator*(const double scalar) const;

	friend Angle operator*(double scalar, const Angle& angle);
	friend std::ostream& operator<<(std::ostream& os, const Angle& date);
	friend std::istream& operator>>(std::istream& is, Angle& date);

	double get_angle(const std::string format = "r") const;
	void set_angle(const double angle, const std::string format = "r");
	void set_angle(std::vector<double> angle, const std::string format = "dms");
	
protected:
	double angle_rad{std::nan("")};

	virtual void check_limits() {}; // no limits are specified for this class.

	// iostream virtual body functions
	virtual void iostream_output_body(std::ostream& os) const;
	void iostream_input_body(std::istream& is);
};


// Virtual friend functions implementation.
inline std::ostream& operator<<(std::ostream& os, const Angle& date)
{
	date.iostream_output_body(os);
	return os;
}

inline std::istream& operator>>(std::istream& is, Angle& date)
{
	date.iostream_input_body(is);
	date.check_limits();
	return is;
}

#endif