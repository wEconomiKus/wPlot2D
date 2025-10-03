/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_LINE_STYLE_COMPONENT_HPP
#define W_LINE_STYLE_COMPONENT_HPP

#include "../srcEntity/wComponent.hpp"

namespace wEngine
{

	/**
	 * @class LineStyleComponent
	 * @brief ESC component that defines the style of a line (solid, dotted, dashed).
	 *
	 * This component controls how lines are drawn in the rendering pipeline.
	 * For dotted and dashed styles, both dash length and gap length can be configured.
	 */
	class LineStyleComponent : public Component
	{
		public:
			/**
			 * @enum LineStyle
			 * @brief Available styles for line rendering.
			 */
			enum class LineStyle
			{
				Solid,
				Dotted,
				Dashed
			};

			/**
			 * @brief Constructs a LineStyleComponent with an optional style.
			 * @param style Line style to use (default: Solid).
			 */
			LineStyleComponent( LineStyle style = LineStyle::Solid );

			/*
			 * @brief Virtual destructor.
			 */
			virtual ~LineStyleComponent( ) = default;

			/**
			 * @brief Returns the current line style.
			 * @return The style as LineStyle.
			 */
			[[nodiscard]] LineStyle getStyle( ) const;

			/**
			 * @brief Sets the current line style.
			 * @param style New line style to apply.
			 */
			void setStyle( LineStyle style );

			/**
			 * @brief Returns the dash length (used for Dashed style).
			 * @return Dash length in pixels.
			 */
			[[nodiscard]] float getDashLength( ) const;

			/**
			 * @brief Sets the dash length.
			 * @param dashLength Dash length in pixels.
			 * @throw std::invalid_argument if dashLength <= 0.
			 */
			void setDashLength( float dashLength );

			/**
			 * @brief Returns the gap length (used for Dotted and Dashed styles).
			 * @return Gap length in pixels.
			 */
			[[nodiscard]] float getGapLength( ) const;

			/**
			 * @brief Sets the gap length.
			 * @param gapLength Gap length in pixels.
			 * @throw std::invalid_argument if gapLength < 0.
			 */
			void setGapLength( float gapLength );

			/*
			 * @brief Outputs the current style and parameters to the console.
			 */
			void debugPrint( ) const;
		private:
			LineStyle mStyle;
			float mDashLength;
			float mGapLength;
	};

}//End of namespace wEngine

#endif