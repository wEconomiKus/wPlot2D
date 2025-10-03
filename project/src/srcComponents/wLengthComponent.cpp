/**
 * @file wLengthComponent.cpp
 * @brief Implementation of the LengthComponent class.
 */

#include "wLengthComponent.hpp"

#include <stdexcept>
#include <string>


namespace wEngine
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Constructors and destructors.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

LengthComponent::LengthComponent( float length )
:	mLength{ length }
{
	validatePositive( length );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods: accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

float LengthComponent::getLength( ) const
{
	return mLength;
}

void LengthComponent::setLength( float newLength )
{
	validatePositive( newLength );
	mLength = newLength;
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Méthodes public : debug.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void LengthComponent::debugPrint( ) const
{
	std::cout << "Length: " << getLength( ) << "\n";
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Private method: internal validation.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void LengthComponent::validatePositive( float value ) const
{
	if (value <= 0.0f)
	{
		throw std::invalid_argument( "LengthComponent error: length must be strictly positive (received: " + std::to_string( value ) + ")" );
	}
}

}//End of namespace wEngine