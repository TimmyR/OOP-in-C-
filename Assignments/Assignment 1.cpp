// Object-Oriented Programming in C++
// Assignment 1
// Calculates photon energies for transitions between atomic energy levels. The user chooses the atomic number 
// and the initial and final principal quantum number.
// Timothe Rhein - 18/2/2022

#include <iostream>
#include <cmath>

double calculate_photon_energy(int atomic_number, int initial_principle_quantum_number, int final_principle_quantum_number, char units)
{
	double photon_energy{ 13.6 * std::pow(atomic_number, 2) * (std::pow(final_principle_quantum_number, -2) - std::pow(initial_principle_quantum_number, -2)) };

	if (units == 'J') {
		return photon_energy * 1.6e-19;
	} else if (units == 'e') {
		return photon_energy;
	}
}

void check_input(int& user_input)
// Check that the input is a positive integer. Asks for input until it is.
{
	while (std::cin.fail() || user_input <= 0) {
		std::cerr << "Error: Please enter a positive integer: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> user_input;
	}
}

char check_answer(char input_1, char input_2) 
// Check the input is either input_1 or input_2. Asks for input until it is.
{
	char answer;
	std::cin >> answer;

	while (!(answer == input_1 || answer == input_2)) {
		std::cout << "Please enter either '" << input_1 << "' or '" << input_2 << "': ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> answer;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return answer;
}


int main()
{
	int atomic_number, initial_principle_quantum_number, final_principle_quantum_number;
	double photon_energy;
	char user_input;

	while (true) {
		std::cout << "Enter the atomic number: ";
		std::cin >> atomic_number;
		check_input(atomic_number);

		std::cout << "Enter the initial principle quantum number: ";
		std::cin >> initial_principle_quantum_number;
		check_input(initial_principle_quantum_number);

		std::cout << "Enter the final principle quantum number: ";
		std::cin >> final_principle_quantum_number;
		check_input(final_principle_quantum_number);

		if (initial_principle_quantum_number > final_principle_quantum_number) {
			std::cout << "Would you like the photon energy in Joules or eV? [J/e]: ";

			user_input = check_answer('J', 'e');
			photon_energy = calculate_photon_energy(atomic_number, initial_principle_quantum_number, final_principle_quantum_number, user_input);
			
			std::cout.precision(3);
			if (user_input == 'J') {
				std::cout << "The photon energy is " << photon_energy << " J.\n";
			} else if (user_input == 'e') {
				std::cout << "The photon energy is " << photon_energy << " eV.\n";
			}
		} else {
			std::cerr << "Error: Initial principle quantum number must be greater than the final principle quantum number.\n";
		}
		std::cout << "Would you like to repeat the calculation? [y/n]: ";

		user_input = check_answer('y', 'n');
		if (user_input == 'y') {}
		else if (user_input == 'n') { break; }
		std::cout << "\n";
	}
	return 0;
}