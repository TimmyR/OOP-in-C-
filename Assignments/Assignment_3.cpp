// Object-Oriented Programming in C++
// Assignment 2 - a class for galaxies
// Timothe Rhein - 10/3/2022

#include <string>
#include <iostream>
#include <vector>

class Galaxy
{
public:
	// Constructors and destructor.
	Galaxy() = default;
	Galaxy(std::string galaxy_hubble_type, double galaxy_redshift, double galaxy_total_mass, double galaxy_stellar_mass_fraction) :
		hubble_type{galaxy_hubble_type}, redshift{galaxy_redshift}, total_mass{galaxy_total_mass}, stellar_mass_fraction{galaxy_stellar_mass_fraction}
	{}
	~Galaxy() {
		std::cout << "Destroying Galaxy of type " << hubble_type << ".\n";
	}

	// Member functions.
	double get_stellar_mass() { return stellar_mass_fraction * total_mass; }
	void print_data();
	void change_hubble_type(std::string);
	void add_satellite(Galaxy*);


private:
	std::string hubble_type{"E0"};
	double redshift{0};
	double total_mass{1e7}; // in units of solar mass
	double stellar_mass_fraction{0};
	std::vector<Galaxy*> satellites;
};

void Galaxy::print_data() {
	std::cout.precision(1);
	std::cout << "-Galaxy [Hubble type, redshift, total mass, stellar mass fraction, number of satellites] : " << "[" << hubble_type << ", " << redshift
		<< ", " << total_mass << " solar masses, " << stellar_mass_fraction << ", " << satellites.size() << "]\n";

	if (satellites.size() != 0) {
		std::cout << "  Satellites :\n";
		for (auto iterator = satellites.begin(); iterator != satellites.end(); iterator++) {
			std::cout << "   -";
			(*iterator)->print_data(); 
		}
	}
}

void Galaxy::change_hubble_type(std::string new_hubble_type) {
	hubble_type = new_hubble_type;
}

void Galaxy::add_satellite(Galaxy* satellite) {
	satellites.push_back(satellite);
}

void print_galaxies_data(std::vector<Galaxy>& galaxy_vector) {
	std::cout << "Print galaxies data: \n";

	for (auto iterator = galaxy_vector.begin(); iterator != galaxy_vector.end(); iterator++) {
		iterator->print_data();
	}
	std::cout << std::endl;
}

int main() 
{
	
	// Define a few galaxies.
	Galaxy galaxy_1{};
	Galaxy galaxy_2{"Sa", 4.3, 3.4e11, 0.035};
	Galaxy galaxy_3{"SBb", 4.3, 4.8e8, 0.031};
	Galaxy galaxy_4{"E6", 0.0013, 6.2e9, 0.04};
	Galaxy galaxy_5{"Irr", 0.001, 7e7, 0.026};
	Galaxy galaxy_6{"Sa", 0.0016, 5.2e7, 0.016};

	// Define satellite galaxies.
	galaxy_2.add_satellite(&galaxy_3);
	galaxy_4.add_satellite(&galaxy_5);
	galaxy_4.add_satellite(&galaxy_6);

	std::vector<Galaxy> galaxies;
	galaxies.reserve(3);		// set capacity to 3 to avoid destroying vectors when using push_back
	galaxies.push_back(galaxy_1);
	galaxies.push_back(galaxy_2);
	galaxies.push_back(galaxy_4);

	print_galaxies_data(galaxies);

	// Use member functions.
	std::cout << "The stellar mass of galaxy_3 is " << galaxy_3.get_stellar_mass() << " solar masses.\n";
	galaxy_5.change_hubble_type("SBc");
	std::cout << std::endl;

	// Show change in hubble_type.
	print_galaxies_data(galaxies);

	return 0;
}