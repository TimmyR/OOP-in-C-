#include "Angle_derived.h"
#include "Date.h"
#include "ExtrasolarObject.h"

#include <cmath>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// Static variable definition
size_t ExtrasolarObject::use_count{0};

size_t ExtrasolarObject::get_use_count()
{
	return use_count;
}

void ExtrasolarObject::set_data(const std::string p_name, const std::string p_experiment, const std::string p_constellation, const std::string p_type, const double p_app_magnitude, const double p_mass, const double p_distance_pc, const Date p_observational_epoch, const RightAscension p_ra, const Angle p_ra_year_change, const Declination p_dec, const Angle p_dec_year_change)
{
	name = p_name;
	experiment = p_experiment;
	constellation = p_constellation;
	type = p_type;
	apparent_magnitude = p_app_magnitude;
	mass = p_mass;
	distance = p_distance_pc;
	observation_epoch = p_observational_epoch;
	ra_observed = p_ra;
	ra_yearly_change = p_ra_year_change;
	dec_observed = p_dec;
	dec_yearly_change = p_dec_year_change;
}

void ExtrasolarObject::iostream_input_body(std::istream& is)
	// Format is "name, experiment, constellation, [spectral or Hubble] type, apparent magnitude, mass, distance, observational epoch, ra, ra yearly change, dec, dec yearly change".
	// All fields are comma separated. For the angles ra, ra centurial change, dec, dec centurial change the format is specified by the Angle class, 
	// while for observational epoch the format is specified by the Date class.
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
		if (entries.size() != 12) {
			throw(entries[0]);

		} else {
			std::istringstream iss{entries[7]};	// entries[7] holds the observational_epoch field.
			Date obs_epoch;
			iss >> obs_epoch;
			iss.str("");
			iss.clear();


			std::vector<std::unique_ptr<Angle>> angles;
			angles.reserve(4);
			angles.push_back(std::make_unique<RightAscension>());
			angles.push_back(std::make_unique<Angle>());
			angles.push_back(std::make_unique<Declination>());
			angles.push_back(std::make_unique<Angle>());

			// entries[8] through entries[11] hold the angle fields:
			// (ra, ra yearly change, dec, dec yearly change)
			for (size_t i{0}; i < 4; i++) {
				iss.str(entries[i + 8]);
				iss >> *angles[i];
				iss.str("");
				iss.clear();
			}

			set_data(entries[0], entries[1], entries[2], entries[3], std::stod(entries[4]), std::stod(entries[5]), std::stod(entries[6]), obs_epoch, (*angles[0]), (*angles[1]), (*angles[2]), (*angles[3]));
		}
	} catch (std::string name) {
		if (name == entries[0]) {
			std::cout << "Error: " << get_class_name() << " " << name << " not read correctly. Please ensure there are 12 comma-separated fields after the object type.\n";
			incorrect_read = true;
		} 
	// Catch exceptions from invalid string to double conversion.
	} catch (const std::invalid_argument&) {
		std::cout << "Error: " << get_class_name() << " not read correctly. Please ensure to only enter numbers or \"nan\" in the numerical fields.\n";
		incorrect_read = true;
	}
}

void ExtrasolarObject::iostream_output_body(std::ostream& os) const
{
	if (incorrect_read == true) {
		std::cout << "Error: the object was not correctly initialised.\n";

	} else {
		os << get_class_name() << ", " << name << ", " << experiment << ", " << constellation << ", " << type << ", " << apparent_magnitude << ", " << mass << ", " << distance << ", " << observation_epoch << ", " << ra_observed << ", " << ra_yearly_change << ", " << dec_observed << ", " << dec_yearly_change << std::endl;
	}
}





