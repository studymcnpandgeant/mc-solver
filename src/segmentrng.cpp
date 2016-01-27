// segmentrng.cpp
// Aaron G. Tumulak

// std includes
#include <cmath>
#include <iostream>

// mc-solver includes
#include "segmentrng.hpp"

// Default constructor
SegmentRng::SegmentRng( std::default_random_engine &generator, const Segment &segment ):
    generator_( generator ),
    segment_( segment ),
    cell_source_dist_( uniform_dist( std::nextafter( 0.0, 0.1 ), segment_.Width() / segment_.NumCells() ) ),
    isotropic_dist_( uniform_dist( -1.0, std::nextafter( 1.0, 1.1 ) ) ),
    group_source_dist_( segment.MaterialReference().ExtSource().GroupDistribution() )
{}

// Sample cell position
double SegmentRng::SamplePosition()
{
    return cell_source_dist_( generator_ );
}

// Sample isotropic direction
double SegmentRng::SampleDirection()
{
    return isotropic_dist_( generator_ );
}

// Sample energy group
double SegmentRng::SampleEnergyGroup()
{
    unsigned int index = group_source_dist_( generator_ );
    return segment_.MaterialReference().ExtSource().energyat( index );
}