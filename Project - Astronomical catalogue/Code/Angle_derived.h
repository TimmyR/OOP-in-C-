#ifndef ANGLE_DERIVED_H
#define ANGLE_DERIVED_H

#include "Angle.h"

#include <iostream>

class RightAscension : public Angle
{
public:
	RightAscension() = default;
	RightAscension(const double angle, const std::string format = "r");
	RightAscension(std::vector<double> angle, const std::string format = "dms");
	RightAscension(const Angle& copied_angle);
	RightAscension(Angle&& moved_angle) noexcept;
	~RightAscension() {};
	
private:
	void check_limits() override;
	void iostream_output_body(std::ostream& os) const override;
};


class Declination : public Angle
{
public:
	Declination() = default;
	Declination(const double angle, const std::string format = "r");
	Declination(std::vector<double> angle, const std::string format = "dms");
	Declination(const Angle& copied_angle);
	Declination(Angle&& moved_angle) noexcept;
	~Declination() {};

private:
	void check_limits() override;
	void iostream_output_body(std::ostream& os) const override;
};

#endif