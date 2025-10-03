/**
 * @file wEntity.cpp
 * @brief Implementation of the Entity class.
 */

#include "wEntity.hpp"

namespace wEngine
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Constructors and destructors.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

Entity::Entity( )
:	mEntityID{ generateNextEntityID( ) }
{

}

Entity::~Entity( )
{
	for (auto& [ typeID, component ] : mComponents)
	{
		component->disable( );
	}
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public methods: accessors and mutators.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

unsigned int Entity::getEntityID( ) const
{
	return mEntityID;
}

void Entity::clearComponents( )
{
	mComponents.clear( );
}

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Static members related to entity ID generation and reset.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

unsigned int Entity::sEntityIDCounter = 0;

void Entity::resetEntityIDCounter( )
{
	sEntityIDCounter = 0;
}

unsigned int Entity::generateNextEntityID( )
{
	return sEntityIDCounter++;
}

} // namespace wEngine