/**
 * @file wLegendEntity.cpp
 * @brief Implementation of the LegendEntity class.
 */

#include "wLegendEntity.hpp"

#include "../srcComponents/wPositionComponent.hpp"
#include "../srcComponents/wColorComponent.hpp"
#include "../srcComponents/wFontComponent.hpp"

namespace wPlot2D
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Constructors and destructors.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

LegendEntity::LegendEntity( const sf::Font& font, const sf::Vector2f& position, bool hasFrame )
:	mFont{ font },
	mFrame{ hasFrame }
{
	addComponent< wEngine::PositionComponent >( position );
	addComponent< wEngine::ColorComponent >( sf::Color::Black );
	addComponent< wEngine::FontComponent >( font );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods: addItem( ).
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void LegendEntity::addItem( const std::string& label, FunctionEntity* function )
{
	addItemGeneric( label, function );
}

void LegendEntity::addItem( const std::wstring& label, FunctionEntity* function )
{
	addItemGeneric( label, function );
}

void LegendEntity::addItem( const std::string& label, DataPlotEntity* plot )
{
	addItemGeneric( label, plot );
}

void LegendEntity::addItem( const std::wstring& label, DataPlotEntity* plot )
{
	addItemGeneric( label, plot );
}

template < typename LabelT, typename SourceT >
void LegendEntity::addItemGeneric( const LabelT& label, SourceT* source )
{
	if (!source)
	{
		return;
	}

	bool hasArrow = false;
	auto line = std::make_unique< LineEntity >(
		sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 1.0f, 1.0f ),
		sf::Vector2f( 0.0f, 0.0f ), sf::Vector2f( 40.0f, 0.0f ),
		hasArrow
	);

	line->setColor( source->getColor( ) );
	line->setThickness( source->getThickness( ) );
	line->setLineStyle( source->getLineStyle( ) );
	line->setDashLength( source->getDashLength( ) );
	line->setGapLength( source->getGapLength( ) );

	createItem( label, std::move( line ) );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods: accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void LegendEntity::setFrameEnabled( bool enabled )
{
	mFrame.setEnabled( enabled );
}

void LegendEntity::setFrameFillColor( const sf::Color& color )
{
	mFrame.setFillColor( color );
}

void LegendEntity::setFrameOutlineColor( const sf::Color& color )
{
	mFrame.setOutlineColor( color );
}

void LegendEntity::setFrameThickness( float thickness )
{
	mFrame.setThickness( thickness );
}

void LegendEntity::setPadding( const sf::Vector2f& padding )
{
	mFrame.setPadding( padding );
}

void LegendEntity::setFont( const sf::Font& font )
{
	auto fontComponent = requireComponent< wEngine::FontComponent >( "LegendEntity::setFont( )" );
	fontComponent->setFont( font );
}

void LegendEntity::setCharacterSize( unsigned int size )
{
	mCharacterSize = size;
	for (auto& item : mItems)
	{
		item.labelText.setCharacterSize( size );
	}
}

void LegendEntity::setTextColor( const sf::Color& color )
{
	auto colorComponent = requireComponent< wEngine::ColorComponent >( "LegendEntity::setTextColor( )" );
	colorComponent->setColor( color );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Private methods.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

template< typename T >
void LegendEntity::createItem( const T& label, std::unique_ptr< LineEntity > line )
{
	auto colorComponent = requireComponent< wEngine::ColorComponent >( "LegendEntity::addItem( )" );
	sf::Color textColor = colorComponent->getColor( );

	sf::Text text( mFont, label, mCharacterSize );
	text.setFillColor( textColor );

	mItems.emplace_back( std::move( line ), std::move( text ) );
}

void LegendEntity::render( sf::RenderWindow& window )
{
	// --- Required ECS components ---
	auto positionComponent = requireComponent< wEngine::PositionComponent >( "LegendEntity::render( )" );
	auto colorComponent = requireComponent< wEngine::ColorComponent >( "LegendEntity::render( )" );
	auto fontComponent = requireComponent< wEngine::FontComponent >( "LegendEntity::render( )" );

	sf::Vector2f position = positionComponent->getPosition( );
	sf::Color color = colorComponent->getColor( );

	// --- Layout parameters ---
	float spacing = static_cast< float >( mCharacterSize ) + 10.0f;	// vertical gap between items
	float lineLength = 40.0f;										// fixed legend line length
	float margin = 10.0f;											// space between line and text
	float maxTextWidth = 0.0f;										// widest label text
	float maxTextHeight = 0.0f;										// tallest label text (usually tied to font size)

	// Compute max text dimensions across all items
	for (auto& item : mItems)
	{
		item.labelText.setFont( fontComponent->getFont( ) );
		item.labelText.setFillColor( color );

		sf::FloatRect bounds = item.labelText.getLocalBounds( );
		maxTextWidth = std::max( maxTextWidth, bounds.size.x );
		maxTextHeight = std::max( maxTextHeight, bounds.size.y );
	}

	// --- Total height of the legend block ---
	float legendHeight = (mItems.size( ) > 1)
		? (static_cast< float >( mItems.size( ) - 1 ) * spacing + maxTextHeight)
		: maxTextHeight;

	// X coordinate of the "line column" (all lines aligned vertically)
	float lineColumnX = position.x - (lineLength + margin + maxTextWidth) / 2.0f;

	// Vertical offset so that the whole legend is centered on position.y
	float yOffset = position.y - legendHeight / 2.0f;

	// --- Place each legend item (line + text) ---
	for (size_t i = 0; i < mItems.size( ); ++i)
	{
		auto& item = mItems[ i ];

		// Vertical center of this row
		sf::FloatRect bounds = item.labelText.getLocalBounds( );
		float yBase = yOffset + i * spacing;

		// Center origin of the text on its visual bounds
		item.labelText.setOrigin( {
			bounds.position.x + bounds.size.x / 2.0f,
			bounds.position.y + bounds.size.y / 2.0f
		} );

		// (1) Line: left column, vertically centered
		sf::Vector2f linePos( lineColumnX, yBase + maxTextHeight / 2.0f );
		item.line->getComponent< wEngine::PositionComponent >( )->setPosition( linePos );

		// (2) Text: right of the line, vertically aligned
		sf::Vector2f textPos( lineColumnX + lineLength + margin + bounds.size.x / 2.0f, yBase + bounds.size.y / 2.0f );
		item.labelText.setPosition( textPos );
	}

	// --- Draw frame if enabled ---
	if (mFrame.isEnabled( ))
	{
		sf::Vector2f padding = mFrame.getPadding( );

		float frameWidth  = lineLength + margin + maxTextWidth + padding.x;
		float frameHeight = legendHeight + padding.y;

		mFrame.update( sf::FloatRect( { 0.0f, 0.0f }, { frameWidth, frameHeight } ), position );
		mFrame.render( window );
	}

	// --- Draw all items (line + label) ---
	for (auto& item : mItems)
	{
		item.line->render( window );
		window.draw( item.labelText );
	}
}

} // namespace wPlot2D