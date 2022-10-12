#include "Date.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


// Constructors
Date::Date(const double julian_date) : julian_date{julian_date} {}

Date::Date(const int year, const int month, const int day, const int hour, const int minute, const int second)
{
	set_date(year, month, day, hour, minute, second);
}

Date::Date(std::vector<int> calendar_date)
{
	size_t defined_entries(calendar_date.size());
	if (defined_entries < 3 || defined_entries > 6) {
		std::cout << "Error: could not read date. There must be between 3 and 6 entries.\n";
		julian_date = std::nan("");

	} else {
		for (size_t i{0}; i < 6 - defined_entries; i++) {
			calendar_date.push_back(0);
		}
		set_date(calendar_date[0], calendar_date[1], calendar_date[2], calendar_date[3], calendar_date[4], calendar_date[5]);
	}
}

Date::Date(const Date& copied_date)
{
	julian_date = copied_date.julian_date;
}

Date::Date(Date&& moved_date) noexcept
{
	julian_date = moved_date.julian_date;
	moved_date.julian_date = 0;
}


// Overloaded operators
Date& Date::operator=(const Date& copied_date)
{
	if (this != &copied_date) {
		julian_date = copied_date.julian_date;
	}
	return *this;
}

Date& Date::operator=(Date&& moved_date) noexcept
{
	if (this != &moved_date) {
		julian_date = moved_date.julian_date;
		moved_date.julian_date = 0;
	}
	return *this;
}

bool Date::operator==(const Date& date) const
{
	return julian_date == date.julian_date;
}

bool Date::operator!=(const Date& date) const
{
	return julian_date != date.julian_date;
}

bool Date::operator<(const Date& date) const
{
	return julian_date < date.julian_date;
}

bool Date::operator>(const Date& date) const
{
	return julian_date > date.julian_date;
}


// Overloaded friend functions
std::ostream& operator<<(std::ostream& os, const Date& date)
{
	if (date.julian_date != date.julian_date) {
		os << "nan";
		return os;
	}
	std::vector<int> calendar_date{date.get_calendar_date()};
	os << calendar_date[0] << "-" << calendar_date[1] << "-" << calendar_date[2] << " " << calendar_date[3] << ":" << calendar_date[4] << ":" << calendar_date[5];
	return os;
}

std::istream& operator>>(std::istream& is, Date& date)
// Can insert as either Julian date or calendar date (proleptic Gregorian), or the standard J2000 epoch for 12 Jan 2000 12:00:00 (TT).
// Julian date format: "J ####"
// Calendar date format: "yyyy MM dd hh mm ss". ("hh mm ss") fields are optional. Delimiters can be ' ', '-' or ':'. 
// J2000 epoch: "j2000".
// Entering "nan" sets the julian_date to std::nan("").
{
	is >> std::ws;

	if (is.peek() == 'J') {
		is.ignore();
		double input_julian_date;
		is >> input_julian_date;

		Date temp{input_julian_date};
		date = temp;

	} else if (is.peek() == 'j') {
		std::string epoch;
		is >> epoch;

		if (epoch == "j2000") {
			// Set date to J2000 epoch - 12 Jan 2000 at 12:00:00 (TT).
			date.set_date(2000, 1, 1, 12);

		} else {
			std::cout << "Error: could not read date. Enter \"j2000\" for the J2000 epoch, otherwise enter \"J [julian date #]\".";
			date.julian_date = std::nan("");
		}

	} else if (is.peek() == 'n' || is.peek() == 'N') {
		std::string epoch;
		is >> epoch;

		if (epoch == "nan" || epoch == "NaN") {
			// No error message in this case.
			date.julian_date = std::nan(""); 

		} else {
			std::cout << "Error: could not read date. Enter \"j2000\" for the J2000 epoch, otherwise enter \"J [julian_date_#]\".";
			date.julian_date = std::nan("");
		}

	} else {
		std::vector<int> date_entries;
		int entry;

		int loop_count{0}; // Prevent never-ending loop in case the format is incorrect.
		while (is.peek() != '\n' && is.peek() != ',' && !is.eof()) {
			is >> entry;
			date_entries.push_back(entry);

			if (is.peek() == '-' || is.peek() == ':') {
				is.ignore();
			}
			
			loop_count++;
			if (loop_count > 6) {
				break;
			}
			
		}
		if (date_entries.size() < 3 || date_entries.size() > 6) {
			std::cout << "Error: could not read date. Please enter integers in the format \"yyyy MM dd hh mm ss\".\n";
			date.julian_date = std::nan("");

		} else {
			Date temp{date_entries};
			date = temp;
		}
	}
	return is;
}




// Public member functions
double Date::get_julian_date() const
{
	return julian_date;
}

double Date::get_julian_date_ut1() const
	// Convert the time scale from terrestrial time (TT) to universal time (UT1) using UT1 = TT - delta_t.
{
	return julian_date - this->get_delta_t() / 86400;	// convert delta_t from seconds to days.
}

