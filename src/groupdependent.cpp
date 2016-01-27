// groupdependent.cpp
// Aaron G. Tumulak

// std includes
#include <cassert>
#include <map>
#include <numeric>
#include <random>
#include <vector>

// mc-solver includes
#include "groupdependent.hpp"

// Default constructor
GroupDependent::GroupDependent()
{}

// Initialize constructor
GroupDependent::GroupDependent( double energy, double value ):
    data_( {{ energy, value }} )
{}

// Sum all values
double GroupDependent::GroupSum() const
{
    return std::accumulate( data_.begin(), data_.end(), 0.0,
            []( const double &x, const std::pair<double,double> &p )
            { return x + p.second; });
}

// Groupwise energy distribution of source neutrons
std::discrete_distribution<int> GroupDependent::GroupDistribution() const
{
    // Construct vector of map values by increasing key
    assert( !data_.empty() );
    std::vector<double> map_values;
    for( auto it = data_.begin(); it != data_.end(); it++ )
    {
        map_values.push_back( it->second );
    }
    // Create distribution
    return std::discrete_distribution<int> ( map_values.begin(), map_values.end() );
};

// Map of exponential distributions of each group
GroupDependent::exp_dist_map GroupDependent::ExponentialDistributions() const
{
    // Construct map of exponential distributions
    assert( !data_.empty() );
    GroupDependent::exp_dist_map output;
    for( auto it = data_.begin(); it != data_.end(); it++ )
    {
        output[ it->first ] = std::exponential_distribution<double> ( it-> second );
    }
    return output;
}

// Read value
double GroupDependent::at( double energy ) const
{
    // Check that group exists
    assert( data_.find( energy ) != data_.end() );

    // Return value
    return data_.at( energy );
}

// Write value
void GroupDependent::Write( double energy, double value )
{
    // Check input arguments are valid
    assert( energy > 0.0 && value >= 0.0 );

    // Do not allow overwriting
    assert( data_.find( energy ) == data_.end() );

    // Write new value at energy
    data_[ energy ] = value;
}

// Add value
void GroupDependent::Add( double energy, double value )
{
    // Check input arguments are valid
    assert( energy > 0.0 && value >= 0.0 );

    // Add value to energy
    data_[ energy ] += value;
}

// Read energy at index
double GroupDependent::energyat( unsigned int index ) const
{
    // Check that index exists
    assert( index < data_.size() );

    // Return value
    return std::next( data_.begin(), index )->first;
}

// Friend functions //

// Overload operator<<()
std::ostream &operator<< ( std::ostream &out, const GroupDependent &obj )
{
    out << std::scientific;

    for(auto it = obj.data_.begin(); it != obj.data_.end(); it++ )
    {
        out << "Group: " << it->first << "\t" << "Value: " << it->second << std::endl;
    }

    out << std::defaultfloat;

    return out;
}
