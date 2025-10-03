/**
 * @file wDiscontinuityComponent.cpp
 * @brief Implementation of the DiscontinuityComponent class.
 */

#include "wDiscontinuityComponent.hpp"

namespace wEngine
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods: accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

const std::vector< std::pair< double, double > >& DiscontinuityComponent::getExcludedIntervals( ) const
{
	return mExcludedIntervals;
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void DiscontinuityComponent::addExcludedInterval( double min, double max )
{
	if (min >= max)
	{
		throw std::invalid_argument( "DiscontinuityComponent::addExcludedInterval : min must be < max" );
	}
	mExcludedIntervals.emplace_back( min, max );
}

void DiscontinuityComponent::clearExcludedIntervals( )
{
	mExcludedIntervals.clear( );
}

bool DiscontinuityComponent::isInExcludedInterval( double x ) const
{
	for (const auto& interval : mExcludedIntervals)
	{
		if (x >= interval.first && x <= interval.second)
		{
			return true;
		}
	}
	return false;
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public method: debug.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void DiscontinuityComponent::debugPrint( ) const
{
	if (mExcludedIntervals.empty( ))
	{
		std::cout << "No excluded intervals defined.\n";
		return;
	}

	std::cout << "Excluded intervals:\n";
	for (const auto& interval : mExcludedIntervals)
	{
		std::cout << " - [" << interval.first << ", " << interval.second << "]\n";
	}
}

}//End of namespace wEngine