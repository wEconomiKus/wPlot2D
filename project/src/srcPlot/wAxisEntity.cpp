/**
 * @file wAxisEntity.cpp
 * @brief Implementation of the AxisEntity class.
 */

#include "wAxisEntity.hpp"

#include "../srcComponents/wPositionComponent.hpp"
#include "../srcComponents/wScaleComponent.hpp"
#include "../srcComponents/wColorComponent.hpp"
#include "../srcComponents/wThicknessComponent.hpp"
#include "../srcComponents/wOffsetComponent.hpp"
#include "../srcComponents/wNotchIntervalComponent.hpp"
#include "../srcComponents/wLengthComponent.hpp"

namespace wPlot2D
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Constructors and destructors.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

AxisEntity::AxisEntity( sf::Font& font, sf::Vector2f origin, sf::Vector2f scale, sf::Vector2f offset, AxisType type, sf::Vector2f axisRange )
:	mTitleFont{ font },
	mLabelsFont{ font },
	mAxisType{ type },
	mAxisRange{ axisRange },
	mArrowSize{ 4.0f },
	mNotchPosition{ NotchPosition::Center },
	mHasLabels{ false }
{
	addComponent< wEngine::PositionComponent >( origin );
	addComponent< wEngine::ScaleComponent >( scale );
	addComponent< wEngine::OffsetComponent >( offset );
	addComponent< wEngine::ColorComponent >( sf::Color::Black );
	addComponent< wEngine::ThicknessComponent >( 5.0f );

	construct( );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods: accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void AxisEntity::setColor( sf::Color color )
{
	auto colorComponent = requireComponent< wEngine::ColorComponent >( "AxisEntity::setColor( )" );
	colorComponent->setColor( color );
}

void AxisEntity::setThickness( float thickness )
{
	auto thicknessComponent = requireComponent< wEngine::ThicknessComponent >( "AxisEntity::setThickness( )" );
	thicknessComponent->setThickness( thickness );
}

void AxisEntity::setArrowSize( float arrowSize )
{
	mArrowSize = arrowSize;
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods: accessors and mutators for axis title.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void AxisEntity::setTitleOffset( sf::Vector2f titleOffset )
{
	auto offsetComponent = mTitle->requireComponent< wEngine::OffsetComponent >( "AxisEntity::setTitleOffset( )" );
	offsetComponent->setOffset( titleOffset );
}

sf::Vector2f AxisEntity::getTitleOffset( ) const
{
	auto offsetComponent = mTitle->requireComponent< wEngine::OffsetComponent >( "AxisEntity::getTitleOffset( )" );
	return offsetComponent->getOffset( );
}

void AxisEntity::setTitleCharacterSize( unsigned int size )
{
	mTitle->setCharacterSize( size );
}

void AxisEntity::setTitleFont( const sf::Font& font )
{
	mTitle->setFont( font );
}

void AxisEntity::setTitleColor( sf::Color newColor )
{
	auto colorComponent = mTitle->requireComponent< wEngine::ColorComponent >( "AxisEntity::setTitleColor( )" );
	colorComponent->setColor( newColor );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods: accessors and mutators for notches.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void AxisEntity::addNotches( float interval, NotchPosition position, bool hasLabels )
{
	addComponent< wEngine::NotchIntervalComponent >( interval );
	mNotchPosition = position;

	mHasLabels = hasLabels;

	initNotches( );
}

void AxisEntity::setNotchesColor( const sf::Color& color )
{
	for (auto& notch : mNotches)
	{
		auto colorComponent = notch->requireComponent< wEngine::ColorComponent >( "AxisEntity::setNotchesColor( )" );
		colorComponent->setColor( color );
	}
}

void AxisEntity::setNotchesThickness( float newThickness )
{
	for (auto& notch : mNotches)
	{
		auto thicknessComponent = notch->requireComponent< wEngine::ThicknessComponent >( "AxisEntity::setNotchesThickness( )" );
		auto positionComponent = notch->requireComponent< wEngine::PositionComponent >( "AxisEntity::setNotchesThickness( )" );

		float oldThickness = thicknessComponent->getThickness( );
		thicknessComponent->setThickness( newThickness );

		sf::Vector2f deltaNotches{ 0.0f, 0.0f };

		if (mAxisType == AxisType::X_AXIS)
		{
			deltaNotches.x = ( oldThickness - newThickness ) / 2.0f;
		}
		else
		{
			deltaNotches.y = ( oldThickness - newThickness ) / 2.0f;
		}

		positionComponent->move( deltaNotches );
	}
}

void AxisEntity::setNotchesLength( float newLength )
{
	sf::Vector2f deltaLabel{ 0.0f, 0.0f };

	for (auto& notch : mNotches)
	{
		auto lengthComponent = notch->requireComponent< wEngine::LengthComponent >( "AxisEntity::setNotchesLength( )" );
		auto positionComponent = notch->requireComponent< wEngine::PositionComponent >( "AxisEntity::setNotchesLength( )" );

		float oldLength = lengthComponent->getLength( );
		lengthComponent->setLength( newLength );

		sf::Vector2f deltaNotches{ 0.0f, 0.0f };
		
		if (mAxisType == AxisType::X_AXIS)
		{
			if (mNotchPosition == NotchPosition::Center)
			{
				deltaNotches.y = (oldLength - newLength) / 2.0f;
				deltaLabel.y = -(oldLength - newLength) / 2.0f;
			}
			else if (mNotchPosition == NotchPosition::Above)
			{
				deltaNotches.y = oldLength - newLength;
				deltaLabel.y = 0.0f;
			}
			else if (mNotchPosition == NotchPosition::Below)
			{
				deltaNotches.y = 0.0f;
				deltaLabel.y = -(oldLength - newLength);
			}
		}
		else if (mAxisType == AxisType::Y_AXIS)
		{
			if (mNotchPosition == NotchPosition::Center)
			{
				deltaNotches.x = (oldLength - newLength) / 2.0f;
				deltaLabel.x = deltaNotches.x;
			}
			else if (mNotchPosition == NotchPosition::Above)
			{
				deltaNotches.x = 0.0f;
				deltaLabel.x = 0.0f;
			}
			else if (mNotchPosition == NotchPosition::Below)
			{
				deltaNotches.x = (oldLength - newLength);
				deltaLabel.x = (oldLength - newLength);
			}
		}

		positionComponent->move( deltaNotches );
	}

	addLabelsOffset( deltaLabel );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods: accessors and mutators for labels.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void AxisEntity::setLabelsFont( const sf::Font& font )
{
	for (auto& labels : mLabels)
	{
		labels->setFont( font );
	}
}

void AxisEntity::setLabelsColor( const sf::Color& color )
{
	for (auto& labels : mLabels)
	{
		auto colorComponent = labels->requireComponent< wEngine::ColorComponent >( "AxisEntity::setLabelsColor( )" );
		colorComponent->setColor( color );
	}
}

std::vector< sf::Vector2f > AxisEntity::getLabelsOffset( ) const
{
	std::vector< sf::Vector2f > offsets;

	for (auto& labels : mLabels)
	{
		auto offsetComponent = labels->requireComponent< wEngine::OffsetComponent >( "AxisEntity::getLabelsOffset( )" );
		offsets.push_back( offsetComponent->getOffset( ) );
	}	

	return offsets;
}

void AxisEntity::setLabelsOffset( sf::Vector2f offset )
{
	for (auto& labels : mLabels)
	{
		auto offsetComponent = labels->requireComponent< wEngine::OffsetComponent >( "AxisEntity::setLabelsOffset( )" );
		offsetComponent->setOffset( offset );
	}
}

void AxisEntity::addLabelsOffset( sf::Vector2f delta )
{
	for (auto& labels : mLabels)
	{
		auto offsetComponent = labels->requireComponent< wEngine::OffsetComponent >( "AxisEntity::setLabelsOffset( )" );
		offsetComponent->addOffset( delta );
	}
}

void AxisEntity::setLabelsCharacterSize( unsigned int newSize )
{
	for (auto& labels : mLabels)
	{
		labels->setCharacterSize( newSize );
	}
}

void AxisEntity::setLabelsDecimalPlaces( int places )
{
	for (auto& labels : mLabels)
	{
		labels->setDecimalPlaces( places );
	}
}

void AxisEntity::setCustomLabels( const std::vector< std::string >& labels )
{
	mLabels.erase(
		std::remove_if(
			mLabels.begin( ),
			mLabels.end( ),
			[ & ]( std::unique_ptr< LabelEntity >& label )
			{
				size_t index = static_cast< size_t >( label->getValue( ) );
				if (index < labels.size( ))
				{
					label->setCustomLabels( labels[ index ] );
					return false;
				}
				return true;
			} ),
		mLabels.end( ) );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void AxisEntity::render( sf::RenderWindow& window )
{
	construct( );

	if (mAxisLine)
	{
		mAxisLine->render( window );
	}

	if (mTitle)
	{
		mTitle->render( window );
	}

	for (auto& notch : mNotches)
	{
		notch->render( window );
	}

	for (auto& labels : mLabels)
	{
		labels->render( window );
	}
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Private methods.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void AxisEntity::construct( )
{
	auto colorComponent = requireComponent< wEngine::ColorComponent >( "AxisEntity::construct( )" );
	auto positionComponent = requireComponent< wEngine::PositionComponent >( "AxisEntity::construct( )" );
	auto scaleComponent = requireComponent< wEngine::ScaleComponent >( "AxisEntity::construct( )" );
	auto offsetComponent = requireComponent< wEngine::OffsetComponent >( "AxisEntity::construct( )" );
	auto thicknessComponent = requireComponent< wEngine::ThicknessComponent >( "AxisEntity::construct( )" );

	sf::Color color = colorComponent->getColor( );
	sf::Vector2f origin = positionComponent->getPosition( );
	sf::Vector2f scale = scaleComponent->getScale( );
	sf::Vector2f offset = offsetComponent->getOffset( );
	float thickness = thicknessComponent->getThickness( );

	sf::Vector2f start, end;
	if (mAxisType == AxisType::X_AXIS)
	{
		start = sf::Vector2f( mAxisRange.x + offset.x, 0.0f );
		end = sf::Vector2f(	mAxisRange.y + offset.x, 0.0f );
	}
	else
	{
		start = sf::Vector2f( 0.0f,	mAxisRange.x + offset.y	);
		end = sf::Vector2f(	0.0f, mAxisRange.y + offset.y );
	}

	bool hasArrow{ true };
	mAxisLine = std::make_unique< LineEntity >( origin, scale, start, end, hasArrow );
	mAxisLine->setColor( color );
	mAxisLine->setThickness( thickness );
	mAxisLine->setLineStyle( wEngine::LineStyleComponent::LineStyle::Solid );
	mAxisLine->setArrowSize( mArrowSize );
}

void AxisEntity::addTitle( const std::wstring& title )
{
	initTitle( title );
}

void AxisEntity::addTitle( const std::string& title )
{
	initTitle( title );
}

template < typename T >
void AxisEntity::initTitle( const T& title )
{
	mTitle = std::make_unique< TitleEntity >( mTitleFont, title );
	sf::FloatRect bounds = mTitle->getTextSize( );

	sf::Vector2f end = mAxisLine->getEndPoint( );

	auto positionComponent = getComponent< wEngine::PositionComponent >( );
	auto scaleComponent = getComponent< wEngine::ScaleComponent >( );

	sf::Vector2f origin = positionComponent->getPosition( );
	sf::Vector2f scale = scaleComponent->getScale( );

	sf::Vector2f endScreen(
		origin.x + end.x * scale.x,
		origin.y - end.y * scale.y
	);

	sf::Vector2f position;
	sf::Vector2f defaultOffset;

	if (mAxisType == AxisType::X_AXIS)
	{
		defaultOffset = sf::Vector2f( 10.0f, 0.0f );
		position.x = endScreen.x + bounds.size.x / 2.0f + defaultOffset.x;
		position.y = origin.y + defaultOffset.y;
	}
	else
	{
		defaultOffset = sf::Vector2f( 0.0f, -5.0f );
		position.x = origin.x + defaultOffset.x;
		position.y = endScreen.y - bounds.size.y / 2.0f + defaultOffset.y;
	}

	auto titlePosComp = mTitle->requireComponent< wEngine::PositionComponent >( "AxisEntity::initTitle( )" );
	titlePosComp->setPosition( position );
}

void AxisEntity::initNotches( )
{
	// Clear previous notches and labels
	mNotches.clear( );
	mLabels.clear( );

	//--- Required components
	auto positionComponent = requireComponent< wEngine::PositionComponent >( "AxisEntity::initNotches( )" );
	auto offsetComponent = requireComponent< wEngine::OffsetComponent >( "AxisEntity::initNotches( )" );
	auto scaleComponent = requireComponent< wEngine::ScaleComponent >( "AxisEntity::initNotches( )" );
	auto intervalComponent = requireComponent< wEngine::NotchIntervalComponent >( "AxisEntity::initNotches( )" );

	//--- Optional styling components (inherited from axis)
	auto colorComponent = getComponent< wEngine::ColorComponent >( );
	auto thicknessComponent = getComponent< wEngine::ThicknessComponent >( );

	//--- Extract data
	sf::Vector2f origin = positionComponent->getPosition( );
	sf::Vector2f offset = offsetComponent->getOffset( );
	sf::Vector2f scale = scaleComponent->getScale( );
	float interval = intervalComponent->getInterval( );
	sf::Color axisColor = colorComponent ? colorComponent->getColor( ) : sf::Color::Black;
	float axisThickness = thicknessComponent? thicknessComponent->getThickness( ) : 2.0f;
	constexpr float notchSize = 16.0f;
	float NotchOffset = notchSize / 2.0f;

	// --- Logical bounds
	float logicalStart = std::ceil( mAxisRange.x / interval ) * interval;
	float logicalEnd = std::floor( mAxisRange.y / interval ) * interval;

	// --- Skip the origin notch ---
	// Numerical iteration may not give exactly 0.0f (e.g., due to floating-point error).
	// We therefore use a tolerance of interval/2 to ensure we exclude the origin and only the origin.
	float EPSILON = interval / 2.0f;

	// Generate notches
	if (mAxisType == AxisType::X_AXIS)
	{
		for (float unit = logicalStart; unit <= logicalEnd; unit += interval)
		{

			if (std::fabs( unit ) < EPSILON)
			{
				continue;
			}

			auto notch = std::make_unique< NotchEntity >( mAxisType  );
			notch->addComponent< wEngine::ColorComponent >( axisColor );
			notch->addComponent< wEngine::ThicknessComponent >( axisThickness );
			notch->addComponent< wEngine::LengthComponent >( notchSize );

			float pixelX = origin.x + (unit + offset.x) * scale.x - axisThickness / 2.0f;
			float pixelY = origin.y - notchSize / 2.0f;

			if (mNotchPosition != NotchPosition::Center)
			{
				pixelY += (mNotchPosition == NotchPosition::Above) ? -NotchOffset : NotchOffset;
			}

			notch->addComponent< wEngine::PositionComponent >( sf::Vector2f( pixelX, pixelY ) );

			mNotches.push_back( std::move( notch ) );

			if (mHasLabels)
			{
				sf::Vector2f labelPosition{ pixelX, pixelY + notchSize };
				auto labelEntity = std::make_unique< LabelEntity >( mLabelsFont, mAxisType, labelPosition );
				labelEntity->setLabelText( labelEntity->formatLabel( unit ) );
				mLabels.push_back( std::move( labelEntity ) );
			}
		}
	}
	else
	{
		for (float unit = logicalStart; unit <= logicalEnd; unit += interval)
		{
			if (std::fabs( unit ) < EPSILON)
			{
				continue;
			}

			auto notch = std::make_unique< NotchEntity >( mAxisType );
			notch->addComponent< wEngine::ColorComponent >( axisColor );
			notch->addComponent< wEngine::ThicknessComponent >( axisThickness );
			notch->addComponent< wEngine::LengthComponent >( notchSize );

// Note: the minus sign is intentional here (-unit).
// It ensures that Y-axis labels have the correct orientation (SFML's Y grows downward).
			float pixelY = origin.y + (-unit + offset.y) * scale.y - axisThickness / 2.0f;
			float pixelX = origin.x - notchSize / 2.0f;

			if (mNotchPosition != NotchPosition::Center)
			{
				pixelX += (mNotchPosition == NotchPosition::Above) ? NotchOffset : -NotchOffset;
			}

			notch->addComponent< wEngine::PositionComponent >( sf::Vector2f( pixelX, pixelY ) );

			mNotches.push_back( std::move( notch ) );

			if (mHasLabels)
			{
				sf::Vector2f labelPosition{ pixelX - notchSize, pixelY };
				auto labelEntity = std::make_unique< LabelEntity >( mLabelsFont, mAxisType, labelPosition );
				labelEntity->setLabelText( labelEntity->formatLabel( unit ) );

				mLabels.push_back( std::move( labelEntity ) );
			}
		}
	}
}

}//End of namespace wPlot2D