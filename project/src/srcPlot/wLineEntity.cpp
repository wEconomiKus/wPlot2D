/**
 * @file wLineEntity.cpp
 * @brief Implementation of the LineEntity class.
 */

#include "wLineEntity.hpp"
#include "../srcComponents/wPositionComponent.hpp"
#include "../srcComponents/wScaleComponent.hpp"
#include "../srcComponents/wColorComponent.hpp"
#include "../srcComponents/wThicknessComponent.hpp"
#include "../srcComponents/wLineStyleComponent.hpp"
#include "../srcUtils/wLineDrawer.hpp"

namespace wPlot2D
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Constructors and destructors.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

LineEntity::LineEntity( const sf::Vector2f& origin, const sf::Vector2f& scale, const sf::Vector2f& start, const sf::Vector2f& end, bool withArrow )
:   mStart{ start },
	mEnd{ end },
	mWithArrow{ withArrow },
	mArrowSize{ 4.0f }
{
	addComponent< wEngine::PositionComponent >( origin );
	addComponent< wEngine::ScaleComponent >( scale );
	addComponent< wEngine::ColorComponent >( sf::Color::Black );
	addComponent< wEngine::ThicknessComponent >( 2.0f );
	addComponent< wEngine::LineStyleComponent >( wEngine::LineStyleComponent::LineStyle::Solid );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods: accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

float LineEntity::getThickness( ) const
{
	return requireComponent< wEngine::ThicknessComponent >( "LineEntity::getThickness( )" )->getThickness( );
}

void LineEntity::setColor( sf::Color color )
{
	requireComponent< wEngine::ColorComponent >( "LineEntity::setColor( )" )->setColor( color );
}

void LineEntity::setThickness( float thickness )
{
	requireComponent< wEngine::ThicknessComponent >( "LineEntity::setThickness( )" )->setThickness( thickness );
}

void LineEntity::setLineStyle( wEngine::LineStyleComponent::LineStyle style )
{
	requireComponent< wEngine::LineStyleComponent >( "LineEntity::setLineStyle( )" )->setStyle( style );
}

void LineEntity::setDashLength( float dashLength )
{
	requireComponent< wEngine::LineStyleComponent >( "LineEntity::setDashLength( )" )->setDashLength( dashLength );
}

void LineEntity::setGapLength( float gapLength )
{
	requireComponent< wEngine::LineStyleComponent >( "LineEntity::setGapLength( )" )->setGapLength( gapLength );
}

sf::Vector2f LineEntity::getStartPoint( ) const
{
	return mStart;
}

sf::Vector2f LineEntity::getEndPoint( ) const
{
	return mEnd;
}

bool LineEntity::hasArrow( ) const
{
	return mWithArrow;
}

[[nodiscard]] float LineEntity::getArrowSize( ) const
{
	return mArrowSize;
}

void LineEntity::setArrowSize( float arrowSize )
{
	mArrowSize = arrowSize;
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void LineEntity::render( sf::RenderWindow& window )
{
	auto positionComponent	= requireComponent< wEngine::PositionComponent >( "LineEntity::render( )" );
	auto colorComponent		= requireComponent< wEngine::ColorComponent >( "LineEntity::render( )" );
	auto thicknessComponent	= requireComponent< wEngine::ThicknessComponent >( "LineEntity::render( )" );
	auto scaleComponent		= requireComponent< wEngine::ScaleComponent >( "LineEntity::render( )" );
	auto lineStyleComponent	= requireComponent< wEngine::LineStyleComponent >( "LineEntity::render( )" );

	sf::Vector2f origin	= positionComponent->getPosition( );
	sf::Color color		= colorComponent->getColor( );
	float thickness		= thicknessComponent->getThickness( );
	sf::Vector2f scale	= scaleComponent->getScale( );

	// Scale and origin transform
	sf::Vector2f p1( origin.x + mStart.x * scale.x, origin.y - mStart.y * scale.y );
	sf::Vector2f p2( origin.x + mEnd.x   * scale.x, origin.y - mEnd.y   * scale.y );

	// Draw arrowhead
	if (mWithArrow)
	{
		sf::Vector2f dir = (p2 - p1).normalized( );
		float arrowSize = thickness * mArrowSize;
		p2 -= dir * arrowSize;

		initArrowHead( p2, dir, arrowSize, color );
		window.draw( mArrowHead );
	}

	// Draw main line
	wEngine::LineDrawer::drawLine(
		window, p1, p2, color, thickness,
		lineStyleComponent->getStyle( ),
		lineStyleComponent->getDashLength( ),
		lineStyleComponent->getGapLength( )
	);
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Private methods.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void LineEntity::initArrowHead( const sf::Vector2f& lineEnd, const sf::Vector2f& dir, float arrowSize, sf::Color color )
{
	mArrowHead.setPointCount( 3 );

	sf::Vector2f perp = dir.perpendicular( );

	mArrowHead.setPoint( 0, lineEnd + perp * (arrowSize / 2.0f) );
	mArrowHead.setPoint( 1, lineEnd - perp * (arrowSize / 2.0f) );
	mArrowHead.setPoint( 2, lineEnd + dir * arrowSize );

	mArrowHead.setFillColor( color );
}

}//End of namespace wPlot2D