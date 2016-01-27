// segmentrng.hpp
// Aaron G. Tumulak

#pragma once

// std includes
#include <iostream>
#include <random>

// mc-solver includes
#include "segment.hpp"

class SegmentRng
{
    public:

        // Default constructor
        SegmentRng( std::default_random_engine &generator, const Segment &segment );

        // Sample cell position
        double SamplePosition();

        // Sample isotropic direction
        double SampleDirection();

        // Sample energy group
        double SampleEnergyGroup();

        // Sample distance to next event
        double SampleDistanceNextEvent( double energy );

        // Accessors and mutators //

        // Generator
        const std::default_random_engine &Generator() const { return generator_; };

    private:

        // Distribution typedefs
        typedef std::uniform_real_distribution<double> uniform_dist;
        typedef std::discrete_distribution<int> discrete_dist;
        typedef std::map<double,std::exponential_distribution<double>> exp_dist_map;

        // Reference to random number generator
        std::default_random_engine &generator_;

        // Const reference to segment
        const Segment &segment_;

        // Distribution for cell source position (0,cell_width)
        uniform_dist cell_source_dist_;

        // Distribution for isotropic direction cosine [-1,1]
        uniform_dist isotropic_dist_;

        // Distribution for cell source energy groups
        discrete_dist group_source_dist_;

        // Map of energy groups and distributions to next event (0,inf)
        exp_dist_map next_event_dists_;
};
