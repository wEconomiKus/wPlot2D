/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_LABEL_ENTITY_HPP
#define W_LABEL_ENTITY_HPP

#include "../srcEntity/wEntity.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wswitch-default"
#include <SFML/Graphics.hpp>
#pragma GCC diagnostic pop

namespace wPlot2D
{

	enum class AxisType;

	/**
	 * @class LabelEntity
	 * @brief Represents a textual label or a collection of axis labels.
	 *
	 * A LabelEntity manages the rendering of formatted text associated with axis notches.
	 * Labels can be generated dynamically (from numeric values, with controlled precision)
	 * or defined manually via custom strings.
	 *
	 * The class relies on SFML's `sf::Text` for rendering and provides customization
	 * of style (font, color, character size) and placement (axis orientation, offset relative to the axis).
	 *
	 * @note Typically, a LabelEntity is aggregated inside an `AxisEntity` to display labels alongside axis notches.
	 *
	 * @see AxisEntity
	 *
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 * 
	 */
	class LabelEntity : public wEngine::Entity
	{
		public:
			/**
			 * @brief Constructs a LabelEntity with a given font, axis orientation and initial position.
			 * @param font Reference to an SFML font (must remain valid during the lifetime of the entity).
			 * @param type Axis orientation (`AxisType::X_AXIS` or `AxisType::Y_AXIS`).
			 * @param initialPosition Position where the label will be anchored.
			 */
			LabelEntity( const sf::Font& font, AxisType type, sf::Vector2f initialPosition );

			/**
			 * @brief Virtual destructor.
			 */
			virtual ~LabelEntity( ) = default;

			/**
			 * @brief Returns the numeric value associated with the label.
			 * @return The value stored in the label.
			 */
			[[nodiscard]] float getValue( ) const;

			/**
			 * @brief Returns the current character size of the label text.
			 * @return Character size in pixels.
			 */
			[[nodiscard]] unsigned int getCharacterSize( ) const;

			/**
			 * @brief Returns the number of decimal places currently used for numeric formatting.
			 * @return Number of digits after the decimal point.
			 */
			[[nodiscard]] int getDecimalPlaces( ) const;

			/**
			 * @brief Sets a new font for the label.
			 * @param font Reference to an SFML font (must remain valid during the lifetime of the entity).
			 */
			void setFont( const sf::Font& font );

			/**
			 * @brief Defines the text content of the label.
			 *
			 * If custom labels are enabled, this method updates the string that will be rendered.
			 * Otherwise, it is generally managed internally via numeric formatting.
			 *
			 * @param text The new string to assign to the label.
			 */
			void setLabelText( std::string text );

			/**
			 * @brief Sets a new character size for the labels.
			 * @param newSize Character size in pixels.
			 */
			void setCharacterSize( unsigned int newSize );

			/**
			 * @brief Sets the number of decimal places for numeric labels.
			 * @param places Digits after the decimal point (must be >= 0).
			 */
			void setDecimalPlaces( int places );

			/**
			 * @brief Sets a custom label string.
			 *
			 * This enables "custom label mode". When active, numeric formatting is ignored
			 * and the provided string is displayed instead.
			 *
			 * @param labels Custom string to display as a label.
			 */
			void setCustomLabels( const std::string& labels );

			/**
			 * @brief Indicates whether the entity is currently using custom labels.
			 * @return True if custom labels are active, false if numeric formatting is used.
			 */
			[[nodiscard]] bool usesCustomLabels( ) const;

			/**
			 * @brief Formats a numeric value into a label string.
			 *
			 * If custom labels are active, the stored custom string is returned.
			 * Otherwise, the numeric value is converted using the current number of decimal places.
			 *
			 * @param value Numeric value to format.
			 * @return A string ready to be displayed as a label.
			 */
			std::string formatLabel( float value );

			/**
			 * @brief Renders the label on the given SFML window.
			 * @param window Reference to the render window.
			 */
			void render( sf::RenderWindow& window );
		private:
			AxisType mAlignment;
			unsigned int mCharacterSize;
			float mValue;
			int mDecimalPlaces;
			sf::Vector2f mOffset;

			std::string mCustomLabels;
			bool mUseCustomLabels;

			sf::Text mLabel;
	};

} // namespace wPlot2D

#endif