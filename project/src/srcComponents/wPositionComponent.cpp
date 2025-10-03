/**
 * @file wPositionComponent.cpp
 * @brief Implementation of the PositionComponent class.
 */

#include "wPositionComponent.hpp"

namespace wEngine
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Constructors and destructors.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

PositionComponent::PositionComponent( sf::Vector2f position )
:	mPosition{ position },
	mLastPosition{ position }
{

}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods: accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

sf::Vector2f PositionComponent::getPosition( ) const
{
	return mPosition;
}

sf::Vector2f PositionComponent::getLastPosition( ) const
{
	return mLastPosition;
}

void PositionComponent::setPosition( sf::Vector2f newPosition )
{
	mLastPosition = mPosition;
	mPosition = newPosition;
}

/*
+---------------------------------------------------------------------------------------------------------------------+
-> Méthodes public.
+---------------------------------------------------------------------------------------------------------------------+
*/

void PositionComponent::move( const sf::Vector2f& offset )
{
	mLastPosition = mPosition;
	mPosition += offset;
}

/*
+---------------------------------------------------------------------------------------------------------------------+
-> Méthodes public : debug.
+---------------------------------------------------------------------------------------------------------------------+
*/

void PositionComponent::debugPrint( ) const
{
	std::cout << "Position: (" << getPosition( ).x << ", " << getPosition( ).y << ")\n";
}

}//End of namespace wEngine