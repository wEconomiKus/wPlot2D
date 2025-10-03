/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_COLOR_COMPONENT_HPP
#define W_COLOR_COMPONENT_HPP

#include "../srcEntity/wComponent.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wswitch-default"
#include <SFML/Graphics.hpp>
#pragma GCC diagnostic pop

namespace wEngine
{

	/**
	 * @class ColorComponent
	 * @brief ECS component that holds a color value.
	 *
	 * This component stores an RGBA color (from SFML) associated with an entity.
	 * It can be used to define the rendering color of graphical elements.
	 * 
	 * ### Usage Examples:
	 * - With predefined SFML colors:
	 *	@code
	 *		addComponent< wEngine::ColorComponent >( sf::Color::Red );
	 *	@endcode
	 * 
	 * - With a custom RGBA color:
	 *	@code
	 *   sf::Color customColor(128, 64, 200, 255); // R, G, B, A
	 *		addComponent< wEngine::ColorComponent >( customColor );
	 *	@endcode
	 *
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 * 
	 */
	class ColorComponent : public Component
	{
		public:
			/**
			 * @brief Constructor with optional color.
			 * @param color The initial color (default is sf::Color::Black).
			 */
			ColorComponent( sf::Color color = sf::Color::Black );

			/*
			 * @brief Virtual destructor.
			 */
			virtual ~ColorComponent( ) = default;

			/**
			 * @brief Gets the current color.
			 * @return The color stored in the component.
			 */
			[[nodiscard]] sf::Color getColor( ) const;

			/**
			 * @brief Sets a new color.
			 * @param newColor The new color to assign.
			 */
			void setColor( sf::Color newColor );

			/**
			 * @brief Outputs the RGBA values of the color to standard output.
			 */
			void debugPrint( ) const;
		private:
			sf::Color mColor;
	};

}//End of namespace wEngine

#endif