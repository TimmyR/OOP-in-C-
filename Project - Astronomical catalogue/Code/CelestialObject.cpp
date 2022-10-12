#include "CelestialObject.h"

bool CelestialObject::operator==(const CelestialObject& object) const
    // Sets condition that only one observation of an object at one time is valid per experiment.
{
    return (name == object.name && experiment == object.experiment && observation_epoch == object.observation_epoch);
}

bool CelestialObject::operator<(const CelestialObject& object) const
{
    if (experiment < object.experiment) return true;
    if (experiment > object.experiment) return false;
    if (name < object.name) return true;
    if (name > object.name) return false;
    if (observation_epoch < observation_epoch) return true;
    return false;
    
    
    return false;
}

std::string CelestialObject::get_name()
{
    return name;
}

std::string CelestialObject::get_experiment()
{
    return experiment;
}

Date CelestialObject::get_date()
{
    return observation_epoch;
}

bool CelestialObject::invalid_state()
    // Returns true if the object hasn't been read correctly.
{
    return incorrect_read;
}

size_t CelestialObject::get_use_count()
{
    return use_count;
}

// Static variable definition
size_t CelestialObject::use_count{0};

