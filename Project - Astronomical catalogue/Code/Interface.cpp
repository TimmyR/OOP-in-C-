#include "CelestialObject.h"
#include "ExtrasolarObject.h"
#include "ExtrasolarObject_derived.h"
#include "Interface.h"
#include "IntrasolarObject.h"
#include "IntrasolarObject_derived.h"

#include <fstream>
#include <iostream>
#include <limits>

Interface::Interface()
{
	read_data_from_file("exit_save.txt");
	welcome_text();
	while (!exit) {
		data_container.check_incorrect_read();
		menu();
	}
	save_data_to_file("exit_save.txt");
}

// Menu interface functions
void Interface::menu()
	// Defines the menu hierarchy. The state of the menu is defined by the variable input_commands.
{
	if (input_commands.size() == 0) {
		text_main();
		user_input(6);
	}

	switch (input_commands[0]) {
	// Enter data
	case 1:
		if (input_commands.size() == 1) {
			text_1();
			user_input(2);
		}
		switch (input_commands[1]) {
		case 1:
			if (input_commands.size() == 2) {
				text_11();
				
				enter_data_from_terminal();
			}
			input_commands.pop_back();
			break;
		case 2:
			if (input_commands.size() == 2) {
				text_12();
				
				read_data_from_file(get_string());
			}
			input_commands.pop_back();
			break;
		case 0:
			input_commands.pop_back();
			input_commands.pop_back();
			break;
		}
		break;
	// Search data.
	case 2:
		if (input_commands.size() == 1) {
			text_2();
			user_input(3);
		}
		switch (input_commands[1]) {
		case 1:
			if (input_commands.size() == 2) {
				search_by_name();
			}
			input_commands.pop_back();
			break;
		case 2:
			if (input_commands.size() == 2) {
				search_by_experiment();
			}
			input_commands.pop_back();
			break;
		case 3:
			if (input_commands.size() == 2) {
				search_by_type();
			}
			input_commands.pop_back();
			break;
		case 0:
			input_commands.pop_back();
			input_commands.pop_back();
			break;
		}
		break;
	// Save data.
	case 3:
		if (input_commands.size() == 1) {
			text_3();

			std::string filename{get_string()};
			bool append{ask_append()};
			save_data_to_file(filename, append);
		}
		input_commands.pop_back();
		break;
	// Delete data.
	case 4:
		confirm_delete();
		input_commands.pop_back();
		break;
	// Object type numbers.
	case 5:
		if (input_commands.size() == 1) {
			text_5();
		}
		input_commands.pop_back();
		break;
	// About.
	case 6:
		if (input_commands.size() == 1) {
			section_break();
			about_text();
		}
		input_commands.pop_back();
		break;
	case 0:
		exit = true;
		break;
	}
}

int Interface::numerical_input(const int max_entry) const
{
	int input{-1};

	while (input < 0 || input > max_entry) {
		std::cin >> input;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (input < 0 || input > max_entry) {
			std::cout << "Error: please enter an integer between 0 and " << max_entry << ": ";
		}
	}
	return input;
}

void Interface::user_input(const int max_entry)
{
	int input{numerical_input(max_entry)};
	input_commands.push_back(input);
}


// Menu text outputs
void Interface::welcome_text() const
{
	std::cout << "Welcome to this star catalogue! Created by Timothe Rhein for the Object-Oriented Programming in C++ Project.\n\n";
	about_text();
}

