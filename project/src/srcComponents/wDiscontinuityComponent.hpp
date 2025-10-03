/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_DISCONTINUITY_COMPONENT_HPP
#define W_DISCONTINUITY_COMPONENT_HPP

#include "../srcEntity/wComponent.hpp"

#include <vector>
#include <utility>
#include <stdexcept>

namespace wEngine
{

	/**
	 * @class DiscontinuityComponent
	 * @brief ECS component that manages excluded intervals for function plotting.
	 *
	 * This component allows the user to explicitly define intervals of the domain
	 * where a function should not be drawn (e.g., around asymptotes or undefined values).
	 * During rendering, points falling inside these intervals are skipped to avoid
	 * unwanted connections across discontinuities.
	 */
	class DiscontinuityComponent : public Component
	{
		public:
			/*
			 * @brief Default constructor.
			 */
			DiscontinuityComponent( ) = default;

			/*
			 * @brief Virtual destructor.
			 */
			virtual ~DiscontinuityComponent( ) = default;

			/**
			 * @brief Gives read-only access to the list of excluded intervals.
			 * @return A constant reference to the vector of (min, max) pairs.
			 */
			[[nodiscard]] const std::vector< std::pair< double,double > >& getExcludedIntervals( ) const;

			/**
			 * @brief Adds an excluded interval to the list.
			 * @param min Lower bound of the interval.
			 * @param max Upper bound of the interval.
			 * @throw std::invalid_argument if min >= max.
			 */
			void addExcludedInterval( double min, double max );

			/**
			 * @brief Removes all excluded intervals.
			 */
			void clearExcludedIntervals( );

			/**
			 * @brief Checks if a value falls into one of the excluded intervals.
			 * @param x Value to test.
			 * @return True if x is inside any excluded interval, false otherwise.
			 */
			[[nodiscard]] bool isInExcludedInterval( double x ) const;

			/*
			 * @brief Outputs the excluded intervals to the console for debugging.
			 */
			void debugPrint( ) const;
		private:
			std::vector< std::pair< double, double > > mExcludedIntervals;
	};

}//End of namespace wEngine

#endif