/**
 * @file wNotchIntervalComponent.cpp
 * @brief Implementation of the wNotchIntervalComponent class.
 */

#include "wNotchIntervalComponent.hpp"

#include <iostream>
#include <stdexcept>

namespace wEngine
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Constructors and destructors.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

NotchIntervalComponent::NotchIntervalComponent( float interval )
:	mInterval{ interval }
{
	validateInterval( interval );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods: accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

float NotchIntervalComponent::getInterval( ) const
{
	return mInterval;
}

void NotchIntervalComponent::setInterval( float newInterval )
{
	validateInterval( newInterval );
	mInterval = newInterval;
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods: debug.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void NotchIntervalComponent::debugPrint( ) const
{
	std::cout << "Notch Interval: " << mInterval << std::endl;
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Private methods.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void NotchIntervalComponent::validateInterval( float value ) const
{
	if (value <= 0.0f)
	{
		throw std::invalid_argument( "NotchIntervalComponent: interval must be strictly positive." );
	}
}

} // End of namespace wEngine