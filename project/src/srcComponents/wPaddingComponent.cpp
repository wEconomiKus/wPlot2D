/**
 * @file wPaddingComponent.cpp
 * @brief Implementation of the PaddingComponent class.
 */

#include "wPaddingComponent.hpp"

#include <stdexcept>

namespace wEngine
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Constructors and destructors.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

PaddingComponent::PaddingComponent( sf::Vector2f padding )
:	mPadding{ padding }
{
	validatePositive( padding );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods: accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void PaddingComponent::setPadding( sf::Vector2f padding )
{
	validatePositive( padding );
	mPadding = padding;
}

sf::Vector2f PaddingComponent::getPadding( ) const
{
	return mPadding;
}

/*
+---------------------------------------------------------------------------------------------------------------------+
-> Méthodes public : debug.
+---------------------------------------------------------------------------------------------------------------------+
*/

void PaddingComponent::debugPrint( ) const
{
	std::cout << "Padding: (" << getPadding( ).x << ", " << getPadding( ).y << ")\n";
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Private method: internal validation.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void PaddingComponent::validatePositive( const sf::Vector2f& value ) const
{
	if (value.x < 0.0f || value.y < 0.0f)
	{
		throw std::invalid_argument( "PaddingComponent: padding values must be non-negative." );
	}
}

}//End of namespace wEngine