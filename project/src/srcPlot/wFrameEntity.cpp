/**
 * @file wFrameEntity.cpp
 * @brief Implementation of the FrameEntity class.
 */

#include "wFrameEntity.hpp"

#include "../srcComponents/wPositionComponent.hpp"
#include "../srcComponents/wThicknessComponent.hpp"
#include "../srcComponents/wColorComponent.hpp"
#include "../srcComponents/wPaddingComponent.hpp"

namespace wPlot2D
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Constructors and destructors.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

FrameEntity::FrameEntity( bool enabled )
:	mEnabled{ enabled }
{
	addComponent< wEngine::ColorComponent >( sf::Color::Black );
	addComponent< wEngine::PaddingComponent >( sf::Vector2f( 20.0f, 20.0f ) );
	addComponent< wEngine::ThicknessComponent >( 1.0f );

	mFrame.setOutlineColor( sf::Color::Black );
	mFrame.setFillColor( sf::Color::Transparent );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods: accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void FrameEntity::setEnabled( bool enabled )
{
	mEnabled = enabled;
}

bool FrameEntity::isEnabled( ) const
{
	return mEnabled;
}

sf::Color FrameEntity::getFillColor( ) const
{
	return mFrame.getFillColor( );
}

sf::Color FrameEntity::getOutlineColor( ) const
{
	return mFrame.getOutlineColor( );
}

float FrameEntity::getThickness( ) const
{
	auto thicknessComponent = requireComponent< wEngine::ThicknessComponent >( "FrameEntity::setThickness( )" );
	return thicknessComponent->getThickness( );
}

sf::Vector2f FrameEntity::getPadding( ) const
{
	auto paddingComponent = requireComponent< wEngine::PaddingComponent >( "FrameEntity::setPadding( )" );
	return paddingComponent->getPadding( );
}

void FrameEntity::setFillColor( const sf::Color& color )
{
	mFrame.setFillColor( color );
}

void FrameEntity::setOutlineColor( const sf::Color& color )
{
	mFrame.setOutlineColor( color );
}

void FrameEntity::setThickness( float thickness )
{
	auto thicknessComponent = requireComponent< wEngine::ThicknessComponent >( "FrameEntity::setThickness( )" );
	thicknessComponent->setThickness( thickness );
}

void FrameEntity::setPadding( const sf::Vector2f& padding )
{
	auto paddingComponent = requireComponent< wEngine::PaddingComponent >( "FrameEntity::setPadding( )" );
	paddingComponent->setPadding( padding );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void FrameEntity::update( const sf::FloatRect& contentBounds, const sf::Vector2f& position )
{
	if (!mEnabled)
	{
		return;
	}

	auto padding	= requireComponent< wEngine::PaddingComponent >( "FrameEntity::update( )" )->getPadding( );
	auto thickness	= requireComponent< wEngine::ThicknessComponent >( "FrameEntity::update( )" )->getThickness( );

	float width  = contentBounds.size.x + padding.x;
	float height = contentBounds.size.y + padding.y;

	mFrame.setOutlineThickness( thickness );
	mFrame.setSize( { width, height } );
	mFrame.setOrigin( { width / 2.0f, height / 2.0f } );
	mFrame.setPosition( position );
}

void FrameEntity::render( sf::RenderWindow& window )
{
	if (mEnabled)
	{
		window.draw( mFrame );
	}
}

}//End of namespace wPlot2D