/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_POSITION_COMPONENT_HPP
#define W_POSITION_COMPONENT_HPP

#include "../srcEntity/wComponent.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wswitch-default"
#include <SFML/Graphics.hpp>
#pragma GCC diagnostic pop

namespace wEngine
{

	/**
	 * @class PositionComponent
	 * @brief ECS component storing the position of an entity in 2D space and supports movement tracking.
	 *
	 * This component holds a 2D vector representing the current and previous spatial position of its parent entity.
	 * 
	 * ### Usage Examples:
	 * - Default position at origin:
	 *	@code
	 *		addComponent< wEngine::PositionComponent >( );
	 *	@endcode
	 *
	 * - Custom position:
	 *	@code
	 *		addComponent< wEngine::PositionComponent >( sf::Vector2f( 100.0f, 200.0f ) );
	 *	@endcode
	 * 
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 */
	class PositionComponent : public Component
	{
		public:
			/**
			 * @brief Constructs a PositionComponent with the given position.
			 * @param position Initial position (default is ( 0.0f, 0.0f )).
			 */
			PositionComponent( sf::Vector2f position = sf::Vector2f( 0.0f, 0.0f ) );

			/*
			 * @brief Virtual destructor.
			 */
			virtual ~PositionComponent( ) = default;

			/**
			 * @brief Gets the current position of the component.
			 * @return The current 2D position vector.
			 */
			[[nodiscard]] sf::Vector2f getPosition( ) const;

			/**
			 * @brief Returns the previous position (before the last move).
			 * @return The last recorded position.
			 */
			[[nodiscard]] sf::Vector2f getLastPosition( ) const;

			/**
			 * @brief Sets the 2D position to a new value.
			 * @param newPosition The new position.
			 */
			void setPosition( sf::Vector2f newPosition );

			/**
			 * @brief Moves the position by an offset.
			 * @param offset The offset to add to the current position.
			 * 
			 * Stores the current position as the last position before applying the offset.
			 */
			void move( const sf::Vector2f& offset );

			/**
			 * @brief Outputs the position (x, y) to standard output for debugging.
			 */
			void debugPrint( ) const;
		private:
			sf::Vector2f mPosition;
			sf::Vector2f mLastPosition;
	};

}//End of namespace wEngine

#endif