/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_NOTCH_INTERVAL_COMPONENT_HPP
#define W_NOTCH_INTERVAL_COMPONENT_HPP

#include "../srcEntity/wComponent.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wswitch-default"
#include <SFML/Graphics.hpp>
#pragma GCC diagnostic pop

namespace wEngine
{

	/**
	 * @class NotchIntervalComponent
	 * @brief ECS component that defines the interval between notches on an axis.
	 *
	 * This component stores the spacing (in logical units) between visual ticks or markers
	 * on an axis, such as those used in coordinate grids or charts.
	 * 
	 * It enables the placement of regular visual markers and may be queried by rendering systems.
	 * 
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 * 
	 */
	class NotchIntervalComponent : public Component
	{
		public:
			/**
			 * @brief Constructs a NotchIntervalComponent with a given interval.
			 * @param interval Distance between notches in logical units (must be > 0). Default is 1.0f.
			 * @throws std::invalid_argument if interval is not strictly positive.
			 */
			NotchIntervalComponent( float interval = 1.0f );

			/*
			 * @brief Virtual destructor.
			 */
			virtual ~NotchIntervalComponent( ) = default;

			/**
			 * @brief Returns the current spacing between notches.
			 * @return The interval, expressed in logical units.
			 */
			[[nodiscard]] float getInterval( ) const;

			/**
			 * @brief Sets a new interval between notches.
			 * @param newInterval New spacing value (must be > 0).
			 * @throws std::invalid_argument if newInterval is not strictly positive.
			 */
			void setInterval( float newInterval );

			/**
			 * @brief Outputs the current interval to standard output for debugging.
			 */
			void debugPrint( ) const;

		private:
			float mInterval;

			/**
			 * @brief Checks that the interval value is strictly positive.
			 * @param value Interval to validate.
			 * @throws std::invalid_argument if value is less than or equal to zero.
			 */
			void validateInterval( float value ) const;
	};

}// End of namespace wEngine

#endif