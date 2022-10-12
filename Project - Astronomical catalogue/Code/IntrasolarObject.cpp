#include "Angle_derived.h"
#include "Date.h"
#include "IntrasolarObject.h"

#include <cmath>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// Static variable definition
size_t IntrasolarObject::use_count{0};

size_t IntrasolarObject::get_use_count()
{
	return use_count;
}

void IntrasolarObject::set_data(const std::string p_name, const std::string p_experiment, const double p_app_magnitude, const double p_mass, const double p_distance_pc, const Date p_observational_epoch, const RightAscension p_ra, const Declination p_dec)
{
	name = p_name;
	experiment = p_experiment;
	apparent_magnitude = p_app_magnitude;
	mass = p_mass;
	distance = p_distance_pc;
	observation_epoch = p_observational_epoch;
	ra_observed = p_ra;
	dec_observed = p_dec;
}

void IntrasolarObject::iostream_input_body(std::istream& is)
	// Format is "name, experiment, apparent magnitude, mass, distance, observational epoch, ra, dec".
	// All fields are comma separated. For the angles ra, ra centurial change, dec, dec centurial change the format is specified by the Angle class. 
	// 
{
	std::string input_line;
	std::string input_entry;
	std::vector<std::string> entries;

	is >> std::ws;
	std::getline(is, input_line);
	std::stringstream ss{input_line};

	try {
		while (ss.peek() != '\n' && !ss.eof()) {
			ss >> std::ws;
			std::getline(ss, input_entry, ',');
			entries.push_back(input_entry);
		}
		if (entries.size() != 8) {
			throw(entries[0]);

		} else {
			std::istringstream iss{entries[5]};
			Date obs_epoch;
			iss >> obs_epoch;
			iss.str("");
			iss.clear();

			std::vector<std::unique_ptr<Angle>> angles;
			angles.reserve(2);
			angles.push_back(std::make_unique<RightAscension>());
			angles.push_back(std::make_unique<Declination>());

			for (size_t i{0}; i < 2; i++) {
				iss.str(entries[i + 6]);
				iss >> *angles[i];
				iss.str("");
				iss.clear();
			}

			set_data(entries[0], entries[1], std::stod(entries[2]), std::stod(entries[3]), std::stod(entries[4]), obs_epoch, (*angles[0]), (*angles[1]));
		}
	// Catch exception from incorrect number of entries being read in.
	} catch (std::string name_entry) {
		if (name_entry == entries[0]) {
			std::cout << "Error: " << get_class_name() << " " << name_entry << " not read correctly. Please ensure there are 8 comma-separated fields after the object type.\n";
			incorrect_read = true;
		} 
	// Catch exceptions from invalid string to double conversion.
	} catch (const std::invalid_argument&) {
		std::cout << "Error: " << get_class_name() << " not read correctly.Please ensure to only enter numbers or \"nan\" in the numerical fields.\n";
		incorrect_read = true;
	}
}

void IntrasolarObject::iostream_output_body(std::ostream& os) const
{
	if (incorrect_read == true) {
		std::cout << "Error: the object was not correctly initialised.\n";

	} else {
		os << get_class_name() << ", " << name << ", " << experiment << ", " << apparent_magnitude << ", " << mass << ", " << distance << ", " << observation_epoch << ", " << ra_observed << ", " << dec_observed << std::endl;
	}
}
