/**
 * @file wMathUtils.cpp
 * @brief Implementation of the MathUtils class.
 */

#include "wMathUtils.hpp"

namespace wEngine
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public static methods.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

std::vector< double > MathUtils::linspace( double start, double end, size_t nbPoints )
{
	if (start >= end)
	{
		throw std::runtime_error( "MathUtils::linspace error: start must be < end." );
	}

	if (nbPoints < 2)
	{
		throw std::runtime_error( "MathUtils::linspace requires at least 2 points." );
	}

	std::vector< double > tempVector( nbPoints );
	double step = (end - start) / (nbPoints - 1);

	size_t I = 0;
	std::generate( tempVector.begin( ), tempVector.end( ),
		[ start, step, &I ]( ) { double res = start + I * step; I++; return res; });

	return tempVector;
}

}//End of namespace wEngine