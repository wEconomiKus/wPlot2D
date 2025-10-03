/**
 * @file wFunctionEntity.cpp
 * @brief Implementation of the FunctionEntity class.
 */

#include "wFunctionEntity.hpp"

#include "../srcUtils/wLineDrawer.hpp"
#include "../srcUtils/wMathUtils.hpp"

#include "../srcComponents/wColorComponent.hpp"
#include "../srcComponents/wPositionComponent.hpp"
#include "../srcComponents/wScaleComponent.hpp"
#include "../srcComponents/wOffsetComponent.hpp"
#include "../srcComponents/wThicknessComponent.hpp"
#include "../srcComponents/wFunctionComponent.hpp"
#include "../srcComponents/wDiscontinuityComponent.hpp"
#include "../srcComponents/wRotationComponent.hpp"

#include <numbers>

namespace wPlot2D
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Constructors and destructors.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

FunctionEntity::FunctionEntity( const sf::Vector2f origin, const sf::Vector2f scale, std::function< double( double ) > func )
{
	addComponent< wEngine::PositionComponent >( origin );
	addComponent< wEngine::ScaleComponent >( scale );
	addComponent< wEngine::ColorComponent >( sf::Color::Black );
	addComponent< wEngine::ThicknessComponent >( 3.0f );
	addComponent< wEngine::FunctionComponent >( func );
	addComponent< wEngine::DiscontinuityComponent >( );
	addComponent< wEngine::OffsetComponent >( );
	addComponent< wEngine::RotationComponent >( );
	addComponent< wEngine::LineStyleComponent >( wEngine::LineStyleComponent::LineStyle::Solid );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods: accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

sf::Vector2f FunctionEntity::getPosition( ) const
{
	auto positionComponent = requireComponent< wEngine::PositionComponent >( "FunctionEntity::getPosition( )" );
	return positionComponent->getPosition( );
}

sf::Color FunctionEntity::getColor( ) const
{
	auto colorComponent = requireComponent< wEngine::ColorComponent >( "FunctionEntity::getColor( )" );
	return colorComponent->getColor( );
}

float FunctionEntity::getThickness( ) const
{
	auto thicknessComponent = requireComponent< wEngine::ThicknessComponent >( "FunctionEntity::getThickness( )" );
	return thicknessComponent->getThickness( );
}

wEngine::LineStyleComponent::LineStyle FunctionEntity::getLineStyle( ) const
{
	auto lineStyleComponent = requireComponent< wEngine::LineStyleComponent >( "FunctionEntity::setLineStyle( )" );
	return lineStyleComponent->getStyle( );
}

float FunctionEntity::getDashLength( ) const
{
	auto lineStyleComponent = requireComponent< wEngine::LineStyleComponent >( "FunctionEntity::setLineStyle( )" );
	return lineStyleComponent->getDashLength( );
}

float FunctionEntity::getGapLength( ) const
{
	auto lineStyleComponent = requireComponent< wEngine::LineStyleComponent >( "FunctionEntity::setLineStyle( )" );
	return lineStyleComponent->getGapLength( );
}

sf::Vector2f FunctionEntity::getOffset( ) const
{
	auto offsetComponent = requireComponent< wEngine::OffsetComponent >( "FunctionEntity::getOffset( )" );
	return offsetComponent->getOffset( );
}

float FunctionEntity::getRotation( ) const
{
	auto rotationComponent = requireComponent< wEngine::RotationComponent >( "FunctionEntity::getRotation( )" );
	return rotationComponent->getAngle( );
}

void FunctionEntity::setPosition( sf::Vector2f position )
{
	auto positionComponent = requireComponent< wEngine::PositionComponent >( "FunctionEntity::setPosition( )" );
	positionComponent->setPosition( position );
}

void FunctionEntity::setColor( sf::Color color )
{
	auto colorComponent = requireComponent< wEngine::ColorComponent >( "FunctionEntity::setColor( )" );
	colorComponent->setColor( color );
}

void FunctionEntity::setThickness( float thickness )
{
	auto thicknessComponent = requireComponent< wEngine::ThicknessComponent >( "FunctionEntity::setThickness( )" );
	thicknessComponent->setThickness( thickness );
}

void FunctionEntity::setLineStyle( wEngine::LineStyleComponent::LineStyle style )
{
	auto styleComponent = requireComponent< wEngine::LineStyleComponent >( "FunctionEntity::setLineStyle( )" );
	styleComponent->setStyle( style );
}

void FunctionEntity::setDashLength( float dashLength )
{
	auto styleComponent = requireComponent< wEngine::LineStyleComponent >( "FunctionEntity::setDashLength( )" );
	styleComponent->setDashLength( dashLength );
}

void FunctionEntity::setGapLength( float gapLength )
{
	auto styleComponent = requireComponent< wEngine::LineStyleComponent >( "FunctionEntity::setGapLength( )" );
	styleComponent->setGapLength( gapLength );
}

void FunctionEntity::setOffset( float offsetX, float offsetY )
{
	auto offsetComponent = requireComponent< wEngine::OffsetComponent >( "FunctionEntity::setOffset( )" );
	offsetComponent->setOffset( { offsetX, offsetY } );
}

void FunctionEntity::setRotation( float angleDegrees )
{
	auto rotationComponent = requireComponent< wEngine::RotationComponent >( "FunctionEntity::setRotation( )" );
	rotationComponent->setAngle( angleDegrees );
}

void FunctionEntity::setScale( sf::Vector2f scale )
{
	auto scaleComponent = requireComponent< wEngine::ScaleComponent >( "FunctionEntity::setScale( )" );
	scaleComponent->setScale( scale );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void FunctionEntity::addExcludedInterval(double min, double max)
{
	auto discontinuityComponent = requireComponent< wEngine::DiscontinuityComponent >( "FunctionEntity::addExcludedInterval( )" );
	discontinuityComponent->addExcludedInterval( min, max );
}

void FunctionEntity::clearExcludedIntervals( )
{
	auto disc = requireComponent< wEngine::DiscontinuityComponent >( "FunctionEntity::clearExcludedIntervals( )" );
	disc->clearExcludedIntervals( );
}

void FunctionEntity::alignToYAxis(float normalizedOffsetX, float normalizedOffsetY)
{
	auto scaleComponent = requireComponent< wEngine::ScaleComponent >( "FunctionEntity::alignToYAxis( )" );
	auto rotationComponent = requireComponent< wEngine::RotationComponent >( "FunctionEntity::alignToYAxis( )" );
	auto offsetComponent = requireComponent< wEngine::OffsetComponent >( "FunctionEntity::alignToYAxis( )" );

	sf::Vector2f currentScale = scaleComponent->getScale( );

	// (1) Apply 90 degrees rotation
	rotationComponent->setAngle( 90.0f );

	// (2) Swap scales
	scaleComponent->setScale( { currentScale.y, currentScale.x } );

	// (3) Apply relative offset (optional)
	offsetComponent->setOffset( {
		normalizedOffsetX * currentScale.x / currentScale.y,
		normalizedOffsetY * currentScale.y / currentScale.x
	});
}

void FunctionEntity::drawFunction( sf::RenderWindow& window, double startX, double endX, size_t nbPoints )
{
	// --- Retrieve required components ---
	auto positionComponent		= requireComponent< wEngine::PositionComponent >( "FunctionEntity::drawFunction( )" );
	auto colorComponent			= requireComponent< wEngine::ColorComponent >( "FunctionEntity::drawFunction( )" );
	auto thicknessComponent		= requireComponent< wEngine::ThicknessComponent >( "FunctionEntity::drawFunction( )" );
	auto scaleComponent			= requireComponent< wEngine::ScaleComponent >( "FunctionEntity::drawFunction( )" );
	auto functionComponent		= requireComponent< wEngine::FunctionComponent >( "FunctionEntity::drawFunction( )" );
	auto discontinuityComponent	= requireComponent< wEngine::DiscontinuityComponent >( "FunctionEntity::drawFunction( )" );
	auto lineStyleComponent		= requireComponent< wEngine::LineStyleComponent >( "FunctionEntity::drawFunction( )" );
	auto offsetComponent		= requireComponent< wEngine::OffsetComponent >( "FunctionEntity::drawFunction( )" );
	auto rotationComponent		= requireComponent< wEngine::RotationComponent >( "FunctionEntity::drawFunction( )" );

	sf::Vector2f origin	= positionComponent->getPosition( );
	sf::Color color		= colorComponent->getColor( );
	float thickness		= thicknessComponent->getThickness( );
	sf::Vector2f scale	= scaleComponent->getScale( );
	sf::Vector2f offset	= offsetComponent->getOffset( );
	float rotationAngle	= rotationComponent->getAngle( );

	// --- Sample the function in the user-defined domain ---
	std::vector< double > xPoints = wEngine::MathUtils::linspace( startX, endX, nbPoints );

	// --- Rotation (in radians)
	float rad	= rotationAngle * static_cast< float >( std::numbers::pi ) / 180.0f;
	float cosA	= std::cos( rad );
	float sinA	= std::sin( rad );

	// --- Split the curve into continuous segments ---
	// Each segment represents a part of the function without discontinuity.
	std::vector< std::vector< sf::Vector2f > > segments;
	segments.emplace_back( );

	for (double x : xPoints)
	{
		// (1) Skip points inside excluded intervals.
		if (discontinuityComponent->isInExcludedInterval( x ))
		{
			// Close current segment if it has points and start a new one.
			if (!segments.back( ).empty( ))
			{
				segments.emplace_back( );
			}
			continue;
		}

		// (2) Evaluate the function at x.
		double y = functionComponent->calculate( x );

		// (3) Handle undefined results (NaN or Inf) as discontinuities.
		if (std::isnan( y ) || std::isinf( y ))
		{
			if (!segments.back( ).empty( ))
			{
				segments.emplace_back( );// start new segment
			}
			continue;
		}
		
		// (4) Compute point.

		// --- Compute point with scale ---
		// Convert logical coordinates (x, y) into scaled pixel space.
		// Note: y is inverted because in SFML the y-axis grows downward.
		float px = static_cast< float >( x ) * scale.x;
		float py = -static_cast <float >( y ) * scale.y;

		// --- Apply rotation around origin ---
		// Rotate the scaled point using the standard 2D rotation matrix:
		// [ cosA -sinA ] [px]
		// [ sinA  cosA ] [py]
		// The rotation is always performed around the logical origin (0,0).
		float rx = px * cosA - py * sinA;
		float ry = px * sinA + py * cosA;

		// --- Apply offset AFTER rotation ---
		// Offset is applied after rotation to avoid "rotating the offset" itself. This allows a clean translation of the entire rotated curve.
		rx += offset.x * scale.x;
		ry -= offset.y * scale.y;

		// --- Translate to window origin ---
		// Finally, shift everything by the entity's origin, which acts as the anchor point of the whole plot in the window coordinate system.
		sf::Vector2f point(origin.x + rx, origin.y + ry);

		// (5) Add point to the current continuous segment.
		segments.back( ).push_back( point );
	}

	// --- Render each valid continuous segment ---
	// At least 2 points are required to draw a polyline.
	for (auto& segment : segments)
	{
		if (segment.size( ) >= 2)
		{
			wEngine::LineDrawer::drawPolylineRound(
				window,
				segment,
				color,
				thickness,
				lineStyleComponent->getStyle( ),
				lineStyleComponent->getDashLength( ),
				lineStyleComponent->getGapLength( ),
				12 // arcResolution (default for rounded joins)
			);
		}
	}
}

}//End of namespace wPlot2D