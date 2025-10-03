/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_SCALE_COMPONENT_HPP
#define W_SCALE_COMPONENT_HPP

#include "../srcEntity/wComponent.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wswitch-default"
#include <SFML/Graphics.hpp>
#pragma GCC diagnostic pop

namespace wEngine
{

	/**
	 * @class ScaleComponent
	 * @brief ECS component that defines the scaling factor for an entity in 2D space.
	 *
	 * The scale determines how much the entity is scaled along the X and Y axes.
	 * It is typically used to transform logical coordinates into pixel coordinates.
	 * 
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 * 
	 */
	class ScaleComponent : public Component
	{
		public:
			/**
			 * @brief Constructs a ScaleComponent with the given scale.
			 * @param scale Initial scale vector (must be strictly positive, defaults is ( 1.0f, 1.0f ).
			 * @throw std::invalid_argument if any scale component is non-positive.
			 */
			ScaleComponent( sf::Vector2f scale = { 1.0f, 1.0f } );

			/*
			 * @brief Virtual destructor.
			 */
			virtual ~ScaleComponent( ) = default;

			/**
			 * @brief Retrieves the current scale factor.
			 * @return The scale as an sf::Vector2f (X and Y scale).
			 */
			[[nodiscard]] sf::Vector2f getScale( ) const;

			/**
			 * @brief Sets a new scale factor.
			 * @param newScale New scale vector (must be strictly positive).
			 * @throw std::invalid_argument if newScale has non-positive values.
			 */
			void setScale( sf::Vector2f newScale );

			/**
			 * @brief Outputs the scale to standard output for debugging.
			 */
			void debugPrint( ) const;
		private:
			sf::Vector2f mScale;

			/**
			 * @brief Ensures that a scale vector has strictly positive components.
			 * @param value The vector to validate.
			 * @throw std::invalid_argument if value.x or value.y is non-positive.
			 */
			void validatePositive( const sf::Vector2f& value ) const;
	};

}//End of namespace wEngine

#endif