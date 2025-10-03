/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_LINE_DRAWER_HPP
#define W_LINE_DRAWER_HPP

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wswitch-default"
#include <SFML/Graphics.hpp>
#pragma GCC diagnostic pop

#include "../srcComponents/wLineStyleComponent.hpp"

namespace wEngine
{

	/**
	 * @class LineDrawer
	 * @brief Utility class for rendering thick lines and polylines with style support.
	 *
	 * The LineDrawer provides static methods to draw line segments and polylines
	 * with configurable thickness, color, and style (Solid, Dashed, Dotted).
	 *
	 * ### Features:
	 * - Thick line rendering via quads (two triangles per segment).
	 * - Support for dashed and dotted patterns using configurable dash/gap lengths.
	 * - Dash/dot continuity across multiple connected segments using a shared pattern offset.
	 * - Optional round joins at corners of polylines (applied only when style == Solid).
	 *
	 * ### Usage:
	 * - Use drawLine( ) to render a single thick segment.
	 * - Use drawPolylineRound( ) to render a sequence of connected points with optional round joins.
	 * - To maintain consistent dash/dot alignment across segments, pass the returned
	 *   @p patternOffset from drawLine( ) into the next segment.
	 *
	 *
	 * @warning Round joins are currently only applied for `Solid` style. For dashed or dotted
	 *          lines, joins would produce inconsistent results and are therefore omitted.
	 *
	 * @see LineStyleComponent for configuring line style options.
	 *
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 * 
	 */
	class LineDrawer
	{
		public:

			/**
			 * @brief Draws a single thick line segment between two points.
			 *
			 * ### Style behavior:
			 * - **Solid**: Renders a single quad covering the full segment.
			 * - **Dashed**: Repeats a dash/gap pattern along the segment.
			 * - **Dotted**: Places successive dots along the segment, using thickness as dot length.
			 *
			 * ### Pattern control:
			 * - @p dashLength sets the visible length of each dash (Dashed style).
			 * - @p gapLength sets the empty space between dashes or dots.
			 * - @p thickness is reused as the dot length if style == Dotted.
			 * - @p patternOffset maintains pattern alignment between consecutive calls.
			 *
			 * @param window		Render target.
			 * @param point1		First endpoint of the line.
			 * @param point2		Second endpoint of the line.
			 * @param color			Line color.
			 * @param thickness		Line thickness in pixels.
			 * @param style			Line style (Solid, Dashed, Dotted).
			 * @param dashLength	Dash length (used if style == Dashed).
			 * @param gapLength		Gap length between dashes or dots.
			 * @param patternOffset	Initial offset within the dash/dot pattern.
			 * 
			 * @return Updated pattern offset after this segment (pass to next segment for continuity).
			 */
			static float drawLine( sf::RenderWindow& window, const sf::Vector2f& point1, const sf::Vector2f& point2,
				const sf::Color& color, float thickness, LineStyleComponent::LineStyle style = LineStyleComponent::LineStyle::Solid,
				float dashLength = 20.0f, float gapLength = 5.0f, float patternOffset = 0.0f );

			/**
			 * @brief Draws a polyline (sequence of connected line segments) with optional round joins.
			 *
			 * - Each segment [p1, p2] is rendered using drawLine( ), with pattern continuity preserved.
			 * - If style == Solid and a next segment exists: a circular arc is approximated using triangles to smooth the corner at [p2].
			 *
			 * @param window		Render target.
			 * @param points		List of polyline points (must contain at least 2).
			 * @param color			Polyline color.
			 * @param thickness		Line thickness in pixels.
			 * @param style			Line style (Solid, Dashed, Dotted).
			 * @param dashLength	Dash length (used if style == Dashed).
			 * @param gapLength		Gap length between dashes or dots.
			 * @param arcResolution	Number of triangles used to approximate each round join (higher = smoother).
			 * 
			 * @note For Dashed or Dotted styles, round joins are skipped.
			 */
			static void drawPolylineRound( sf::RenderWindow& window, const std::vector<sf::Vector2f>& points, const sf::Color& color,
				float thickness, LineStyleComponent::LineStyle style = LineStyleComponent::LineStyle::Solid, float dashLength = 20.0f,
				float gapLength = 5.0f, unsigned int arcResolution = 12 );
	};

}//End of namespace wEngine

#endif