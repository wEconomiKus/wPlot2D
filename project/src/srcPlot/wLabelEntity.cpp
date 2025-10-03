/**
 * @file wLabelEntity.cpp
 * @brief Implementation of the LabelEntity class.
 */

#include "wLabelEntity.hpp"
#include "wAxisEntity.hpp"

#include "../srcComponents/wPositionComponent.hpp"
#include "../srcComponents/wOffsetComponent.hpp"
#include "../srcComponents/wColorComponent.hpp"
#include "../srcComponents/wFontComponent.hpp"

namespace wPlot2D
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Constructors and destructors.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

LabelEntity::LabelEntity( const sf::Font& font, AxisType type, sf::Vector2f initialPosition )
:	mAlignment{ type },
	mCharacterSize{ 25 },
	mValue{ 0.0f },
	mDecimalPlaces{ 1 },
	mOffset{ sf::Vector2f( 0.0f, 0.0f ) },
	mCustomLabels{ "" },
	mUseCustomLabels{ false },
	mLabel{ font }
{
	addComponent< wEngine::PositionComponent >( initialPosition );
	addComponent< wEngine::OffsetComponent >( );
	addComponent< wEngine::ColorComponent >( sf::Color::Black );
	addComponent< wEngine::FontComponent >( font );

	mLabel.setCharacterSize( getCharacterSize( ) );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods: accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

float LabelEntity::getValue( ) const
{
	return mValue;
}

unsigned int LabelEntity::getCharacterSize( ) const
{
	return mCharacterSize;
}

int LabelEntity::getDecimalPlaces( ) const
{
	return mDecimalPlaces;
}

void LabelEntity::setCharacterSize( unsigned int newSize )
{
	mCharacterSize = newSize;
}

void LabelEntity::setLabelText( std::string text )
{
	mLabel.setString( text );
}

void LabelEntity::setFont( const sf::Font& font )
{
	auto fontComponent = requireComponent< wEngine::FontComponent >( "LabelEntity::setFont( )" );
	fontComponent->setFont( font );
}

void LabelEntity::setDecimalPlaces( int places )
{
	mDecimalPlaces = std::max( 0, places );
}

void LabelEntity::setCustomLabels( const std::string& labels )
{
	mCustomLabels = labels;
	mUseCustomLabels = true;
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

bool LabelEntity::usesCustomLabels( ) const
{
	return mUseCustomLabels;
}

std::string LabelEntity::formatLabel( float value )
{
	mValue = value;

	if (mUseCustomLabels)
	{
		return mCustomLabels;
	}
	else
	{
		std::ostringstream oss;
		oss << std::fixed << std::setprecision( mDecimalPlaces ) << value;
		return oss.str( );
	}
}

void LabelEntity::render( sf::RenderWindow& window )
{
	auto positionComponent = requireComponent< wEngine::PositionComponent >( "LabelEntity::render( )" );
	auto offsetComponent = requireComponent< wEngine::OffsetComponent >( "LabelEntity::render( )" );
	auto colorComponent = requireComponent< wEngine::ColorComponent >( "LabelEntity::render( )" );
	auto fontComponent = requireComponent< wEngine::FontComponent >( "LabelEntity::render( )" );

	sf::Vector2f position = positionComponent->getPosition( );
	sf::Color color = colorComponent->getColor( );

	mLabel.setFont( fontComponent->getFont( ) );
	mLabel.setCharacterSize( getCharacterSize( ) );
	mLabel.setFillColor( color );

	setLabelText( formatLabel( mValue ) );
	
	if (mAlignment == AxisType::X_AXIS)
	{
		offsetComponent->addOffset( { 0.0f, 5.0f } );
		sf::Vector2f offset = offsetComponent->getOffset( );
		sf::Vector2f center = sf::Vector2f( - mLabel.getGlobalBounds( ).size.x / 2.0f, - mLabel.getGlobalBounds( ).size.y / 2.0f );
		mLabel.setPosition( position + center + offset );
	}
	else
	{
		sf::Vector2f offset = offsetComponent->getOffset( );
		sf::Vector2f center = sf::Vector2f( - mLabel.getGlobalBounds( ).size.x, - mLabel.getGlobalBounds( ).size.y );
		mLabel.setPosition( position + center + offset );
	}

	window.draw( mLabel );
}

}// End of namespace wPlot2D