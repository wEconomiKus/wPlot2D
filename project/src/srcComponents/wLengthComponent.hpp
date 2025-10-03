/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_LENGTH_COMPONENT_HPP
#define W_LENGTH_COMPONENT_HPP

#include "../srcEntity/wComponent.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wswitch-default"
#include <SFML/Graphics.hpp>
#pragma GCC diagnostic pop

namespace wEngine
{

	/**
	 * @class LengthComponent
	 * @brief ECS component that defines the length of a drawable object.
	 *
	 * This component stores a positive float value representing the length (in pixels)
	 * of lines or shapes. The value must be strictly positive.
	 *
	 * @throws std::invalid_argument if the value is zero or negative.
	 * 
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 * 
	 */
	class LengthComponent : public Component
	{
		public:
			/**
			 * @brief Constructs the component with an initial positive length.
			 * @param length Initial length value (default is 2.0f).
			 * @throws std::invalid_argument if the value is zero or negative.
			 */
			LengthComponent( float length = 2.0f );

			/*
			 * @brief Virtual destructor.
			 */
			virtual ~LengthComponent( ) = default;

			/**
			 * @brief Returns the current length.
			 * @return A positive float representing the line length (in pixels).
			 */
			[[nodiscard]] float getLength( ) const;

			/**
			 * @brief Sets a new length value.
			 * @param newLength A strictly positive float.
			 * @throws std::invalid_argument if the value is zero or negative.
			 */
			void setLength( float newLength );

			/**
			 * @brief Outputs the current length value to the console for debugging.
			 */
			void debugPrint( ) const;
		private:
			float mLength;

			/**
			 * @brief Validates that the length value is strictly positive.
			 * @param value The length value to validate.
			 * @throw std::invalid_argument if `value` is less than or equal to zero.
			 */
			void validatePositive( float value ) const;
	};

}//End of namespace wEngine

#endif