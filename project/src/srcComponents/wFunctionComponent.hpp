/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_FUNCTION_COMPONENT_HPP
#define W_FUNCTION_COMPONENT_HPP

#include <functional>
#include <stdexcept>

#include "../srcEntity/wComponent.hpp"

namespace wEngine
{

	/**
	 * @class FunctionComponent
	 * @brief ECS component that stores a mathematical function f(x).
	 *
	 * This component wraps a `std::function< double( double ) >` and provides
	 * an interface to evaluate the function at any given x-coordinate.
	 * It is mainly used by FunctionEntity to render mathematical curves.
	 * 
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 * 
	 */
	class FunctionComponent : public Component
	{
		public:
			/**
			 * @brief Constructs a FunctionComponent with a given function.
			 * @param function A callable object of type double( double ).
			 * @throw std::invalid_argument if the provided function is empty.
			 */
			FunctionComponent( std::function< double( double ) > function );

			/*
			 * @brief Virtual destructor.
			 */
			virtual ~FunctionComponent( ) = default;

			/**
			 * @brief Evaluates the stored function at a given x.
			 * @param x The input value.
			 * @return The result f(x).
			 * @throw std::runtime_error if no function is set.
			 */
			[[nodiscard]] double calculate( double x ) const;

			/*
			 * @brief Prints a message confirming that the function is set.
			 */
			void debugPrint( ) const;
		private:
			std::function< double( double ) > mFunction;
	};

}//End of namespace wEngine

#endif