/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_MATH_UTILS_HPP
#define W_MATH_UTILS_HPP

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#include <SFML/System/Vector2.hpp>
#pragma GCC diagnostic pop

#include <cmath>
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace wEngine
{

	/**
	 * @class MathUtils
	 * @brief Provides common mathematical helper functions for plotting and geometry.
	 *
	 * This utility class groups static methods that are frequently needed
	 * when working with numerical data, discretization, and rendering curves.
	 * 
	 * @note All methods are static and do not require instantiation.
	 *
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 * 
	 */
	class MathUtils
	{
		public:
			/**
			 * @brief Generates a linearly spaced vector of values between two bounds.
			 *
			 * This function produces a vector of
			 * evenly spaced points between @p start and @p end (inclusive).
			 *
			 * @param start Starting value.
			 * @param end   Ending value.
			 * @param nbPoints Number of points to generate (must be >= 2).
			 * @return A std::vector< double > containing evenly spaced values.
			 * @throw std::invalid_argument if start >= end or nbPoints < 2.
			 *
			 *	@code
			 *		auto values = MathUtils::linspace( 0.0, 1.0, 5 );
			 *		// values = { 0.0, 0.25, 0.5, 0.75, 1.0 }
			 *	@endcode
			 */
			[[nodiscard]] static std::vector< double > linspace( double start, double end, size_t nbPoints );
	};

}//End of namespace wEngine

#endif