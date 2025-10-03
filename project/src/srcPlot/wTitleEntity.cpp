/**
 * @file wTitleEntity.cpp
 * @brief Implementation of the TitleEntity class.
 */

#include "wTitleEntity.hpp"

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

TitleEntity::TitleEntity( const sf::Font& font, const std::string& title, bool hasFrame )
:	mTitleText( font ),
	mFrame{ hasFrame }
{
	addComponent< wEngine::FontComponent >( font );

	init( title );
}

TitleEntity::TitleEntity( const sf::Font& font, const std::wstring& title, bool hasFrame )
:	mTitleText( font ),
	mFrame{ hasFrame }
{
	addComponent< wEngine::FontComponent >( font );
	
	init( title );
}

template < typename T >
void TitleEntity::init( const T& title )
{
	mTitleText.setString( title );
	mTitleText.setCharacterSize( 30 );

	sf::Color defaultColor{ sf::Color::Black };

	addComponent< wEngine::OffsetComponent >( );
	addComponent< wEngine::PositionComponent >( );
	addComponent< wEngine::ColorComponent >( defaultColor );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods (Text): accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

unsigned int TitleEntity::getCharacterSize( ) const
{
	return mTitleText.getCharacterSize( );
}

sf::FloatRect TitleEntity::getTextSize( ) const
{
	return mTitleText.getLocalBounds( );
}

void TitleEntity::setTextColor( sf::Color textColor )
{
	auto colorComponent = requireComponent< wEngine::ColorComponent >( "TitleEntity::setTextColor( )" );
	colorComponent->setColor( textColor );
}

void TitleEntity::setOffset( sf::Vector2f offset )
{
	auto offsetComponent = requireComponent< wEngine::OffsetComponent >( "TitleEntity::setOffset( )" );
	offsetComponent->setOffset( offset );
}

void TitleEntity::setCharacterSize( unsigned int size )
{
	mTitleText.setCharacterSize( size );
}

void TitleEntity::setFont( const sf::Font& font )
{
	auto fontComponent = requireComponent< wEngine::FontComponent >( "TitleEntity::setFont( )" );
	fontComponent->setFont( font );
}


/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods (Frame): accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void TitleEntity::setFrameEnabled( bool enabled )
{
	mFrame.setEnabled( enabled );
}

bool TitleEntity::isFrameEnabled( ) const
{
	return mFrame.isEnabled( );
}

void TitleEntity::setFrameOutlineColor( const sf::Color& color )
{
	mFrame.setOutlineColor( color );
}

void TitleEntity::setFrameFillColor( const sf::Color& color )
{
	mFrame.setFillColor( color );
}

void TitleEntity::setFrameThickness( float thickness )
{
	mFrame.setThickness( thickness );
}

void TitleEntity::setPadding( sf::Vector2f padding )
{
	mFrame.setPadding( padding );
}

sf::Color TitleEntity::getFrameOutlineColor( ) const
{
	return mFrame.getOutlineColor( );
}

sf::Color TitleEntity::getFrameFillColor( ) const
{
	return mFrame.getFillColor( );
}

float TitleEntity::getFrameThickness( ) const
{
	return mFrame.getThickness( );
}

sf::Vector2f TitleEntity::getPadding( ) const
{
	return mFrame.getPadding( );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void TitleEntity::render( sf::RenderWindow& window )
{
	auto positionComponent = requireComponent< wEngine::PositionComponent >( "TitleEntity::render( )" );
	auto offsetComponent = requireComponent< wEngine::OffsetComponent >( "TitleEntity::render( )" );
	auto colorComponent = requireComponent< wEngine::ColorComponent >( "TitleEntity::render( )" );
	auto fontComponent = requireComponent< wEngine::FontComponent >( "TitleEntity::render( )" );

	mTitleText.setFont( fontComponent->getFont( ) );

	sf::Vector2f finalPosition = positionComponent->getPosition( ) + offsetComponent->getOffset( );

	sf::FloatRect bounds = mTitleText.getLocalBounds( );

	// Center origin based on visual bounds
	mTitleText.setOrigin( {
		bounds.position.x + bounds.size.x / 2.0f,
		bounds.position.y + bounds.size.y / 2.0f
	} );

	mTitleText.setFillColor( colorComponent->getColor( ) );
	mTitleText.setPosition( finalPosition );

	mFrame.update( bounds, finalPosition );
	mFrame.render( window );

	window.draw( mTitleText );
}

}// End of namespace wPlot2D