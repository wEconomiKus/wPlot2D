/**
 * @file wThicknessComponent.cpp
 * @brief Implementation of the ThicknessComponent class.
 */

#include "wThicknessComponent.hpp"

#include <string>
#include <stdexcept>

namespace wEngine
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Constructors and destructors.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

ThicknessComponent::ThicknessComponent( float thickness )
:	mThickness{ thickness }
{
	validatePositive( thickness );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods: accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

float ThicknessComponent::getThickness( ) const
{
	return mThickness;
}

void ThicknessComponent::setThickness( float newThickness )
{
	validatePositive( newThickness );
	mThickness = newThickness;
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Méthodes public : debug.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void ThicknessComponent::debugPrint( ) const
{
	std::cout << "Thickness: " << getThickness( ) << "\n";
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Private method: internal validation.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void ThicknessComponent::validatePositive( float value ) const
{
	if (value <= 0.0f)
	{
		throw std::invalid_argument( "ThicknessComponent error: thickness must be strictly positive (received: " + std::to_string( value ) + ")" );
	}
}

}//End of namespace wEngine