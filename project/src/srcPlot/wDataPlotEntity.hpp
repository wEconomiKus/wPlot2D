/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_DATA_PLOT_ENTITY_HPP
#define W_DATA_PLOT_ENTITY_HPP

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
	 * @class DataPlotEntity
	 * @brief Entity for plotting raw data points as a connected polyline.
	 *
	 * Stores a vector of raw (x,y) points and draws straight line segments between them.
	 * Each segment is rendered using the current line style (Solid, Dashed, Dotted),
	 * with configurable color, thickness, dash length, and gap length.
	 *
	 * @note Unlike FunctionEntity, this class does not evaluate a function — 
	 * it directly uses the provided data points. The points are still transformed 
	 * by the entity's origin and scale before rendering.
	 *
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 * 
	 */
	class DataPlotEntity : public wEngine::Entity
	{
		public:
			/**
			 * @brief Constructs a DataPlotEntity with given origin, scale, and raw data points.
			 *
			 * @param origin		Origin of the plot in window coordinates.
			 * @param scale			Scaling factors applied to x and y values.
			 * @param dataPoints	Vector of raw (x,y) points to plot.
			 */
			DataPlotEntity( const sf::Vector2f origin, const sf::Vector2f scale, const std::vector< sf::Vector2f >& dataPoints );

			/**
			 * @brief Virtual destructor.
			 */
			virtual ~DataPlotEntity( ) = default;

			/**
			 * @brief Get the current line color.
			 * @return The SFML color used for rendering the polyline.
			 */
			[[nodiscard]] sf::Color getColor( ) const;


			/**
			 * @brief Get the line thickness in pixels.
			 * @return Current thickness value.
			 */
			[[nodiscard]] float getThickness( );

			/**
			 * @brief Get the current line style.
			 * @return Solid, Dashed, or Dotted.
			 */
			[[nodiscard]] wEngine::LineStyleComponent::LineStyle getLineStyle( );


			/**
			 * @brief Get the dash length for dashed lines.
			 * @return Dash length in pixels.
			 */
			[[nodiscard]] float getDashLength( );

			/**
			 * @brief Get the gap length for dashed/dotted lines.
			 * @return Gap length in pixels.
			 */
			[[nodiscard]] float getGapLength( );

			/**
			 * @brief Sets the color of the plotted line.
			 * @param color New SFML color.
			 */
			void setColor( sf::Color color );

			/**
			 * @brief Sets the line thickness in pixels.
			 * @param thickness Line width.
			 */
			void setThickness( float thickness );

			/**
			 * @brief Sets the line style (Solid, Dashed, or Dotted).
			 * @param style New line style.
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
			 * @brief Draws the connected data points to the window.
			 *
			 * The data points are transformed by scale and origin, then connected
			 * with styled line segments using LineDrawer::drawLine.
			 *
			 * @param window Target SFML render window.
			 */
			void drawDataPlot( sf::RenderWindow &window );

		private:
			std::vector< sf::Vector2f > mDataPoints;
	};

}//End of namespace wPlot2D

#endif