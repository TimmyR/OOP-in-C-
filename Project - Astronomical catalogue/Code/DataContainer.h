#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include "CelestialObject.h"

#include <functional>
#include <iterator>
#include <memory>
#include <set>
#include <string>
#include <vector>

class DataContainer
	// Class to store data of CelestialObject derived objects.
{
public:
	DataContainer() = default;
	~DataContainer() {};

	friend std::ostream& operator<<(std::ostream& os, const DataContainer& object);
	friend std::istream& operator>>(std::istream& is, DataContainer& object);

	size_t size() const;
	void clear();

	void output_results(std::ostream& os, const std::vector<size_t>& results_indices) const;
	std::vector<size_t> search_by_name(std::string search_term) const;
	std::vector<size_t> search_by_experiment(std::string search_term) const;
	std::vector<size_t> search_by_type(std::string search_term) const;

	void check_incorrect_read();


private:
	std::set<std::unique_ptr<CelestialObject>> data;

	template<class type>
	void create_object(std::istream& is, const std::string object_type, bool& data_read);
};


template<class type>
inline void DataContainer::create_object(std::istream& is, const std::string object_type, bool& data_read)
	// Creates an object if object_type is equivalent to type::get_object_type(). type must be derived from CelestialObject.
{
	if (object_type == type::get_object_type()) {
		auto object = std::make_unique<type>();
		is >> *object;
		data.insert(std::move(object));
		data_read = true;
	}
}

#endif