void Interface::about_text() const
{
	std::cout << "This program stores data for observations of several types of celestial objects. What data is stored depends on the type of celestial object.\n";
	std::cout << "For extrasolar objects (\"star\", \"galaxy\") there are 13 fields required for data entry:\n";
	std::cout << "  -> object type, name, experiment, constellation, [spectral or Hubble] type, apparent magnitude, mass, distance, observational epoch, right ascension (ra), ra yearly change, declination (dec) , dec yearly change\n\n";
	std::cout << "For intrasolar objects (\"Sun\", \"planet\", \"comet\", \"asteroid\") there are 9 fields required for data entry:\n";
	std::cout << "  -> object type, name, experiment, apparent magnitude, mass, distance, observational epoch, ra, dec\n\n";
	std::cout << "Some notes on formatting:\n";
	std::cout << "- object type must match one of the strings mentioned above (eg. \"star\" or \"planet\").\n";
	std::cout << "- name, experiment, constellation and [spectral or Hubble] type can be any string.\n";
	std::cout << "- apparent magnitude, mass and distance are doubles. Mass is measured in solar masses and distance in parsecs.\n";
	std::cout << "- observational epoch is the date and time of observation. This can be entered in the following formats:\n";
	std::cout << "  - \"J [number]\" to input a julian date.\n";
	std::cout << "  - \"j2000\" for the J2000 epoch (1 January 2000 12:00:00).\n";
	std::cout << "  - \"yyyy MM dd hh mm ss\" to input a proleptic Gregorian calendar date.\n";
	std::cout << "- ra, ra yearly change, dec, dec yearly change are all angles. These can be entered in the following formats:\n";
	std::cout << "  - \"r [number]\" for an angle in radians.\n";
	std::cout << "  - \"d [number]\" for an angle in degrees.\n";
	std::cout << "  - \"dms [deg] [min] [sec] \" for an angle in degrees, minutes, and seconds.\n";
	std::cout << "  - \"hms [hrs] [min] [sec] \" for an angle in hours, minutes, and seconds.\n";
	std::cout << "- ra must be between 0 and 360 degrees, while dec must be between -90 and 90 degrees.\n";
	std::cout << "For any data that is not measured in a particular experiment, please enter \"nan\" instead.\n\n";
	std::cout << "When exiting, all data present in database will be saved in \"exit_save.txt\". Data from this file is automatically loaded on launch.\n";
}

void Interface::section_break(const bool double_lines) const
{
	if (double_lines) {
		std::cout << "\n----------------------------------------------------------------------------------------";
	}
	std::cout << "\n----------------------------------------------------------------------------------------\n\n";
}

void Interface::text_main() const
{
	section_break(true);
	std::cout << "There are " << CelestialObject::get_use_count() << " objects in the database.\n\n";
	std::cout << " --- Main menu --- \n";
	std::cout << "1. Enter observational data.\n";
	std::cout << "2. Search data.\n";
	std::cout << "3. Save all data to file.\n";
	std::cout << "4. Delete all data.\n";
	std::cout << "5. Number of objects by type.\n";
	std::cout << "6. About.\n";
	std::cout << "0. Exit.\n\n";
	std::cout << "Please choose an option: ";
}

void Interface::text_1() const
{
	section_break();
	std::cout << "1. Enter into terminal\n";
	std::cout << "2. Enter from file.\n";
	std::cout << "0. Back.\n\n";
	std::cout << "Please choose an option: ";
}

void Interface::text_11() const
{
	std::cout << "Please follow the format specified in the About section.\n";
	std::cout << "Enter the observational data: ";
}

void Interface::text_12() const
{
	std::cout << "Enter the filename containing the data: ";
}

void Interface::text_2() const
{
	section_break();
	std::cout << "Choose a field to search by:\n";
	std::cout << "1. Name.\n";
	std::cout << "2. Experiment.\n";
	std::cout << "3. Object type.\n";
	std::cout << "0. Back.\n\n";
	std::cout << "Please choose an option: ";
}

void Interface::text_3() const
{
	section_break();
	std::cout << "Enter the filename you would like to save to: ";
}

void Interface::text_5() const
{
	section_break();
	std::cout << "Here are the number of observations for each available object type.\n\n";
	std::cout << "Celestial Objects: " << CelestialObject::get_use_count() << std::endl;
	std::cout << "	Intersolar Objects: " << IntrasolarObject::get_use_count() << std::endl;
	std::cout << "		Sun: " << Sun::get_use_count() << std::endl;
	std::cout << "		Planet: " << Planet::get_use_count() << std::endl;
	std::cout << "		Comet: " << Comet::get_use_count() << std::endl;
	std::cout << "		Asteroid: " << Asteroid::get_use_count() << std::endl;
	std::cout << "	Extrasolar Objects: " << ExtrasolarObject::get_use_count() << std::endl;
	std::cout << "		Star: " << Star::get_use_count() << std::endl;
	std::cout << "		Galaxy: " << Galaxy::get_use_count() << std::endl;
}



