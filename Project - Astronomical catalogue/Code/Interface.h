#ifndef INTERFACE_H
#define INTERFACE_H

#include "DataContainer.h"


#include <string>
#include <vector>

class Interface
	// Command line interface.
{
public:
	Interface();
	~Interface() {};

private:
	bool exit{false};
	std::vector<int> input_commands;
	DataContainer data_container;

	// Menu interface functions
	void menu();
	int numerical_input(const int max_entry) const;
	void user_input(const int max_entry);

	// Menu text outputs.
	void welcome_text() const;
	void about_text() const;
	void section_break(const bool double_lines=false) const;
	void text_main() const;
	void text_1() const;
	void text_11() const;
	void text_12() const;
	void text_2() const;
	void text_3() const;
	void text_5() const;

	// Functional member functions
	void save_data_to_file(const std::string filename, const bool append = false) const;
	void save_data_to_file(const std::string filename, const std::vector<size_t>& result_indices, const bool append = false) const;
	void read_data_from_file(const std::string filename);
	void enter_data_from_terminal();
	std::string get_string() const;
	bool ask_append() const;
	void confirm_delete();

	void output_search_results(const std::vector<size_t>& result_indices) const;
	void search_by_name() const;
	void search_by_experiment() const;
	void search_by_type() const;
};

#endif