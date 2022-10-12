// Object-Oriented Programming in C++
// Assignment 2
// Timothe Rhein - 27/2/2022

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>

std::string ask_filename()
{
	std::string filename;
	std::cout << "Please enter the filename containing the course data: ";
	std::getline(std::cin, filename);

	return filename;
}

std::string trim_whitespace(std::string& input)
{
	size_t start_position{input.find_first_not_of(' ')};

	if (start_position == std::string::npos) {
		return input;
	}
	size_t end_position{input.find_last_not_of(' ')};

	return input.substr(start_position, end_position - start_position + 1);
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

void print_line(std::vector<double> grades, std::vector<std::string> titles, size_t index, int precision = 1) {
	std::cout.precision(precision);
	std::cout << std::fixed << grades[index] << "   " << titles[index] << std::endl;
}

double calculate_mean(std::vector<double> values)
{
	double sum_of_elements{0};
	for (auto iterator = values.begin(); iterator != values.end(); iterator++) {
		sum_of_elements += *iterator;
	}
	return sum_of_elements / values.size();
}

double calculate_standard_deviation(std::vector<double> values)
{
	double sum_of_differences_squared{0};
	double mean{calculate_mean(values)};
	for (auto iterator = values.begin(); iterator != values.end(); iterator++) {
		sum_of_differences_squared += std::pow((*iterator - mean), 2);
	}
	return std::sqrt(sum_of_differences_squared / (values.size() - 1));
}

double calculate_standard_error_of_mean(std::vector<double> values)
{
	return calculate_standard_deviation(values) / std::sqrt(values.size());
}

void print_statistics(std::vector<double> values) {
	std::cout << "\nThe mean grade is " << calculate_mean(values) << ".\n";
	std::cout << "The standard deviation is " << calculate_standard_deviation(values) << ".\n";
	std::cout << "The standard error in the mean is " << calculate_standard_error_of_mean(values) << ".\n";
}


int main()
{
	// Ask user for filename and test it.
	std::string filename{ask_filename()};
	std::fstream data_file{filename};
	
	while (!data_file.good()) {
		std::cerr << "Error: file could not be opened. Try entering the filename again, or 'exit' to exit.\n";
		
		data_file.close();
		data_file.clear();

		filename = ask_filename();
		if (filename == "exit") {
			return 0;
		}
		data_file.open(filename);
	}
	
	// Read file and store in vectors.
	std::string* temporary_segments{new std::string};
	std::vector<std::string>* line_segments{new std::vector<std::string>};

	std::vector<double> course_grades;
	std::vector<int> course_codes;
	std::vector<std::string> course_names;

	while (!data_file.eof()) {
		try {
			// Repeated for each line of the file. Defines 3 columns (grade, code, name) separated by the first 2 spaces.
			for (size_t i{0}; i < 2; i++) {
				std::getline(data_file, *temporary_segments, ' ');
				line_segments->push_back(*temporary_segments);
			}
			std::getline(data_file, *temporary_segments);
			line_segments->push_back(*temporary_segments);

			// Assign course grade, code and name to their respective vectors after type conversion if needed.
			course_grades.push_back(std::stod((*line_segments)[0]));
			course_codes.push_back(std::stoi((*line_segments)[1]));
			course_names.push_back(trim_whitespace((*line_segments)[2]));

			line_segments->clear();

		} catch (std::exception& ex) {
			line_segments->clear();
		} 
	}
	delete temporary_segments;
	delete line_segments;

	data_file.close();
	data_file.clear();

	if (course_grades.size() == 0) {
		std::cout << "No data was read from the file. Please ensure the format is \"grade code name\".\n Exiting...\n";
		return 0;
	}

	std::cout << "\nThere are " << course_grades.size() << " entries read from the file.\n";


	// Create course title vector
	std::vector<std::string> course_titles;
	std::stringstream title;

	for (size_t i{0}; i < course_grades.size(); i++) {
		title << "PHYS " << course_codes[i] << ' ' << course_names[i];
		course_titles.push_back(title.str());
		title.str("");
	}

	// Option menu
	int* option_selection{new int};

	while (true) {
		std::cout << "\nPlease enter the number from one of the following options:\n";
		std::cout << "1. Print all courses and the mean, standard deviation, and error in mean of their grades.\n";
		std::cout << "2. Choose courses from a specific year.\n";
		std::cout << "3. Sort courses by title or course code.\n";
		std::cout << "4. Exit.\n";

		std::cin >> *option_selection;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


		if (*option_selection == 1) {
			// Print all courses in file order and their statistics.
			std::cout << "\nGrade  " << "Course title\n";
			std::cout << "------------------------\n";
			for (size_t i{0}; i < course_grades.size(); i++) {
				print_line(course_grades, course_titles, i);
			}
			print_statistics(course_grades);

		} else if (*option_selection == 2) {
			// Print all courses for a specific year and their statistics.
			int* year(new int);
			std::cout << "\nChoose a year from 1 to 4: ";

			while (true) {
				std::cin >> *year;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				if (*year >= 1 && *year <= 4) {
					break;
				} else {
					std::cout << "Please enter an integer from 1 to 4: ";
				}
			}
			std::vector<double>* selected_course_grades{new std::vector<double>};

			std::cout << "\nGrade  " << "Course title\n";
			std::cout << "------------------------\n";
			for (size_t i{0}; i < course_grades.size(); i++) {
				if (std::to_string(course_codes[i])[0] == std::to_string(*year)[0]) {
					print_line(course_grades, course_titles, i);
					selected_course_grades->push_back(course_grades[i]);
				}
			}
			std::cout << "\nThere are " << (*selected_course_grades).size() << " entries in this selection.\n";
			print_statistics(*selected_course_grades);

			delete year;
			delete selected_course_grades;

		} else if (*option_selection == 3) {
			// Sort courses by name or course code.
			std::cout << "Would you like to sort by name or code? [n/c]: ";
			char user_input{check_answer('n', 'c')};

			std::cout << "\nGrade  " << "Course title\n";
			std::cout << "------------------------\n";

			// Create vector of indices for sorting the courses.
			std::vector<size_t>* indices{new std::vector<size_t>};
			indices->resize(course_grades.size());
			std::iota(indices->begin(), indices->end(), 0);

			if (user_input == 'n') {
				// Sort indices by name.
				std::sort(indices->begin(), indices->end(), [course_names](size_t a, size_t b) {return course_names[a] < course_names[b]; });

				for (size_t i{0}; i < indices->size(); i++) {
					print_line(course_grades, course_titles, (*indices)[i]);
				}
				print_statistics(course_grades);

			} else if (user_input == 'c') {
				// Sort indices by code.
				std::sort(indices->begin(), indices->end(), [course_codes](size_t a, size_t b) {return course_codes[a] < course_codes[b]; });

				for (size_t i{0}; i < indices->size(); i++) {
					print_line(course_grades, course_titles, (*indices)[i]);
				}
				print_statistics(course_grades);
			}

			delete indices;

		} else if (*option_selection == 4) {
			break;
		} 
	}

	delete option_selection;
	
	return 0;
}