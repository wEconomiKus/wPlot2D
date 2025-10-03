/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_OFFSET_COMPONENT_HPP
#define W_OFFSET_COMPONENT_HPP

#include "../srcEntity/wComponent.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wswitch-default"
#include <SFML/Graphics.hpp>
#pragma GCC diagnostic pop

namespace wEngine
{

	/**
	 * @class OffsetComponent
	 * @brief ECS component that defines a logical coordinate offset.
	 *
	 * This component stores a 2D offset (in logical units) applied to graphical elements
	 * such as axes, curves, titles, labels and data points. It allows changing the visual
	 * reference frame without affecting pixel-based positioning.
	 *
	 * ### Usage Examples:
	 * - With offset = ( 0, 0 ), logical coordinates are drawn as-is.
	 * - With offset = ( -20, 0 ), the visual origin is shifted 20 units to the right.
	 *
	 * The offset is often combined with the origin and scale to compute actual pixel positions.
	 *
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 * 
	 */
	class OffsetComponent : public Component
	{
		public:
			/**
			 * @brief Constructs the component with an optional offset.
			 * @param offset A 2D vector representing the logical offset (default is ( 0.0f, 0.0f )).
			 */
			OffsetComponent( sf::Vector2f offset = sf::Vector2f( 0.0f, 0.0f ) );

			/*
			 * @brief Virtual destructor.
			 */
			virtual ~OffsetComponent( ) = default;

			/**
			 * @brief Returns the current offset.
			 * @return A 2D vector representing the logical offset.
			 */
			[[nodiscard]] sf::Vector2f getOffset( ) const;

			/**
			 * @brief Updates the logical offset value.
			 * @param offset The new offset to apply.
			 */
			void setOffset( sf::Vector2f offset );

			/**
			 * @brief Increments the current offset by a given vector.
			 * @param delta The additional offset to add to the current value.
			 */
			void addOffset( sf::Vector2f delta );

			/**
			 * @brief Outputs the current offset value to the console for debugging.
			 */
			void debugPrint( ) const;
		private:
			sf::Vector2f mOffset;
	};

}//End of namespace wEngine

#endif