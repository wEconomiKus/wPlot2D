/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_FUNCTION_ENTITY_HPP
#define W_FUNCTION_ENTITY_HPP

#include "../srcEntity/wEntity.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wswitch-default"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#pragma GCC diagnostic pop

#include "../srcComponents/wLineStyleComponent.hpp"

namespace wPlot2D
{

	/**
	 * @class FunctionEntity
	 * @brief Represents a mathematical function as a drawable entity in a 2D plot.
	 *
	 * A FunctionEntity manages all components required to render a curve:
	 * - Origin and scale (mapping logical space to pixels).
	 * - Color, thickness, and line style (solid, dashed, dotted).
	 * - Offset and rotation of the curve.
	 * - Discontinuities handled by excluded intervals.
	 *
	 * The function is sampled at evenly spaced x-values and rendered as a polyline.
	 * Excluded intervals and invalid values (NaN, Inf) split the curve into separate segments.
	 *
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 * 
	 */
	class FunctionEntity : public wEngine::Entity
	{
		public:
			/**
			 * @brief Construct a new FunctionEntity.
			 * @param origin Logical origin of the coordinate system (pixels).
			 * @param scale Scale factors for x and y (pixels per unit).
			 * @param func Function of type double(double) to be plotted.
			 */
			FunctionEntity( const sf::Vector2f origin, const sf::Vector2f scale, std::function< double( double ) > func );

			/**
			 * @brief Virtual destructor.
			 */
			virtual ~FunctionEntity( ) = default;

			/**
			 * @brief Get the position (origin) of the function in pixel space.
			 * @return The current origin as an sf::Vector2f.
			 */
			[[nodiscard]] sf::Vector2f getPosition( ) const;

			/**
			 * @brief Get the color of the function curve.
			 * @return The current curve color.
			 */
			[[nodiscard]] sf::Color getColor( ) const;

			/**
			 * @brief Get the line thickness of the function curve.
			 * @return The thickness in pixels.
			 */
			[[nodiscard]] float getThickness( ) const;

			/**
			 * @brief Get the line style of the function curve.
			 * @return The current line style (Solid, Dashed, or Dotted).
			 */
			[[nodiscard]] wEngine::LineStyleComponent::LineStyle getLineStyle( ) const;

			/**
			 * @brief Get the dash length when the line style is Dashed.
			 * @return Dash length in pixels.
			 * @note This value has no effect if the style is not Dashed.
			 */
			[[nodiscard]] float getDashLength( ) const;

			/**
			 * @brief Get the gap length between dashes or dots.
			 * @return Gap length in pixels.
			 * @note This setting affects both Dashed and Dotted line styles.
			 */
			[[nodiscard]] float getGapLength( ) const;

			/**
			 * @brief Get the current offset applied to the function curve.
			 * @return A 2D vector containing the (x,y) offset in pixels.
			 */
			[[nodiscard]] sf::Vector2f getOffset( ) const;

			/**
			 * @brief Get the current rotation angle of the function curve.
			 * @return The rotation angle in degrees.
			 */
			[[nodiscard]] float getRotation( ) const;

			/**
			 * @brief Set the position (origin) of the function in pixel space.
			 * @param position The new origin as an sf::Vector2f.
			 */
			void setPosition( sf::Vector2f position );

			/**
			 * @brief Set the color of the function curve.
			 * @param color The new color as an sf::Color.
			 */
			void setColor( sf::Color color );

			/**
			 * @brief Set the line thickness of the function curve.
			 * @param thickness The new line thickness in pixels.
			 */
			void setThickness( float thickness );

			/**
			 * @brief Set the line style of the function curve.
			 * @param style The new style (Solid, Dashed, or Dotted).
			 */
			void setLineStyle( wEngine::LineStyleComponent::LineStyle style );

			/**
			 * @brief Set the length of each dash when the line style is Dashed.
			 * @param dashLength The dash length in pixels (must be > 0).
			 * @throw std::invalid_argument if dashLength <= 0.
			 * @note This setting has no effect if the line style is not Dashed.
			 */
			void setDashLength( float dashLength );

			/**
			 * @brief Set the length of the gap between dashes or dots.
			 * @param gapLength The gap length in pixels (must be >= 0).
			 * @throw std::invalid_argument if gapLength < 0.
			 * @note This setting affects both Dashed and Dotted line styles.
			 */
			void setGapLength( float gapLength );

			/**
			 * @brief Set an offset applied to the function curve.
			 *
			 * The offset is applied after scaling and rotation, allowing
			 * the curve to be shifted horizontally and vertically relative
			 * to its logical origin.
			 *
			 * @param offsetX Horizontal offset in pixels.
			 * @param offsetY Vertical offset in pixels.
			 */
			void setOffset( float offsetX, float offsetY );

			/**
			 * @brief Set the rotation angle of the function curve.
			 *
			 * The rotation is applied around the logical origin of the graph.
			 * The angle is expressed in degrees, with positive values
			 * corresponding to counter-clockwise rotation.
			 *
			 * @param angleDegrees Rotation angle in degrees.
			 */
			void setRotation( float angleDegrees );

			/**
			 * @brief Sets the scaling factors for the function graph.
			 *
			 * This method updates the ScaleComponent so the user can control
			 * how much the x and y coordinates are stretched on screen.
			 *
			 * @param scale The new scaling vector (scale.x, scale.y).
			 */
			void setScale( sf::Vector2f scale );

			/**
			 * @brief Add an excluded interval where the function should not be drawn.
			 *
			 * Useful to handle discontinuities such as vertical asymptotes.
			 *
			 * @param min Left bound of the interval.
			 * @param max Right bound of the interval.
			 */
			void addExcludedInterval( double min, double max );

			/**
			 * @brief Clear all excluded intervals.
			 */
			void clearExcludedIntervals( );

			/**
			 * @brief Rotates the function by 90 degrees and swaps scales accordingly.
			 *
			 * This is a common operation when we want to interpret the function's values along the X-axis instead of the Y-axis (or vice versa).
			 * The method:
			 *   - Sets a 90 degrees rotation.
			 *   - Swaps scale.x and scale.y to preserve unit consistency.
			 *   - Applies an optional normalized offset for alignment.
			 *
			 * @param normalizedOffsetX Relative offset along X after rotation, expressed in units of (oldScaleX / oldScaleY).
			 * @param normalizedOffsetY Relative offset along Y after rotation, expressed in units of (oldScaleY / oldScaleX).
			 */
			void alignToYAxis( float normalizedOffsetX = 0.0f, float normalizedOffsetY = 0.0f );

			/**
			 * @brief Draw the function on the target window.
			 * @param window Render target.
			 * @param startX Start of the logical x-range.
			 * @param endX End of the logical x-range.
			 * @param nbPoints Number of points to sample (default: 1000).
			 */
			void drawFunction( sf::RenderWindow &window, double startX, double endX, size_t nbPoints = 1000 );
		private:
	};

}//End of namespace wPlot2D

#endif