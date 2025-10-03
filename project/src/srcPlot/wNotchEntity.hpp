/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_NOTCH_ENTITY_HPP
#define W_NOTCH_ENTITY_HPP

#include "../srcEntity/wEntity.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wswitch-default"
#include <SFML/Graphics.hpp>
#pragma GCC diagnostic pop

namespace wPlot2D
{

	enum class AxisType;

	/**
	 * @class NotchEntity
	 * @brief Represents a single tick mark ("notch") on a 2D axis.
	 *
	 * A `NotchEntity` is a visual element used to mark intervals along a coordinate axis,
	 * helping users interpret scale in a plot. It is rendered as a small filled rectangle,
	 * oriented perpendicularly to its associated axis (`X_AXIS` or `Y_AXIS`).
	 *
	 * ### Components required:
	 * - `PositionComponent`: specifies the top-left pixel position.
	 * - `ColorComponent`: defines the notch color.
	 * - `ThicknessComponent`: defines the thickness (along the axis).
	 * - `LengthComponent`: defines the length (perpendicular to the axis).
	 *
	 * ### Orientation:
	 * - `AxisType::X_AXIS` : vertical notch (aligned with Y),
	 * - `AxisType::Y_AXIS` : horizontal notch (aligned with X).
	 *
	 * The actual rendering logic is handled internally using `sf::RectangleShape`.
	 *
	 * @note Components must be added externally (typically by `AxisEntity::addNotches( )`).
	 * @see AxisEntity, AxisType, PositionComponent, LengthComponent, ThicknessComponent
	 *
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 * 
	 */
	class NotchEntity : public wEngine::Entity
	{
		public:
			/**
			 * @brief Constructs a `NotchEntity` aligned to a given axis.
			 * @param type The axis type (X or Y) which determines notch orientation.
			 */
			NotchEntity( AxisType type );

			/**
			 * @brief Virtual destructor.
			 */
			virtual ~NotchEntity( ) = default;

			/**
			 * @brief Renders the notch using SFML.
			 *
			 * Builds a rectangle from ECS components (position, thickness, length, color)
			 * and draws it in the render window.
			 *
			 * @throws std::runtime_error if any required component is missing.
			 * @param window The render window to draw onto.
			 */
			void render( sf::RenderWindow& window );

		private:
			AxisType mAlignment;
	};

} // namespace wPlot2D

#endif