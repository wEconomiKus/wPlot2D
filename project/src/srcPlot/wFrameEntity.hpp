/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_FRAME_ENTITY_HPP
#define W_FRAME_ENTITY_HPP

#include "../srcEntity/wEntity.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wswitch-default"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#pragma GCC diagnostic pop

namespace wPlot2D
{


	/**
	 * @class FrameEntity
	 * @brief Entity representing a rectangular frame around content.
	 *
	 * A FrameEntity is typically used to visually surround titles, legends, or
	 * other graphical content. It supports:
	 * - Toggle visibility (`enabled` flag),
	 * - Fill and outline colors,
	 * - Outline thickness,
	 * - Padding around the content.
	 *
	 * The size of the frame is dynamically updated from the content bounds
	 * (see `update( )`).
	 *
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 * 
	 */
	class FrameEntity : public wEngine::Entity
	{
		public:
			/**
			 * @brief Constructs a frame entity.
			 * @param enabled Whether the frame should be enabled initially.
			 */
			FrameEntity( bool enabled = true );

			/**
			 * @brief Virtual destructor.
			 */
			virtual ~FrameEntity( ) = default;

			/**
			 * @brief Enables or disables the frame.
			 * @param enabled New enabled state.
			 */
			void setEnabled( bool enabled );

			/**
			 * @brief Checks whether the frame is currently enabled.
			 * @return True if the frame is enabled, false otherwise.
			 */
			[[nodiscard]] bool isEnabled( ) const;

			/**
			 * @brief Gets the current fill color of the frame.
			 * @return Fill color.
			 */
			[[nodiscard]] sf::Color getFillColor( ) const;

			/**
			 * @brief Gets the current outline color of the frame.
			 * @return Outline color.
			 */
			[[nodiscard]] sf::Color getOutlineColor( ) const;

			/**
			 * @brief Gets the current outline thickness of the frame.
			 * @return Outline thickness (in pixels).
			 */
			[[nodiscard]] float getThickness( ) const;

			/**
			 * @brief Gets the current padding applied around the content.
			 * @return Padding as (x, y).
			 */
			[[nodiscard]] sf::Vector2f getPadding( ) const;

			/**
			 * @brief Sets the fill color of the frame.
			 * @param color New fill color.
			 */
			void setFillColor( const sf::Color& color );

			/**
			 * @brief Sets the outline color of the frame.
			 * @param color New outline color.
			 */
			void setOutlineColor( const sf::Color& color );

			/**
			 * @brief Sets the outline thickness of the frame.
			 * @param thickness New outline thickness (must be > 0).
			 */
			void setThickness( float thickness );

			/**
			 * @brief Sets the padding around the content.
			 * @param padding Padding as (x, y).
			 */
			void setPadding( const sf::Vector2f& padding );

			/**
			 * @brief Updates the size and position of the frame based on content bounds.
			 * @param contentBounds The bounding box of the content (width/height).
			 * @param position The position of the frame's center in pixels.
			 */
			void update( const sf::FloatRect& contentBounds, const sf::Vector2f& position );

			/**
			 * @brief Renders the frame to the given render window.
			 * @param window Target render window.
			 */
			void render( sf::RenderWindow& window );
		private:
			bool mEnabled;
			sf::RectangleShape mFrame;
	};

}//End of namespace wPlot2D

#endif