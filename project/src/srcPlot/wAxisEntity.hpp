/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_AXIS_ENTITY_HPP
#define W_AXIS_ENTITY_HPP

#include "../srcEntity/wEntity.hpp"
#include "../srcUtils/wAssetManager.hpp"

#include "wLineEntity.hpp"
#include "wNotchEntity.hpp"
#include "wTitleEntity.hpp"
#include "wLabelEntity.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wswitch-default"
#include <SFML/Graphics.hpp>
#pragma GCC diagnostic pop

#include <vector>

namespace wPlot2D
{

	/**
	 * @enum AxisType
	 * @brief Enum representing the type of axis to render.
	 */
	enum class AxisType
	{
		X_AXIS,
		Y_AXIS
	};

	/**
	 * @enum NotchPosition
	 * @brief Enum controlling the visual placement of notches relative to the axis.
	 */
	enum class NotchPosition
	{
		Center,
		Above,
		Below
	};

	/**
	 * @class AxisEntity
	 * @brief Represents a visual axis (X or Y) in a 2D plot with optional notches and title.
	 *
	 * This class manages the rendering of a coordinate axis in a Cartesian 2D system. It supports:
	 * - Rendering of an axis line with an arrowhead.
	 * - Adding notches (tick marks) with optional labels.
	 * - Attaching a customizable axis title.
	 *
	 * @see TitleEntity, LabelEntity, NotchEntity, LineEntity
	 *
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 * 
	 */
	class AxisEntity : public wEngine::Entity
	{
		public:
			/**
			 * @brief Constructs an AxisEntity with a given orientation, origin, scale, and range.
			 * @param font		Reference to a font used for the title and labels.
			 * @param origin	Pixel position of the logical origin (typically from GraphicsEntity).
			 * @param scale		Scaling factor (pixels per logical unit).
			 * @param offset	Logical displacement of the axis system.
			 * @param type		Axis type (`X_AXIS` or `Y_AXIS`).
			 * @param axisRange	Logical range covered by the axis (e.g., [-5, 5]).
			 */
			AxisEntity( sf::Font& font, sf::Vector2f origin, sf::Vector2f scale, sf::Vector2f offset, AxisType type, sf::Vector2f axisRange );

			/**
			 * @brief Virtual destructor.
			 */
			virtual ~AxisEntity( ) = default;

			/**
			 * @brief Sets the color of the axis line.
			 * @param color New axis color.
			 * @throws std::runtime_error if ColorComponent is missing.
			 */
			void setColor( sf::Color color );

			/**
			 * @brief Sets the thickness of the axis line (in pixels).
			 * @param thickness New thickness (must be > 0).
			 * @throws std::invalid_argument if thickness <= 0.
			 * @throws std::runtime_error if ThicknessComponent is missing.
			 */
			void setThickness( float thickness );

			/**
			 * @brief Sets the size of the arrowhead at the end of the axis.
			 * @param arrowSize Arrowhead size in pixels.
			 */
			void setArrowSize( float arrowSize );

			/**
			 * @brief Adds a title to the axis.
			 * @param title Title string (narrow string).
			 */
			void addTitle( const std::string& title );

			/**
			 * @brief Adds a title to the axis.
			 * @param title Title string (wide string).
			 */
			void addTitle( const std::wstring& title );

			/**
			 * @brief Sets the font of the axis title.
			 * @param font Reference to an SFML font.
			 */
			void setTitleFont( const sf::Font& font );

			/**
			 * @brief Sets the character size of the axis title.
			 * @param size Character size in pixels.
			 */
			void setTitleCharacterSize( unsigned int size );

			/**
			 * @brief Sets the color of the axis title.
			 * @param newColor New text color.
			 */
			void setTitleColor( sf::Color newColor );

			/**
			 * @brief Sets a manual offset for the title position.
			 * @param titleOffset Pixel offset applied to the title position.
			 */
			void setTitleOffset( sf::Vector2f titleOffset );

			/**
			 * @brief Gets the current title offset.
			 * @return Offset vector in pixels.
			 */
			sf::Vector2f getTitleOffset( ) const;

			/**
			 * @brief Adds notches along the axis.
			 * @param interval Logical spacing between notches (> 0).
			 * @param position Placement relative to axis (Center, Above, Below).
			 * @param hasLabels If true, labels are displayed for each notch.
			 */
			void addNotches( float interval, NotchPosition position, bool hasLabels = false );

			/**
			 * @brief Sets the color of all notches.
			 * @param color New notch color.
			 */
			void setNotchesColor( const sf::Color& color );

			/**
			 * @brief Sets the thickness of all notches.
			 * @param thickness New thickness in pixels.
			 */
			void setNotchesThickness( float thickness );

			/**
			 * @brief Sets the length of all notches.
			 * @param newLength New length in pixels.
			 */
			void setNotchesLength( float newLength );

			/**
			 * @brief Sets the font of all labels.
			 * @param font Reference to an SFML font.
			 */
			void setLabelsFont( const sf::Font& font );

			/**
			 * @brief Sets the color of all labels.
			 * @param color New text color.
			 */
			void setLabelsColor( const sf::Color& color );

			/**
			 * @brief Gets the current offset of all labels.
			 * @return Vector of offsets (one per label).
			 */
			std::vector< sf::Vector2f > getLabelsOffset( ) const;

			/**
			 * @brief Sets a new offset for all labels.
			 * @param offset Offset vector in pixels.
			 */
			void setLabelsOffset( sf::Vector2f offset );

			/**
			 * @brief Applies an additional offset to all labels.
			 * @param delta Delta offset in pixels.
			 */
			void addLabelsOffset( sf::Vector2f delta );

			/**
			 * @brief Sets the character size of all labels.
			 * @param newSize Character size in pixels.
			 */
			void setLabelsCharacterSize( unsigned int newSize );

			/**
			 * @brief Sets the number of decimal places for numeric labels.
			 * @param places Digits after decimal point (>= 0).
			 */
			void setLabelsDecimalPlaces( int places );

			/**
			 * @brief Replaces numeric labels with a custom set of strings.
			 * @param labels Vector of user-defined label strings.
			 */
			void setCustomLabels( const std::vector< std::string >& labels );

			/**
			 * @brief Renders the axis (line, arrow, title, notches, labels).
			 * @param window Target render window.
			 */
			void render( sf::RenderWindow& window );
		private:
			sf::Font& mTitleFont;
			sf::Font& mLabelsFont;
			AxisType mAxisType;
			sf::Vector2f mAxisRange;
			std::unique_ptr< LineEntity > mAxisLine;
			float mArrowSize;

			std::vector< std::unique_ptr< NotchEntity > > mNotches;
			NotchPosition mNotchPosition;

			std::unique_ptr< TitleEntity > mTitle;

			bool mHasLabels;
			std::vector< std::unique_ptr< LabelEntity > > mLabels;

			/**
			 * @brief Internal: rebuilds the axis geometry.
			 */
			void construct( );

			/**
			 * @brief Internal: initializes a title with generic string type.
			 */
			template < typename T >
			void initTitle( const T& title );

			/**
			 * @brief Internal: generates and positions notches and labels.
			 */
			void initNotches( );
	};

}//End of namespace wPlot2D

#endif