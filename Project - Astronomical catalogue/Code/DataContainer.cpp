#include "DataContainer.h"
#include "ExtrasolarObject_derived.h"
#include "IntrasolarObject_derived.h"

#include <iostream>
#include <string>


std::ostream& operator<<(std::ostream& os, const DataContainer& object)
{
	for (auto& it : object.data) {
		os << *it;
	}
	return os;
}

std::istream& operator>>(std::istream& is, DataContainer& data_cont)
	// Inserts an object into the data container.
{
	std::string object_type;
	bool data_read{false};

	is >> std::ws;
	std::getline(is, object_type, ',');

	// Condition to not run this code if a new-line character is encountered.
	if (object_type.size() > 1) {
		// Will create an object only if the object_type matches with the class.
		data_cont.create_object<Star>(is, object_type, data_read);
		data_cont.create_object<Galaxy>(is, object_type, data_read);
		data_cont.create_object<Sun>(is, object_type, data_read);
		data_cont.create_object<Planet>(is, object_type, data_read);
		data_cont.create_object<Comet>(is, object_type, data_read);
		data_cont.create_object<Asteroid>(is, object_type, data_read);

		if (data_read == false) {
			std::cout << "Error: data not read properly. Please ensure the object type specifier is correct.\n";
		}
	}
	return is;
}

size_t DataContainer::size() const
{
	return data.size();
}

void DataContainer::clear()
{
	data.clear();
}

void DataContainer::output_results(std::ostream& os, const std::vector<size_t>& results_indices) const
{
	auto data_iterator = data.begin();
	for (auto it : results_indices) {
		std::advance(data_iterator, it);
		os << **data_iterator;
		data_iterator = data.begin();
	}
}

std::vector<size_t> DataContainer::search_by_name(std::string search_term) const
{
	std::vector<size_t> result_indices;
	size_t index{0};

	for (auto& it : data) {
		if (it->get_name() == search_term) {
			result_indices.push_back(index);
		}
		index++;
	}
	return result_indices;
}

std::vector<size_t> DataContainer::search_by_experiment(std::string search_term) const
{
	std::vector<size_t> result_indices;
	size_t index{0};

	for (auto& it : data) {
		if (it->get_experiment() == search_term) {
			result_indices.push_back(index);
		}
		index++;
	}
	return result_indices;
}

std::vector<size_t> DataContainer::search_by_type(std::string search_term) const
{
	std::vector<size_t> result_indices;
	size_t index{0};

	for (auto& it : data) {
		if (it->get_class_name() == search_term) {
			result_indices.push_back(index);
		}
		index++;
	}
	return result_indices;
}

void DataContainer::check_incorrect_read()
	// Deletes objects that haven't been read correctly.
{
	for (auto it = data.begin(); it != data.end();) {
		if ((*it)->invalid_state()) {
			it = data.erase(it);
		} else {
			it++;
		}
	}
}
