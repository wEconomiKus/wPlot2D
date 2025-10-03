/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_THICKNESS_COMPONENT_HPP
#define W_THICKNESS_COMPONENT_HPP

#include "../srcEntity/wComponent.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wswitch-default"
#include <SFML/Graphics.hpp>
#pragma GCC diagnostic pop

namespace wEngine
{

	/**
	 * @class ThicknessComponent
	 * @brief ECS component that defines the thickness of a drawable object.
	 *
	 * This component stores a positive float value representing the thickness (in pixels)
	 * of lines or shapes (e.g., axes, borders). The value must be strictly positive.
	 *
	 * Examples:
	 * - A thickness of 1.0f draws a thin line.
	 * - A thickness of 4.0f produces a bold axis.
	 *
	 * @throws std::invalid_argument if the value is zero or negative.
	 * 
	 * ### Usage Examples:
	 * - A thickness of 1.0f draws a thin line.
	 * - A thickness of 4.0f produces a bold axis.
	 * 
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 * 
	 */
	class ThicknessComponent : public Component
	{
		public:
			/**
			 * @brief Constructs the component with an initial positive thickness.
			 * @param thickness Initial thickness value (default is 2.0f).
			 * @throws std::invalid_argument if the value is zero or negative.
			 */
			ThicknessComponent( float thickness = 2.0f );

			/*
			 * @brief Virtual destructor.
			 */
			virtual ~ThicknessComponent( ) = default;

			/**
			 * @brief Returns the current thickness.
			 * @return A positive float representing the line thickness (in pixels).
			 */
			[[nodiscard]] float getThickness( ) const;

			/**
			 * @brief Sets a new thickness value.
			 * @param newThickness A strictly positive float.
			 * @throws std::invalid_argument if the value is zero or negative.
			 */
			void setThickness( float newThickness );

			/**
			 * @brief Outputs the current thickness value to the console for debugging.
			 */
			void debugPrint( ) const;
		private:
			float mThickness;

			/*
			 * @brief Validates that the thickness value is strictly positive.
			 * @param value The thickness value to validate.
			 * @throws std::invalid_argument if value <= 0.
			 */
			void validatePositive( float value ) const;
	};

}//End of namespace wEngine

#endif