// groupgroupdependent.cpp
// Aaron G. Tumulak

// std includes
#include <cassert>
#include <vector>

// mc-solver includes
#include "groupgroupdependent.hpp"

// Default constructor
GroupGroupDependent::GroupGroupDependent()
{}

// Map of discrete distributions of each group
GroupGroupDependent::discrete_dist_map GroupGroupDependent::DiscreteDistributions() const
{
    GroupGroupDependent::discrete_dist_map distributions;
    for( auto it = data_.begin(); it != data_.end(); it++ )
    {
        double from_energy = it->first;
        // Create map of scattering energy distributions for each from_energy
        distributions[ from_energy ] = it->second.GroupDistribution();
    }
    return distributions;
}

// Read value
GroupDependent GroupGroupDependent::at( double energy ) const
{
    // Check that group exists
    assert( data_.find( energy ) != data_.end() );

    // Return value
    return data_.at( energy );
}

// Write value
void GroupGroupDependent::Write( double energy_1, double energy_2, double value )
{
    // Check input arguments are valid
    assert( energy_1 > 0.0 && energy_1 > 0.0 && value >= 0.0 );

    // Check if GroupDependent value exists at energy_1
    if( data_.find( energy_1 ) != data_.end() )
    {
        // Group at energy_1 exists, write/overwrite value at energy_2
        data_[ energy_1 ].Write( energy_2, value );
    }
    else
    {
        // Group at energy_1 doesn't exist, create new group
        data_[ energy_1 ] = GroupDependent( energy_2, value );
    }
}

// Friend functions //

// Overload operator<<()
std::ostream &operator<< ( std::ostream &out, const GroupGroupDependent &obj )
{
    for( auto it = obj.data_.begin(); it != obj.data_.end(); it++ )
    {
        out << "Group: " << std::scientific << it->first << std::endl;
        out << it->second;
        if( it != prev( obj.data_.end() ) )
        {
            out << std::endl;
        }
    }

    out << std::defaultfloat;

    return out;
}