// Functional member functions
void Interface::save_data_to_file(const std::string filename, const bool append) const
	// Saves all data to the file.
	// If append is false, file will be overwritten. Otherwise appends at the end of the file.
{
	std::ofstream save_file;
	if (append) {
		save_file.open(filename, std::ios::app);

	} else {
		save_file.open(filename, std::ios::trunc);
	}

	if (!save_file.good()) {
		std::cout << "Error: file not opened correctly." << std::endl;

	} else {
		save_file << data_container;
		std::cout << "Saved to file " << filename << " !\n";
	}
	save_file.close();
	save_file.clear();
}



void Interface::save_data_to_file(const std::string filename, const std::vector<size_t>& result_indices, const bool append) const
	// Saves data defined by the result_indices to file.
	// If append is false, file will be overwritten. Otherwise appends at the end of the file.

{
	std::ofstream save_file;
	if (append) {
		save_file.open(filename, std::ios::app);
		
	} else {
		save_file.open(filename, std::ios::trunc);
	}

	if (!save_file.good()) {
		std::cout << "Error: file not opened correctly." << std::endl;

	} else {
		data_container.output_results(save_file, result_indices);
		std::cout << "Saved to file " << filename << " !\n";
	}
	save_file.close();
	save_file.clear();
}

void Interface::read_data_from_file(const std::string filename)
{
	std::ifstream file_to_read{filename};

	if (!file_to_read.good()) {
		std::cout << "Error: file not read correctly." << std::endl;

	} else {
		while (!file_to_read.eof()) {
			file_to_read >> data_container;
		}
	}
	file_to_read.close();
	file_to_read.clear();
}

void Interface::enter_data_from_terminal()
{
	std::cin >> data_container;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string Interface::get_string() const
{
	std::string str;
	std::cin >> std::ws;
	std::getline(std::cin, str, '\n');
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return str;
}

bool Interface::ask_append() const
{
	std::cout << "Appending to the file will keep previous data, otherwise it will be overwritten.\n";
	std::cout << "Would you like to append? [y/n]: ";
	
	char input{'a'};
	while (input != 'y' && input != 'n') {
		std::cin >> input;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (input == 'y') {
			return true;

		} else if (input == 'n') {
			return false;

		} else {
			std::cout << "Please enter either 'y' or 'n': ";
		}
	}
	return false;
}

void Interface::confirm_delete()
{
	std::cout << "Are you sure you would like to delete all data? [y/n]: ";
	
	char input{'a'};
	while (input != 'y' && input != 'n') {
		std::cin >> input;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (input == 'y') {
			data_container.clear();

		} else if (input == 'n') {
			break;

		} else {
			std::cout << "Please enter either 'y' or 'n': ";
		}
	}
}


void Interface::output_search_results(const std::vector<size_t>& results_indices) const
{
	std::cout << "\nNumber of results: " << results_indices.size() << "\n\n";
	std::cout << "1. Print details in terminal.\n";
	std::cout << "2. Output results to file.\n";
	std::cout << "0. Back.\n";
	std::cout << "Please choose an option: ";

	int input{numerical_input(2)};
	std::cout << std::endl;
	std::cout << std::endl;

	if (input == 1) {
		data_container.output_results(std::cout, results_indices);

	} else if (input == 2) {
		std::cout << "Enter the filename you would like to save to: ";
		std::string filename{get_string()};
		bool append{ask_append()};
		save_data_to_file(filename, results_indices, append);

	} 
}

void Interface::search_by_name() const
{
	std::cout << "Please enter the name of the object you want to find: ";

	std::string search_term{get_string()};
	std::vector<size_t> result_indices;

	result_indices = data_container.search_by_name(search_term);

	if (result_indices.size() == 0) {
		std::cout << "No results found for \"" << search_term << "\".\n";

	} else {
		output_search_results(result_indices);
	}
}

void Interface::search_by_experiment() const
{
	std::cout << "Please enter the experiment you would like to search for: ";

	std::string search_term{get_string()};
	std::vector<size_t> result_indices;

	result_indices = data_container.search_by_experiment(search_term);

	if (result_indices.size() == 0) {
		std::cout << "No results found for \"" << search_term << "\".\n";

	} else {
		output_search_results(result_indices);
	}
}

void Interface::search_by_type() const
{
	std::cout << "Please enter the object type: ";

	std::string search_term{get_string()};
	std::vector<size_t> result_indices;

	result_indices = data_container.search_by_type(search_term);

	if (result_indices.size() == 0) {
		std::cout << "No results found for \"" << search_term << "\".\n";

	} else {
		output_search_results(result_indices);
	}
}