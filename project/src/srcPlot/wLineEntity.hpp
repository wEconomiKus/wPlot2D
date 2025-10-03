/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_LINE_ENTITY_HPP
#define W_LINE_ENTITY_HPP

#include "../srcEntity/wEntity.hpp"
#include "../srcComponents/wLineStyleComponent.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wswitch-default"
#include <SFML/Graphics.hpp>
#pragma GCC diagnostic pop

namespace wPlot2D
{

	/**
	 * @class LineEntity
	 * @brief Entity representing a straight line segment with optional arrowhead.
	 *
	 * This entity provides configurable line rendering within the plot area:
	 * - Supports Solid, Dashed, and Dotted styles (via LineStyleComponent).
	 * - Customizable color, thickness, dash length, and gap length.
	 * - Optional arrowhead at the end (useful for axes or vectors).
	 *
	 * Coordinates are expressed in logical units and transformed by
	 * the entity’s origin and scale before being rendered.
	 *
	 * @see wEngine::LineDrawer for the rendering implementation
	 * @see wEngine::LineStyleComponent for style configuration
	 *
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 * 
	 */
	class LineEntity : public wEngine::Entity
	{
		public:
			/**
			 * @brief Construct a line entity between two points.
			 *
			 * @param origin	Origin of the plot (reference point).
			 * @param scale		Scaling factor to convert logical coordinates into pixels.
			 * @param start		Line starting point (logical coordinates).
			 * @param end		Line ending point (logical coordinates).
			 * @param withArrow	Whether to draw an arrowhead at the end.
			 */
			LineEntity( const sf::Vector2f& origin, const sf::Vector2f& scale, const sf::Vector2f& start, const sf::Vector2f& end,
				bool withArrow = false );

			/**
			 * @brief Virtual destructor.
			 */
			virtual ~LineEntity( ) = default;

			/**
			 * @brief Sets the color of the line and arrowhead.
			 * @param color New color to apply.
			 */
			void setColor( sf::Color color );

			/**
			 * @brief Sets the thickness of the line.
			 * @param thickness Thickness in pixels.
			 */
			void setThickness( float thickness );

			/**
			 * @brief Returns the current thickness of the line.
			 * @return Thickness in pixels.
			 */
			[[nodiscard]] float getThickness( ) const;

			/**
			 * @brief Sets the visual style of the line.
			 * @param style Solid, Dashed, or Dotted.
			 */
			void setLineStyle( wEngine::LineStyleComponent::LineStyle style );

			/**
			 * @brief Sets the dash length for dashed lines.
			 * @param dashLength Length of each dash in pixels.
			 */
			void setDashLength( float dashLength );

			/**
			 * @brief Sets the gap length between dashes or dots.
			 * @param gapLength Length of the gap in pixels.
			 */
			void setGapLength( float gapLength );

			/**
			 * @brief Returns the starting point of the line.
			 * @return Start point in logical coordinates.
			 */
			[[nodiscard]] sf::Vector2f getStartPoint( ) const;

			/**
			 * @brief Returns the ending point of the line.
			 * @return End point in logical coordinates.
			 */
			[[nodiscard]] sf::Vector2f getEndPoint( ) const;

			/**
			 * @brief Checks if the line has an arrowhead.
			 * @return True if an arrowhead is drawn, false otherwise.
			 */
			[[nodiscard]] bool hasArrow( ) const;

			/**
			 * @brief Returns the arrowhead size factor.
			 * @return Arrow size relative to line thickness.
			 */
			[[nodiscard]] float getArrowSize( ) const;

			/**
			 * @brief Sets the arrowhead size factor.
			 * @param arrowSize Arrow size relative to line thickness.
			 */
			void setArrowSize( float arrowSize );

			/**
			 * @brief Renders the line (and optional arrowhead).
			 * @param window Target render window.
			 */
			void render( sf::RenderWindow& window );

		private:
			sf::Vector2f mStart;
			sf::Vector2f mEnd;
			bool mWithArrow;
			sf::ConvexShape mArrowHead;
			float mArrowSize;

			/**
			 * @brief Initializes the arrowhead geometry at the end of the line.
			 *
			 * The arrowhead is a filled triangle oriented along the line direction.
			 * Its size scales with both line thickness and the user-defined arrowSize factor.
			 *
			 * @param lineEnd	Line end point (in pixel coordinates).
			 * @param dir		Normalized line direction vector.
			 * @param arrowSize	Arrowhead length in pixels.
			 * @param color		Arrowhead fill color.
			 */
			void initArrowHead( const sf::Vector2f& lineEnd, const sf::Vector2f& dir, float arrowSize, sf::Color color );
	};

}//End of namespace wPlot2D

#endif