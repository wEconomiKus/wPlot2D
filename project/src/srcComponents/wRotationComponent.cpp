/**
 * @file wRotationComponent.cpp
 * @brief Implementation of the RotationComponent class.
 */

#include "wRotationComponent.hpp"

namespace wEngine
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Constructors and destructors.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

RotationComponent::RotationComponent( float angle )
:	mAngle{ angle }
{

}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods: accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void RotationComponent::setAngle( float angle )
{
	mAngle = angle;
}

float RotationComponent::getAngle( ) const
{
	return mAngle;
}

}//End of namespace wEngine