std::vector<int> Date::get_calendar_date() const
	// Algorithm adapted from https://en.wikipedia.org/wiki/Julian_day#Julian_or_Gregorian_calendar_from_Julian_day_number . 
	// Returns the proleptic Gregorian calendar date in format (yyyy, MM, dd, hh, mm, ss). 
	// Need to be carefull for dates before 15 Oct 1582 (5 Oct 1582 in Julian calendar).
{
	int julian_day_number = int(julian_date);
	int year, month, day, hour, minute, second;
	int e, g, h, f;

	// Algorithm parameters.
	const int y{4716}, v{3}, j{1401}, u{5}, m{2}, s{153}, n{12}, w{2}, r{4}, b{274277}, p{1461}, c{-38};
	
	f = julian_day_number + j + int((int((4 * julian_day_number + b) / 146097) * 3) / 4) + c;
	e = r * f + v;
	g = int((e % p) / r);
	h = u * g + w;

	day = int((h % s) / u) + 1;
	month = ((int(h / s) + m) % n) + 1;
	year = int(e / p) - y + int((n + m - month) / n);

	// Calculate time of day.
	// Corrects for the fact that Julian days start at 12:00 (noon).
	double day_fraction{julian_date - julian_day_number - 0.5};
	if (day_fraction <= 0) {
		day_fraction++;
	} else {
		day++;
	}

	hour = int(day_fraction * 24);
	minute = int((day_fraction * 24 - hour) * 60);
	second = int(((day_fraction * 24 - hour) * 60 - minute) * 60 + 0.5); // add 0.5 to round to nearest second.

	if (second >= 60) {
		second -= 60;
		minute++;
	}
	if (minute >= 60) {
		minute -= 60;
		hour++;
	}
	if (hour >= 24) {
		hour -= 24;
		day++;
	}
	if (day > 31) {
		day -= 31;
		month++;
	}
	if (month > 12) {
		month -= 12;
		year++;
	}

	return std::vector<int>({year, month, day, hour, minute, second});
}

void Date::set_date(const int year, const int month, const int day, const int hour, const int minute, const int second)
// Set the julian_date from a Gregorian calendar date and time. Since there is no year 0 BC, the year 1 BC = 0; 2 BC = -1; y BC = -y+1.
// Algorithm adapted from https://en.wikipedia.org/wiki/Julian_day#Converting_Gregorian_calendar_date_to_Julian_Day_Number .
{
	double julian_day_number;
	julian_day_number = (1461 * (year + 4800 + (month - 14) / 12)) / 4 + (367 * (month - 2 - 12 * ((month - 14) / 12))) / 12 - (3 * ((year + 4900 + (month - 14) / 12) / 100)) / 4 + day - 32075;

	julian_date = julian_day_number + float(hour - 12) / 24 + float(minute) / 1440 + float(second) / 86400;
}

double Date::get_delta_t(const std::string coefficient_file) const
	// Get the value of delta_t = TT - UT1 in seconds. 
	// Default coefficient_file is https://astro.ukho.gov.uk/nao/lvm/Table-S15.2020.txt which are the coefficients found in 
	// the studies https://royalsocietypublishing.org/doi/10.1098/rspa.2016.0404 and https://royalsocietypublishing.org/doi/10.1098/rspa.2020.0776 .
	// Please ensure any other file has the same format.
{
	// year_decimal calculation from julian_date from https://ytliu0.github.io/starCharts/docs/star_charts.pdf .
	double year_decimal;
	if (julian_date >= 2299160.5) {
		year_decimal = (julian_date - 2451544.5) / 365.2425 + 2000;
	} else {
		year_decimal = (julian_date + 0.5) / 365.25 - 4712;
	}
	
	// Extrapolation formula if date is before -720 or after 2019. 
	auto extrapolation_function = [&](double year) {
		const double t_1825{(year - 1825.0) / 100};	// centuries since 1825
		return 31.4115 * t_1825 * t_1825 + 284.8435805251424 * std::cos(0.4487989505128276 * (t_1825 + 0.75));
	};

	if (year_decimal < -720) {
		return extrapolation_function(year_decimal) + 1.007739546148514;

	} else if (year_decimal >= 2019) {
		return extrapolation_function(year_decimal) - 150.3150351029286;

	}
		
	// Read file and choose coefficients based on year.
	std::fstream data_file{coefficient_file};

	if (!data_file.good()) {
		std::cout << "Error: the delta_t coefficient file \"" << coefficient_file << "\" was not read correctly. Please ensure it is in the correct format.\n";
		data_file.close();
		data_file.clear();
		return std::nan("");
	}

	// Skip first 6 lines.
	std::string file_line;
	for (size_t i{0}; i < 6; i++) {
		std::getline(data_file, file_line);
	}
	int row;
	double year_lower, year_upper, a_0, a_1, a_2, a_3;

	data_file >> std::ws;

	while (data_file.peek() != '-') {
		data_file >> row >> year_lower >> year_upper;

		if (year_decimal >= year_lower && year_decimal < year_upper) {
			data_file >> a_0 >> a_1 >> a_2 >> a_3;
			data_file.close();
			data_file.clear();

			const double t{(year_decimal - year_lower) / (year_upper - year_lower)};
			return a_0 + t * (a_1 + t * (a_2 + t * a_3));
		}
		std::getline(data_file, file_line);
		data_file >> std::ws;
	}
	data_file.close();
	data_file.clear();

	std::cout << "Error: delta_t was not found.\n";
	return std::nan("");	
}

double Date::get_obliquity_ecliptic() const
{
	double t{(julian_date - 2451545) / 36525};	// Julian centuries since J2000.
	double obliquity {0.40909260060058283 - 0.00022707106390167 * t - 8.876938501115605e-10 *t*t + 9.712757287348442e-09 *t*t*t - 2.792e-12 *t*t*t*t - 2.10e-13 *t*t*t*t*t};
	
	return obliquity;
}
