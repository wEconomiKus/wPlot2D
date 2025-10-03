/**
 * @file wScaleComponent.cpp
 * @brief Implementation of the ScaleComponent class.
 */

#include "wScaleComponent.hpp"

namespace wEngine
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Constructors and destructors.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

ScaleComponent::ScaleComponent( sf::Vector2f scale )
:	mScale{ scale }
{
	validatePositive( scale );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods: accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

sf::Vector2f ScaleComponent::getScale( ) const
{
	return mScale;
}

void ScaleComponent::setScale( sf::Vector2f newScale )
{
	validatePositive( newScale );
	mScale = newScale;
}

/*
+---------------------------------------------------------------------------------------------------------------------+
-> Méthodes public : debug.
+---------------------------------------------------------------------------------------------------------------------+
*/

void ScaleComponent::debugPrint( ) const
{
	std::cout << "Scale: (" << getScale( ).x << ", " << getScale( ).y << ")\n";
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Private method: internal validation.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void ScaleComponent::validatePositive( const sf::Vector2f& value ) const
{
	if (value.x <= 0.0f || value.y <= 0.0f)
	{
		throw std::invalid_argument( "ScaleComponent: scale values must be strictly positive." );
	}
}

}//End of namespace wEngine