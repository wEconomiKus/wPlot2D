#ifndef W_PADDING_COMPONENT_HPP
#define W_PADDING_COMPONENT_HPP

#include "../srcEntity/wComponent.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wswitch-default"
#include <SFML/Graphics.hpp>
#pragma GCC diagnostic pop

namespace wEngine
{

	/**
	 * @class PaddingComponent
	 * @brief ECS component representing internal padding for UI-like elements.
	 *
	 * This component encapsulates a 2D padding vector (horizontal and vertical)
	 * that can be used to add internal spacing between a visual element (e.g., a
	 * title or a frame) and its boundary.
	 *
	 * ### Padding Convention:
	 * - `x` corresponds to horizontal padding (left and right),
	 * - `y` corresponds to vertical padding (top and bottom).
	 *
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 * 
	 */
	class PaddingComponent : public Component
	{
		public:
			/**
			 * @brief Constructs a PaddingComponent with optional initial padding.
			 * @param padding Padding vector (x, y) (default is ( 0.0f, 0.0f )).
			 */
			PaddingComponent( sf::Vector2f padding = sf::Vector2f( 0.0f, 0.0f ) );

			/*
			 * @brief Virtual destructor.
			 */
			virtual ~PaddingComponent( ) = default;

			/**
			 * @brief Sets the padding vector.
			 * @param padding New padding values (x, y).
			 */
			void setPadding( sf::Vector2f padding );

			/**
			 * @brief Returns the current padding values.
			 * @return Padding vector (x, y).
			 */
			[[nodiscard]] sf::Vector2f getPadding( ) const;

			/**
			 * @brief Prints the current padding values to standard output for debugging.
			 */
			void debugPrint( ) const;
		private:
			sf::Vector2f mPadding;

			/**
			 * @brief Ensures that a padding vector has non-negative components.
			 * @param value The vector to validate.
			 * @throw std::invalid_argument if value.x or value.y is negative.
			 */
			void validatePositive( const sf::Vector2f& value ) const;
	};

}//End of namespace wEngine

#endif