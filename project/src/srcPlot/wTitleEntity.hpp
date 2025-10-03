/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_TITLE_ENTITY_HPP
#define W_TITLE_ENTITY_HPP

#include "../srcEntity/wEntity.hpp"
#include "../srcUtils/wPathUtils.hpp"
#include "wFrameEntity.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wswitch-default"
#include <SFML/Graphics.hpp>
#pragma GCC diagnostic pop

namespace wPlot2D
{

	/**
	 * @class TitleEntity
	 * @brief Represents a textual label (typically an axis title or main plot title) in a 2D plot.
	 *
	 * A `TitleEntity` displays text using SFML's `sf::Text`, styled and positioned
	 * using ECS components (`PositionComponent`, `OffsetComponent`, `ColorComponent`, `FontComponent`).
	 * Optionally, it can display a surrounding rectangular frame (`FrameEntity`) with customizable
	 * outline, fill color, thickness, and padding.
	 *
	 * ### Notes:
	 * - The font passed to the constructor must remain valid during the lifetime of the entity
	 *   (SFML does not copy font data).
	 * - The frame is disabled by default unless explicitly enabled at construction or later.
	 *
	 * @see FrameEntity, AxisEntity, GraphicsEntity
	 *
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 * 
	 */
	class TitleEntity : public wEngine::Entity
	{
		public:
			/**
			 * @brief Constructs a title entity with specified font and text (UTF-8).
			 * @param font Reference to an externally managed font (must remain valid).
			 * @param title The string to display.
			 * @param hasFrame Whether a surrounding frame should be displayed.
			 */
			TitleEntity( const sf::Font& font, const std::string& title, bool hasFrame = false );

			/**
			 * @brief Constructs a title entity with specified font and wide string (UTF-16/32).
			 * @param font Reference to an externally managed font (must remain valid).
			 * @param title The wide string to display.
			 * @param hasFrame Whether a surrounding frame should be displayed.
			 */
			TitleEntity( const sf::Font& font, const std::wstring& title, bool hasFrame = false );

			/**
			 * @brief Virtual destructor.
			 */
			virtual ~TitleEntity( ) = default;

			/**
			 * @brief Returns the current character size.
			 * @return Character size (font size in pixels).
			 */
			[[nodiscard]] unsigned int getCharacterSize(  ) const;

			/**
			 * @brief Returns the local bounding box of the title text.
			 * @return A FloatRect representing the size and local origin of the text.
			 */
			[[nodiscard]] sf::FloatRect getTextSize( ) const;

			/**
			 * @brief Sets the text color.
			 * @param textColor New SFML color.
			 */
			void setTextColor( sf::Color textColor );

			/**
			 * @brief Sets the offset relative to the base anchor position.
			 * @param offset Displacement vector in pixels.
			 */
			void setOffset( sf::Vector2f offset );

			/**
			 * @brief Sets the font size (character size) of the title.
			 * @param size Size in pixels.
			 */
			void setCharacterSize( unsigned int size );

			/**
			 * @brief Sets the font reference for the title.
			 * @param font Reference to an externally managed font (must remain valid).
			 * @note The font must outlive this entity, otherwise rendering will be invalid.
			 */
			void setFont( const sf::Font& font );

			/**
			 * @brief Returns the current outline color of the frame.
			 * @return SFML color.
			 */
			[[nodiscard]] sf::Color getFrameOutlineColor( ) const;

			/**
			 * @brief Returns the current fill color of the frame.
			 * @return SFML color.
			 */
			[[nodiscard]] sf::Color getFrameFillColor( ) const;

			/**
			 * @brief Returns the frame's outline thickness.
			 * @return Thickness in pixels.
			 */
			[[nodiscard]] float getFrameThickness( ) const;

			/**
			 * @brief Returns the internal padding of the frame.
			 * @return Padding vector `{ x, y }` in pixels.
			 */
			[[nodiscard]] sf::Vector2f getPadding( ) const;

			/**
			 * @brief Returns whether the title has a visible frame.
			 * @return True if frame is enabled.
			 */
			[[nodiscard]] bool isFrameEnabled( ) const;

			/**
			 * @brief Enables or disables the visual frame.
			 * @param enabled True to show the frame, false to hide it.
			 */
			void setFrameEnabled( bool enabled );

			/**
			 * @brief Sets the frame's outline color.
			 * @param color SFML color.
			 */
			void setFrameOutlineColor( const sf::Color& color );

			/**
			 * @brief Sets the fill color of the frame.
			 * @param color SFML color.
			 */
			void setFrameFillColor( const sf::Color& color );

			/**
			 * @brief Sets the thickness of the frame's outline.
			 * @param thickness Outline thickness in pixels.
			 */
			void setFrameThickness( float thickness );

			/**
			 * @brief Sets the internal padding of the frame (horizontal and vertical).
			 *
			 * This creates a margin between the text and the frame borders.
			 * Expressed as (horizontal, vertical) padding in pixels.
			 *
			 * @param padding Vector of type (left/right, top/bottom) padding.
			 */
			void setPadding( sf::Vector2f padding );

			/**
			 * @brief Renders the title and its frame (if enabled) to the window.
			 *
			 * The title position is computed from:
			 * - `PositionComponent` (anchor point),
			 * - `OffsetComponent` (displacement),
			 * - the text's local bounds (centered origin).
			 *
			 * If the frame is enabled, it is rendered behind the text, centered
			 * with the same anchor point and adjusted using the specified padding.
			 *
			 * @param window The target SFML render window.
			 */
			void render( sf::RenderWindow& window );

		private:
			sf::Text mTitleText;
			FrameEntity mFrame;

			/**
			 * @brief Internal helper to initialize the title string and default components.
			 * @tparam T Type of the string (std::string or std::wstring).
			 * @param title The string to display.
			 */
			template < typename T >
			void init( const T& title );
	};

} // namespace wPlot2D

#endif