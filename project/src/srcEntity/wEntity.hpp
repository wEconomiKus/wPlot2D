/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_ENTITY_HPP
#define W_ENTITY_HPP

#include <vector>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <stdexcept>
#include <type_traits>

#include "wComponent.hpp"

namespace wEngine
{

	/*
	 * @brief Generates a new unique component type ID.
	 * @return A unique integer for component type identification.
	 */
	inline std::size_t getNextComponentTypeID( )
	{
		static std::size_t componentTypeCounter = 0;
		return componentTypeCounter++;
	}

	/*
	 * @brief Returns the unique type ID associated with a specific component type.
	 * @tparam ComponentType The type of the component.
	 * @return A unique integer identifying the component type.
	 */
	template< typename ComponentType >
	std::size_t getComponentTypeID( ) noexcept
	{
		static std::size_t componentTypeID = getNextComponentTypeID( );
		return componentTypeID;
	}

	/**
	 * @class Entity
	 * @brief Represents an entity in the ECS (Entity-Component System) architecture.
	 *
	 * Each entity is uniquely identified and can dynamically manage a collection of components.
	 * Components are stored in a type-safe map and accessed by type.
	 * 
	 * The class provides utility methods to add, remove, retrieve and query components,
	 * as well as retrieve components through interfaces.
	 *
	 * @note Entities do not define behavior directly: behavior is defined by the components attached to them.
	 *
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 */
	class Entity
	{
		public:
			/*
			 * @brief Default constructor. Generates a new entity with a unique ID.
			 */
			Entity( );

			/*
			 * @brief Destructor. Disables all attached components before destruction.
			 */
			virtual ~Entity( );

			/**
			 * @brief Returns the unique ID associated with this entity.
			 * @return Unsigned integer representing the entity's ID.
			 */
			[[nodiscard]] unsigned int getEntityID( ) const;

			/**
			 * @brief Removes all components currently attached to the entity.
			 */
			void clearComponents( );

			/**
			 * @brief Resets the global entity ID counter to zero.
			 *
			 * This affects all subsequently created entities.
			 * Use with caution, especially in multi-entity systems.
			 */
			static void resetEntityIDCounter( );

			/**
			 * @brief Adds a new component of type T to the entity.
			 * 
			 * Constructs the component using the provided arguments and attaches it to the entity.
			 * 
			 * @tparam T Component type, must inherit from wEngine::Component.
			 * @tparam Args Variadic arguments used to construct the component.
			 * @param args Constructor arguments forwarded to the component.
			 * @return Shared pointer to the newly created component.
			 * 
			 * @throws std::runtime_error if a component of the same type already exists in the entity.
			 */
			template< typename T, typename... Args >
			std::shared_ptr< T > addComponent( Args&&... args )
			{
				static_assert( std::is_base_of< Component, T >::value, "T must be derived from Component" );

				auto typeID = getComponentTypeID< T >( );
				if (mComponents.contains( typeID ))
				{
					std::cerr << "Warning: Component " << typeid( T ).name( )
					          << " already exists in entity " << mEntityID << std::endl;
					throw std::runtime_error( "Component already exists in entity" );
				}

				auto component = std::make_shared< T >( std::forward< Args >( args )... );
				component->setParent( this );
				mComponents[ typeID ] = component;

				return component;
			}

			/**
			 * @brief Removes the component of type T from the entity.
			 * 
			 * If no such component exists, this operation does nothing.
			 * 
			 * @tparam T Component type to remove.
			 */
			template< typename T >
			void removeComponent( )
			{
				static_assert( std::is_base_of< Component, T >::value, "T must be derived from Component" );

				auto typeID = getComponentTypeID< T >( );
				mComponents.erase( typeID );
			}

			/**
			 * @brief Checks whether the entity has a component of type T.
			 * 
			 * @tparam T Component type to check.
			 * @return True if the component is present, false otherwise.
			 */
			template< typename T >
			[[nodiscard]] bool hasComponent( ) const noexcept
			{
				static_assert( std::is_base_of< Component, T >::value, "T must be derived from Component" );

				return mComponents.contains( getComponentTypeID< T >( ) );
			}

			/**
			 * @brief Retrieves the component of type T attached to the entity.
			 * 
			 * @tparam T Component type to retrieve.
			 * @return Shared pointer to the component if found, or nullptr otherwise.
			 */
			template< typename T >
			[[nodiscard]] std::shared_ptr< T > getComponent( ) const
			{
				static_assert( std::is_base_of< Component, T >::value, "T must be derived from Component" );

				auto typeID = getComponentTypeID< T >( );
				auto it = mComponents.find( typeID );
				if (it != mComponents.end( ))
				{
					return std::dynamic_pointer_cast< T >( it->second );
				}

				return nullptr;
			}

			/**
			 * @brief Retrieves the component of type T and throws if it's missing.
			 *
			 * This method is similar to getComponent( ), but throws a std::runtime_error
			 * if the component is not found. Useful for critical systems where components
			 * must be present.
			 *
			 * @tparam T The type of the component.
			 * @param context Optional string to specify the context of the call (e.g., method name).
			 * @return A shared pointer to the required component.
			 * @throws std::runtime_error if the component is not found.
			 */
			template< typename T >
			[[nodiscard]] std::shared_ptr< T > requireComponent( const std::string& context = "" ) const
			{
				static_assert( std::is_base_of< Component, T >::value, "T must be derived from Component" );

				if (!hasComponent< T >( ))
				{
					std::string msg = "Missing required component: ";
					msg += typeid( T ).name( );
					if (!context.empty( ))
					{
						msg += " in context: " + context;
					}
					throw std::runtime_error( msg );
				}

				return getComponent< T >( );
			}

			/**
			 * @brief Returns the first component that implements the specified interface.
			 *
			 * Checks all components attached to the entity using dynamic casting. If a component
			 * matches the given interface type, it is returned.
			 *
			 * @tparam Interface The desired interface type.
			 * @return A shared pointer to the matching component, or nullptr if none found.
			 */
			template< typename Interface >
			[[nodiscard]] std::shared_ptr< Interface > getInterfaceComponent( ) const
			{
				for (const auto& [ typeID, component ] : mComponents)
				{
					auto interfaceComponent = std::dynamic_pointer_cast< Interface >( component );
					if (interfaceComponent)
					{
						return interfaceComponent;
					}
				}
				return nullptr;
			}

		private:
			unsigned int mEntityID;
			std::unordered_map< std::size_t, std::shared_ptr< Component > > mComponents;

			static unsigned int sEntityIDCounter;
			static unsigned int generateNextEntityID( );
	};

}// End of namespace wEngine

#endif