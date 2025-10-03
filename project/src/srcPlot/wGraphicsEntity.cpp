/**
 * @file wGraphicsEntity.cpp
 * @brief Implementation of the GraphicsEntity class.
 */

#include "wGraphicsEntity.hpp"

#include <string>
#include "../srcUtils/wPathUtils.hpp"

#include "../srcComponents/wColorComponent.hpp"
#include "../srcComponents/wPositionComponent.hpp"
#include "../srcComponents/wScaleComponent.hpp"
#include "../srcComponents/wOffsetComponent.hpp"
#include "../srcComponents/wThicknessComponent.hpp"

namespace wPlot2D
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Constructors and destructors.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

GraphicsEntity::GraphicsEntity( const std::string& windowTitle, const sf::Vector2u& windowSize,
	const sf::Vector2f& originFactor, const sf::Vector2f& scaleFactor )
{
	mAssets.LoadFont( "Courier", wEngine::PathUtils::getExecutableDir( ) + "/../Resources/Fonts/CourierPrimeCode.ttf" );
	mAssets.LoadFont( "Inconsolata", wEngine::PathUtils::getExecutableDir( ) + "/../Resources/Fonts/Inconsolata/Inconsolata.otf" );

	validateNormalizedFactor( originFactor );

	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;

	mWindow.create( sf::VideoMode( windowSize ), windowTitle, sf::Style::None, sf::State::Windowed, settings );

	addComponent< wEngine::PositionComponent >( convertNormalizedToPixels( originFactor ) );
	addComponent< wEngine::ScaleComponent >( convertNormalizedToPixels( scaleFactor ) );
	addComponent< wEngine::OffsetComponent >( );

	auto colorComponent = addComponent< wEngine::ColorComponent >( sf::Color::White );
	mWindow.clear( colorComponent->getColor( ) );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods: accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

sf::RenderWindow& GraphicsEntity::getWindow( )
{
	return mWindow;
}

sf::Vector2u GraphicsEntity::getWindowSize( ) const
{
	return mWindow.getSize( );
}

void GraphicsEntity::setWindowSize( const sf::Vector2u& newSize )
{
	mWindow.setSize( newSize );
	sf::View view(sf::FloatRect({0.f, 0.f}, {static_cast<float>(newSize.x), static_cast<float>(newSize.y)}));
	mWindow.setView(view);
}

void GraphicsEntity::setWindowTitle( const std::string& title )
{
	mWindow.setTitle( title );
}

void GraphicsEntity::setBackgroundColor( const sf::Color& color )
{
	mWindow.clear( color );
}



void GraphicsEntity::addFont( const std::string& name, const std::string& fileName )
{
	mAssets.LoadFont( name, fileName );
}


sf::Font& GraphicsEntity::getFont( const std::string name )
{
	return mAssets.getFont( name );
}










sf::Vector2f GraphicsEntity::getOrigin( ) const
{
	auto positionComponent = requireComponent< wEngine::PositionComponent >( "GraphicsEntity::getOrigin( )" );
	return positionComponent->getPosition( );
}

void GraphicsEntity::setOrigin( sf::Vector2f originFactor )
{
	validateNormalizedFactor( originFactor );

	auto positionComponent = requireComponent< wEngine::PositionComponent >( "GraphicsEntity::setOrigin( )" );
	positionComponent->setPosition( convertNormalizedToPixels( originFactor ) );
}

[[nodiscard]] sf::Vector2f GraphicsEntity::getScale( ) const
{
	auto scaleComponent = requireComponent< wEngine::ScaleComponent >( "GraphicsEntity::getScale( )" );
	return scaleComponent->getScale( );
}

void GraphicsEntity::setScale( sf::Vector2f scaleFactor )
{
	auto scaleComponent = requireComponent< wEngine::ScaleComponent >( "GraphicsEntity::setScale( )" );
	scaleComponent->setScale( convertNormalizedToPixels( scaleFactor ) );
}

sf::Vector2f GraphicsEntity::getOffset( ) const
{
	auto offsetComponent = requireComponent< wEngine::OffsetComponent >( "GraphicsEntity::getOffset( )" );
	return offsetComponent->getOffset( );
}

void GraphicsEntity::setOffset( sf::Vector2f offset )
{
	auto offsetComponent = requireComponent< wEngine::OffsetComponent >( "GraphicsEntity::setOffset( )" );
	offsetComponent->setOffset( offset );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods (Axis): accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

AxisEntity* GraphicsEntity::addAxis( AxisType type, sf::Vector2f axisRange )
{
	if (type == AxisType::X_AXIS)
	{
		mAxisX = std::make_unique< AxisEntity >( mAssets.getFont( "Courier" ), getOrigin( ), getScale( ), getOffset( ), type, axisRange );
		return mAxisX ? mAxisX.get( ) : nullptr;
	}
	else
	{
		mAxisY = std::make_unique< AxisEntity >( mAssets.getFont( "Courier" ), getOrigin( ), getScale( ), getOffset( ), type, axisRange );
		return mAxisY ? mAxisY.get( ) : nullptr;
	}
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods (Title): accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

TitleEntity* GraphicsEntity::addTitle( const std::string& title, TitleAlignment alignment )
{
	return addTitleImpl( title, alignment );
}

TitleEntity* GraphicsEntity::addTitle( const std::wstring& title, TitleAlignment alignment )
{
	return addTitleImpl( title, alignment );
}

template < typename T >
TitleEntity* GraphicsEntity::addTitleImpl( const T& title, TitleAlignment titleAlignment )
{
	mTitle = std::make_unique< TitleEntity >( mAssets.getFont( "Courier" ), title, true );
	mTitle->setCharacterSize( 60 );

	mAlignment = titleAlignment;

	auto colorComponent = mTitle->requireComponent< wEngine::ColorComponent >( "GraphicsEntity::addTitleImpl( )" );
	auto positionComponent = mTitle->requireComponent< wEngine::PositionComponent >( "GraphicsEntity::addTitleImpl( )" );
	auto offsetComponent = mTitle->requireComponent< wEngine::OffsetComponent >( "GraphicsEntity::addTitleImpl( )" );

	const float windowWidth = static_cast< float >( mWindow.getSize( ).x );
	const float windowHeight = static_cast< float >( mWindow.getSize( ).y );

	sf::Vector2f basePosition;
	if (titleAlignment == TitleAlignment::Bottom)
	{
		basePosition = sf::Vector2f( windowWidth / 2.0f, windowHeight - mTitle->getTextSize( ).size.y / 2.0f );
		offsetComponent->setOffset( { 0.0f, -50.0f } );
	}
	else
	{
		basePosition = sf::Vector2f( windowWidth / 2.0f, mTitle->getTextSize( ).size.y / 2.0f );
		offsetComponent->setOffset( { 0.0f, 50.0f } );
	}

	positionComponent->setPosition( basePosition );

	return mTitle ? mTitle.get( ) : nullptr;
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods (Function): accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

FunctionEntity* GraphicsEntity::addFunction( std::function< double( double ) > func, double startX, double endX, size_t nbPoints )
{
	sf::Vector2f origin = getOrigin( );
	sf::Vector2f scale  = getScale( );

	auto functionEntity = std::make_unique< FunctionEntity >( origin, scale, func );
	mFunctions.push_back( FunctionData{ std::move( functionEntity ), startX, endX, nbPoints } );

	return mFunctions.back( ).entity.get( );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods (DataPlot): accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

DataPlotEntity* GraphicsEntity::addDataPlot( const std::vector< sf::Vector2f >& dataPoints )
{
	sf::Vector2f origin = getOrigin( );
	sf::Vector2f scale  = getScale( );

	auto dataPlotEntity = std::make_unique< DataPlotEntity >( origin, scale, dataPoints );
	mDataPlots.push_back( DataPlotData{ std::move( dataPlotEntity ) } );

	return mDataPlots.back( ).entity.get( );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods (Legend): accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

LegendEntity* GraphicsEntity::addLegend( const sf::Vector2f& position, bool hasFrame )
{
	sf::Vector2u windowSize = mWindow.getSize( );
	sf::Vector2f pixelPos( position.x * windowSize.x, position.y * windowSize.y );

	mLegend = std::make_unique< LegendEntity >( mAssets.getFont( "Courier" ), pixelPos, hasFrame );

	return mLegend ? mLegend.get( ) : nullptr;
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods (Text): accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

TitleEntity* GraphicsEntity::addText( const std::string& text, sf::Vector2f position )
{
	return initText( text, position );
}

TitleEntity* GraphicsEntity::addText( const std::wstring& text, sf::Vector2f position )
{
	return initText( text, position );
}

template < typename T >
TitleEntity* GraphicsEntity::initText( const T& text, sf::Vector2f position )
{
	auto textEntity = std::make_unique< TitleEntity >( mAssets.getFont( "Courier" ), text, true );

	auto positionComponent = textEntity->template requireComponent< wEngine::PositionComponent >( "GraphicsEntity::addText( )" );
	sf::Vector2u windowSize = mWindow.getSize( );
	sf::Vector2f pixelPos( position.x * windowSize.x, position.y * windowSize.y );
	positionComponent->setPosition( pixelPos );

	mTexts.push_back( TextData{ std::move( textEntity ) } );

	return mTexts.back( ).entity.get( );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods (LinePlot): accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

LineEntity* GraphicsEntity::addLine( const sf::Vector2f& start, const sf::Vector2f& end, bool withArrow )
{
	sf::Vector2f origin = getOrigin( );
	sf::Vector2f scale  = getScale( );

	auto lineEntity = std::make_unique< LineEntity >( origin, scale, start, end, withArrow );

	mLines.push_back( LineData{ std::move( lineEntity ) } );

	return mLines.back( ).entity.get( );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public method: Saves a screenshot of the current window contents to an image file.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void GraphicsEntity::saveToFile( const std::string& filename )
{
	render( );

	sf::Texture texture( sf::Vector2u( mWindow.getSize( ).x, mWindow.getSize( ).y ) );
	texture.update( mWindow );

	sf::Image screenshot = texture.copyToImage( );
	if( !screenshot.saveToFile( filename ) )
	{
		throw std::runtime_error( "Failed to save window screenshot to " + filename );
	}
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Private methods.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void GraphicsEntity::render( )
{
	for (auto& f : mFunctions)
	{
		f.entity->drawFunction( mWindow, f.startX, f.endX, f.nbPoints );
	}

	for (auto& data : mDataPlots)
	{
		data.entity->drawDataPlot( mWindow );
	}

	for (auto& line : mLines)
	{
		line.entity->render( mWindow );
	}

	if (mAxisX)
	{
		mAxisX->render( mWindow );
	}

	if (mAxisY)
	{
		mAxisY->render( mWindow );
	}

	if (mTitle)
	{
		if (mTitle->isFrameEnabled( ))
		{
			auto positionComponent = mTitle->requireComponent< wEngine::PositionComponent >( "GraphicsEntity::addTitle( )" );
			sf::Vector2f basePosition = positionComponent->getPosition( );
			(mAlignment == TitleAlignment::Bottom
				? basePosition.y -= mTitle->getFrameThickness( )
				: basePosition.y += mTitle->getFrameThickness( ));

			positionComponent->setPosition( basePosition );
		}

		mTitle->render( mWindow );
	}

	if (mLegend)
	{
		mLegend->render( mWindow );
	}

	for (auto& text : mTexts)
	{
		text.entity->render( mWindow );
	}
}

void GraphicsEntity::validateNormalizedFactor( const sf::Vector2f& factor ) const
{
	if (factor.x < 0.0f || factor.x > 1.0f || factor.y < 0.0f || factor.y > 1.0f)
	{
		throw std::invalid_argument( "GraphicsEntity: originFactor must be in the range [0, 1]." );
	}
}

sf::Vector2f GraphicsEntity::convertNormalizedToPixels( const sf::Vector2f& factor ) const
{
	return sf::Vector2f( factor.x * getWindowSize( ).x, factor.y * getWindowSize( ).y );
}

}//End of namespace wPlot2D