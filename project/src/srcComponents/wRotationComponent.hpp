/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_ROTATION_COMPONENT_HPP
#define W_ROTATION_COMPONENT_HPP

#include "../srcEntity/wComponent.hpp"

namespace wEngine
{

	/**
	 * @class RotationComponent
	 * @brief ECS component that stores a rotation angle (in degrees).
	 *
	 * This component can be attached to any entity that needs to be rotated
	 * relative to its logical origin. The angle is expressed in degrees
	 * (positive values correspond to counter-clockwise rotation).
	 *
	 * ### Usage Example:
	 *	@code
	 * 		addComponent< wEngine::RotationComponent >( 45.0f ); // Rotate 45° counter-clockwise
	 *	@endcode
	 * 
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 * 
	 */
	class RotationComponent : public Component
	{
		public:
			/**
			 * @brief Construct a RotationComponent with an initial angle.
			 * @param angle Initial rotation angle in degrees (default: 0.0f).
			 */
			RotationComponent( float angle = 0.0f );

			/*
			 * @brief Virtual destructor.
			 */
			virtual ~RotationComponent( ) = default;

			/**
			 * @brief Set the rotation angle.
			 * @param angle New rotation angle in degrees.
			 */
			void setAngle( float angle );

			/**
			 * @brief Get the current rotation angle.
			 * @return The stored angle in degrees.
			 */
			[[nodiscard]] float getAngle( ) const;

		private:
			float mAngle;
	};

}//End of namespace wEngine

#endif