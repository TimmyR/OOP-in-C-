#ifndef DATE_H
#define DATE_H

#include "Angle.h"

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

class Date
	// Store a date as a Julian Date: number of days since 12:00:00 on Monday 24 Nov 4714 BC (proleptic Gregorian calendar).
	// The proleptic Gregorian calendar is used for input and output, so be careful for dates before 15 Oct 1582. 
	// Time scale is terrestrial time (TT) unless specified.
{
public:
	Date() = default;
	Date(const double julian_date);
	Date(const int year, const int month, const int day, const int hour = 0 , const int minute = 0, const int second = 0);
	Date(const std::vector<int> calendar_date);
	Date(const Date& copied_date);
	Date(Date&& moved_date) noexcept;
	~Date() {};

	Date& operator=(const Date& copied_date);
	Date& operator=(Date&& moved_date) noexcept;
	bool operator==(const Date& date) const;
	bool operator!=(const Date& date) const;
	bool operator<(const Date& date) const;
	bool operator>(const Date& date) const;

	friend std::ostream& operator<<(std::ostream& os, const Date& date);
	friend std::istream& operator>>(std::istream& is, Date& date);

	double get_julian_date() const;
	double get_julian_date_ut1() const;
	std::vector<int> get_calendar_date() const;
	void set_date(const int year, const int month, const int day, const int hour = 0, const int minute = 0, const int second = 0);

	double get_delta_t(const std::string coefficient_file = "dt_fitting_coefficients.txt") const;
	double get_obliquity_ecliptic() const;

private:
	double julian_date{std::nan("")};
};

#endif