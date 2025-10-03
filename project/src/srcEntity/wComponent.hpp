/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_COMPONENT_HPP
#define W_COMPONENT_HPP

#include <iostream>

namespace wEngine
{

	class Entity;

	/**
	 * @class Component
	 * @brief Abstract base class for all ECS components.
	 * 
	 * Defines the minimal interface required by any component: activation control
	 * and access to its owning entity.
	 * 
	 * Intended to be subclassed by specific component implementations.
	 * 
	 * Created by Wilfried Koch. <br>
	 * Copyright @ 2025 Wilfried Koch. All rights reserved.
	 */
	class Component
	{
		public:
			/*
			 * @brief Virtual destructor.
			 */
			virtual ~Component( ) = default;

			/*
			 * @brief Enables the component (makes it active).
			 */
			virtual void enable( );

			/*
			 * @brief Disables the component (makes it inactive).
			 */
			virtual void disable( );

			/**
			 * @brief Checks whether the component is currently active.
			 * @return True if enabled, false if disabled.
			 */
			[[nodiscard]] bool isEnabled( ) const;

			/**
			 * @brief Sets the parent entity of this component.
			 * @param parent A pointer to the entity that owns this component.
			 */
			void setParent( Entity* parent );

			/**
			 * @brief Returns the parent entity of this component.
			 * @return Pointer to the owning Entity.
			 */
			[[nodiscard]] Entity* getParent( ) const;

		protected:

			/**
			 * @brief Protected constructor to restrict instantiation to derived classes.
			 */
			Component( );

		private:
			bool mEnabled;
			Entity* mParent;
	};

}// End of namespace wEngine

#endif