/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_FONT_COMPONENT_HPP
#define W_FONT_COMPONENT_HPP

#include "../srcEntity/wComponent.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wswitch-default"
#include <SFML/Graphics.hpp>
#pragma GCC diagnostic pop

namespace wEngine
{

	/**
	 * @class FontComponent
	 * @brief Holds a reference to an SFML font for rendering text.
	 *
	 * This component allows entities to store and access an `sf::Font` reference
	 * without needing to pass the AssetManager explicitly.
	 *
	 * @note The font must outlive the entity that uses it.
	 *
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 * 
	 */
	class FontComponent : public Component
	{
		public:
			/**
			 * @brief Constructs the FontComponent with a reference to the font.
			 * @param font Reference to an externally managed sf::Font.
			 */
			explicit FontComponent( const sf::Font& font );

			/**
			 * @brief Virtual destructor.
			 */
			~FontComponent( ) override = default;

			/**
			 * @brief Returns the stored font reference.
			 * @return A constant reference to the sf::Font.
			 */
			const sf::Font& getFont( ) const;

			/**
			 * @brief Updates the stored font reference.
			 * @param font Reference to an externally managed sf::Font.
			 * @note The font must outlive this component.
			 */
			void setFont( const sf::Font& font );

			/**
			 * @brief Prints debug information about the stored font.
			 */
			void debugPrint( ) const;

		private:
			const sf::Font* mFont;
	};

}//End of namespace wEngine

#endif