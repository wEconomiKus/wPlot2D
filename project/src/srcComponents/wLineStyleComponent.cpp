/**
 * @file wLineStyleComponent.cpp
 * @brief Implementation of the LineStyleComponent class.
 */

#include "wLineStyleComponent.hpp"

#include <stdexcept>
#include <string>

namespace wEngine
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Constructors and destructors.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

LineStyleComponent::LineStyleComponent( LineStyle style )
:	mStyle{ style },
	mDashLength{ 20.0f },
	mGapLength{ 10.0f }
{

}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods: accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

LineStyleComponent::LineStyle LineStyleComponent::getStyle( ) const
{
	return mStyle;
}

void LineStyleComponent::setStyle( LineStyle style )
{
	mStyle = style;
}

float LineStyleComponent::getDashLength( ) const
{
	return mDashLength;
}

void LineStyleComponent::setDashLength( float dashLength )
{
	if (dashLength <= 0.0f)
	{
		throw std::invalid_argument( "LineStyleComponent: dash length must be > 0." );
	}
	mDashLength = dashLength;
}

float LineStyleComponent::getGapLength( ) const
{
	return mGapLength;
}

void LineStyleComponent::setGapLength( float gapLength )
{
	if (gapLength < 0.0f)
	{
		throw std::invalid_argument( "LineStyleComponent: gap length cannot be negative." );
	}
	mGapLength = gapLength;
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public method: debug.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void LineStyleComponent::debugPrint( ) const
{
	std::string styleStr;
	switch (mStyle)
	{
		case LineStyle::Solid:
			styleStr = "Solid"; 
			break;
		case LineStyle::Dotted:
			styleStr = "Dotted";
			break;
		case LineStyle::Dashed:
			styleStr = "Dashed";
			break;
		default:
			break;
	}

	std::cout	<< "LineStyle: "		<< styleStr
				<< " | Dash length: "	<< mDashLength
				<< " | Gap length: "	<< mGapLength << "\n";
}

}//End of namespace wEngine