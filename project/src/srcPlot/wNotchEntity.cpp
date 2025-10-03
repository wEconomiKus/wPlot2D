/**
 * @file wNotchEntity.cpp
 * @brief Implementation of the NotchEntity class.
 */

#include "wNotchEntity.hpp"
#include "wAxisEntity.hpp"

#include "../srcComponents/wPositionComponent.hpp"
#include "../srcComponents/wColorComponent.hpp"
#include "../srcComponents/wThicknessComponent.hpp"
#include "../srcComponents/wLengthComponent.hpp"

namespace wPlot2D
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Constructors and destructors.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

NotchEntity::NotchEntity( AxisType type )
:	mAlignment{ type }
{

}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void NotchEntity::render( sf::RenderWindow& window )
{
	auto positionComponent	= requireComponent< wEngine::PositionComponent >( "NotchEntity::render( )" );
	auto thicknessComponent	= requireComponent< wEngine::ThicknessComponent >( "NotchEntity::render( )" );
	auto lengthComponent	= requireComponent< wEngine::LengthComponent >( "NotchEntity::render( )" );
	auto colorComponent		= requireComponent< wEngine::ColorComponent >( "NotchEntity::render( )" );

	sf::Vector2f pos	= positionComponent->getPosition( );
	sf::Color color		= colorComponent->getColor( );
	float thickness		= thicknessComponent->getThickness( );
	float length		= lengthComponent->getLength( );

	sf::RectangleShape shape;
	shape.setFillColor( color );
	shape.setPosition( pos );

	if (mAlignment == AxisType::X_AXIS)
	{
		shape.setSize( { thickness, length } );
	}
	else
	{
		shape.setSize( { length, thickness } );
	}

	window.draw( shape );
}

}// End of namespace wPlot2D