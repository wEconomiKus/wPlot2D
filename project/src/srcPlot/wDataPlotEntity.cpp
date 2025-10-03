/**
 * @file wDataPlotEntity.cpp
 * @brief Implementation of the DataPlotEntity class.
 */

#include "wDataPlotEntity.hpp"

#include "../srcUtils/wLineDrawer.hpp"

#include "../srcComponents/wColorComponent.hpp"
#include "../srcComponents/wPositionComponent.hpp"
#include "../srcComponents/wScaleComponent.hpp"
#include "../srcComponents/wThicknessComponent.hpp"

namespace wPlot2D
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Constructors and destructors.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

DataPlotEntity::DataPlotEntity( const sf::Vector2f origin, const sf::Vector2f scale, const std::vector< sf::Vector2f >& dataPoints )
:	mDataPoints{ dataPoints }
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

sf::Color DataPlotEntity::getColor( ) const
{
	auto colorComponent = requireComponent< wEngine::ColorComponent >( "DataPlotEntity::getColor( )" );
	return colorComponent->getColor( );
}

float DataPlotEntity::getThickness( )
{
	auto thicknessComponent = requireComponent< wEngine::ThicknessComponent >( "DataPlotEntity::getThickness( )" );
	return thicknessComponent->getThickness( );
}

wEngine::LineStyleComponent::LineStyle DataPlotEntity::getLineStyle( )
{
	auto styleComponent = requireComponent< wEngine::LineStyleComponent >( "DataPlotEntity::getLineStyle( )" );
	return styleComponent->getStyle( );
}

float DataPlotEntity::getDashLength( )
{
	auto styleComponent = requireComponent< wEngine::LineStyleComponent >( "DataPlotEntity::getDashLength( )" );
	return styleComponent->getDashLength( );
}

float DataPlotEntity::getGapLength( )
{
	auto styleComponent = requireComponent< wEngine::LineStyleComponent >( "DataPlotEntity::getGapLength( )" );
	return styleComponent->getGapLength( );
}

void DataPlotEntity::setColor( sf::Color color )
{
	auto colorComponent = requireComponent< wEngine::ColorComponent >( "DataPlotEntity::setColor( )" );
	colorComponent->setColor( color );
}

void DataPlotEntity::setThickness( float thickness )
{
	auto thicknessComponent = requireComponent< wEngine::ThicknessComponent >( "DataPlotEntity::setThickness( )" );
	thicknessComponent->setThickness( thickness );
}

void DataPlotEntity::setLineStyle( wEngine::LineStyleComponent::LineStyle style )
{
	auto styleComponent = requireComponent< wEngine::LineStyleComponent >( "DataPlotEntity::setLineStyle( )" );
	styleComponent->setStyle( style );
}

void DataPlotEntity::setDashLength( float dashLength )
{
	auto styleComponent = requireComponent< wEngine::LineStyleComponent >( "DataPlotEntity::setDashLength( )" );
	styleComponent->setDashLength( dashLength );
}

void DataPlotEntity::setGapLength( float gapLength )
{
	auto styleComponent = requireComponent< wEngine::LineStyleComponent >( "DataPlotEntity::setGapLength( )" );
	styleComponent->setGapLength( gapLength );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void DataPlotEntity::drawDataPlot( sf::RenderWindow &window )
{
	if (mDataPoints.size( ) < 2)
	{
		return;
	}

	auto positionComponent	= requireComponent< wEngine::PositionComponent >( "DataPlotEntity::drawDataPlot" );
	auto scaleComponent		= requireComponent< wEngine::ScaleComponent >( "DataPlotEntity::drawDataPlot" );
	auto colorComponent		= requireComponent< wEngine::ColorComponent >( "DataPlotEntity::drawDataPlot" );
	auto thicknessComponent	= requireComponent< wEngine::ThicknessComponent >( "DataPlotEntity::drawDataPlot" );
	auto styleComponent		= requireComponent< wEngine::LineStyleComponent >( "DataPlotEntity::drawDataPlot" );

	sf::Vector2f origin	= positionComponent->getPosition( );
	sf::Vector2f scale	= scaleComponent->getScale( );
	sf::Color color		= colorComponent->getColor( );
	float thickness		= thicknessComponent->getThickness( );
	auto style			= styleComponent->getStyle( );
	float dashLength	= styleComponent->getDashLength( );
	float gapLength		= styleComponent->getGapLength( );

	// Transform points
	std::vector< sf::Vector2f > transformed;
	transformed.reserve( mDataPoints.size( ) );

	for (auto& p : mDataPoints)
	{
		transformed.emplace_back( origin.x + p.x * scale.x, origin.y - p.y * scale.y );
	}

	// Draw as connected line segments
	float patternOffset = 0.0f;
	for (size_t i = 0; i < transformed.size( ) - 1; ++i)
	{
		const sf::Vector2f& p1 = transformed[ i ];
		const sf::Vector2f& p2 = transformed[ i+1 ];
		if (p1 == p2)
		{
			continue;
		}

		patternOffset = wEngine::LineDrawer::drawLine(
			window,
			p1,
			p2,
			color,
			thickness,
			style,
			dashLength,
			gapLength,
			patternOffset
		);
	}
}

}//End of namespace wPlot2D