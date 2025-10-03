/**
 * @file wFunctionComponent.cpp
 * @brief Implementation of the FunctionComponent class.
 */

#include "wFunctionComponent.hpp"

namespace wEngine
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Constructors and destructors.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

FunctionComponent::FunctionComponent( std::function< double( double ) > function )
:	mFunction{ function }
{
	if (!mFunction)
	{
		throw std::invalid_argument( "FunctionComponent: provided function is empty." );
	}
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

double FunctionComponent::calculate( double x ) const
{
	if (!mFunction)
	{
		throw std::runtime_error( "FunctionComponent: no function defined." );
	}

	return mFunction( x );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public method: debug.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void FunctionComponent::debugPrint( ) const
{
	if (mFunction)
	{
		std::cout << "FunctionComponent: function is set and callable.\n";
	}
	else
	{
		std::cout << "FunctionComponent: no function defined.\n";
	}
}

}//End of namespace wEngine