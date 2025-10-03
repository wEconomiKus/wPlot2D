/**
 * @file wColorComponent.cpp
 * @brief Implementation of the ColorComponent class.
 */

#include "wColorComponent.hpp"
#include <iostream>

namespace wEngine
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Constructors and destructors.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

ColorComponent::ColorComponent( sf::Color color )
:	mColor{ color }
{

}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods: accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

sf::Color ColorComponent::getColor( ) const
{
	return mColor;
}

void ColorComponent::setColor( sf::Color newColor )
{
	mColor = newColor;
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public method: debug.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void ColorComponent::debugPrint( ) const
{
	std::cout	<< "Color RGBA: ("
				<< static_cast< int >( mColor.r ) << ", "
				<< static_cast< int >( mColor.g ) << ", "
				<< static_cast< int >( mColor.b ) << ", "
				<< static_cast< int >( mColor.a ) << ")\n";
}

}//End of namespace wEngine