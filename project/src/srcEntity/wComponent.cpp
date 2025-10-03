/**
 * @file wComponent.cpp
 * @brief Implementation of the Component class.
 */

#include "wComponent.hpp"

namespace wEngine
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Constructors and destructors.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

Component::Component( )
:	mEnabled{ true },
	mParent{ nullptr }
{

}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods: accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

void Component::enable( )
{
	mEnabled = true;
}

void Component::disable( )
{
	mEnabled = false;
}

bool Component::isEnabled( ) const
{
	return mEnabled;
}

void Component::setParent( Entity* parent )
{
	mParent = parent;
}

Entity* Component::getParent( ) const
{
	return mParent;
}

}//End of namespace wEngine