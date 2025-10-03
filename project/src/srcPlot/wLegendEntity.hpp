/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_LEGEND_ENTITY_HPP
#define W_LEGEND_ENTITY_HPP

#include "../srcEntity/wEntity.hpp"
#include "wLineEntity.hpp"
#include "wFrameEntity.hpp"

#include "wFunctionEntity.hpp"
#include "wDataPlotEntity.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wswitch-default"
#include <SFML/Graphics.hpp>
#pragma GCC diagnostic pop

namespace wPlot2D
{


	/**
	 * @class LegendEntity
	 * @brief Represents a legend box that describes functions and data plots.
	 *
	 * A `LegendEntity` provides a visual legend for plotted entities such as
	 * `FunctionEntity` and `DataPlotEntity`. Each legend item is composed of:
	 * - A sample line (`LineEntity`) with the same style, thickness, and color as the source entity.
	 * - A text label (`sf::Text`) describing the entity.
	 *
	 * The legend can optionally be surrounded by a frame (`FrameEntity`) with
	 * configurable padding, outline color, thickness, and fill color.
	 *
	 * ### Components and Features:
	 * - Configurable font and text size.
	 * - Support for UTF-8 and wide string labels.
	 * - Dynamic addition of items from existing plotted entities.
	 * - Automatic alignment of line + text pairs inside the legend box.
	 *
	 * @see FunctionEntity, DataPlotEntity, LineEntity, FrameEntity
	 *
	 * @note The font passed in the constructor must remain valid during the lifetime
	 * of the legend, as SFML does not copy font data internally.
	 *
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch
	 * 
	 */
	class LegendEntity : public wEngine::Entity
	{
		public:
			/**
			 * @brief Constructs a LegendEntity.
			 *
			 * Initializes the legend with a given font, anchor position, and optional frame.
			 *
			 * @param font		Reference to the font used for labels (must remain valid).
			 * @param position	Anchor position of the legend box in window coordinates.
			 * @param hasFrame	Whether to display a surrounding frame (default: true).
			 */
			LegendEntity( const sf::Font& font, const sf::Vector2f& position, bool hasFrame = true );

			/**
			 * @brief Virtual destructor.
			 */
			virtual ~LegendEntity( ) = default;

			/**
			 * @brief Adds a new legend item associated with a function.
			 * @param label   Label text (UTF-8 string).
			 * @param function Pointer to the source FunctionEntity.
			 */
			void addItem( const std::string& label, FunctionEntity* function );

			/**
			 * @brief Adds a new legend item associated with a function (wide string).
			 * @param label   Label text (wide string).
			 * @param function Pointer to the source FunctionEntity.
			 */
			void addItem( const std::wstring& label, FunctionEntity* function );

			/**
			 * @brief Adds a new legend item associated with a data plot.
			 * @param label Label text (UTF-8 string).
			 * @param plot  Pointer to the source DataPlotEntity.
			 */
			void addItem( const std::string& label, DataPlotEntity* plot );

			/**
			 * @brief Adds a new legend item associated with a data plot (wide string).
			 * @param label Label text (wide string).
			 * @param plot  Pointer to the source DataPlotEntity.
			 */
			void addItem( const std::wstring& label, DataPlotEntity* plot );

			/**
			 * @brief Enables or disables the surrounding frame of the legend.
			 * @param enabled True to display the frame, false to hide it.
			 */
			void setFrameEnabled( bool enabled );

			/**
			 * @brief Sets the fill color of the legend frame.
			 * @param color SFML color applied to the frame's background.
			 */
			void setFrameFillColor( const sf::Color& color );

			/**
			 * @brief Sets the outline color of the legend frame.
			 * @param color SFML color applied to the frame's border.
			 */
			void setFrameOutlineColor( const sf::Color& color );

			/**
			 * @brief Sets the outline thickness of the legend frame.
			 * @param thickness Thickness in pixels (positive for outside expansion).
			 */
			void setFrameThickness( float thickness );

			/**
			 * @brief Sets the internal padding between items and the frame borders.
			 *
			 * Padding defines horizontal and vertical margins in pixels.
			 *
			 * @param padding Vector (x, y) where:
			 * - `x` = horizontal padding (left/right),
			 * - `y` = vertical padding (top/bottom).
			 */
			void setPadding( const sf::Vector2f& padding );

			/**
			 * @brief Updates the font used for all legend labels.
			 * @note The font must remain valid during the legend’s lifetime,
			 *       as SFML does not copy font data internally.
			 * @param font Reference to an externally managed sf::Font.
			 */
			void setFont( const sf::Font& font );

			/**
			 * @brief Sets the character size of the legend text.
			 * @param size Font size in pixels.
			 */
			void setCharacterSize( unsigned int size );

			/**
			 * @brief Sets the color of the legend labels.
			 * @param color SFML color applied to all legend text.
			 */
			void setTextColor( const sf::Color& color );

			/**
			 * @brief Renders the legend (all items and optional frame) to the target window.
			 *
			 * Each item is drawn with its sample line and label text, aligned inside
			 * the legend box. The optional frame is drawn behind all items.
			 *
			 * @param window The target SFML render window.
			 */
			void render( sf::RenderWindow& window );
		private:
			/**
			 * @struct LegendItem
			 * @brief Internal structure holding a single legend entry.
			 */
			struct LegendItem
			{
				std::string label;
				std::unique_ptr< LineEntity > line;
				sf::Text labelText;

				LegendItem( std::unique_ptr< LineEntity > line, sf::Text&& txt )
				:	line{ std::move( line ) },
					labelText{ std::move( txt ) }
					{

					}
			};

			/**
			 * @brief Adds a legend item corresponding to a given data source.
			 *
			 * This generic method is used internally by the public `addItem` overloads
			 * to handle both `FunctionEntity` and `DataPlotEntity`, with string or wstring labels.
			 *
			 * @tparam LabelT Type of the label (std::string or std::wstring).
			 * @tparam SourceT Type of the data source (FunctionEntity* or DataPlotEntity*).
			 * @param label The label text to display.
			 * @param source Pointer to the source entity whose style (color, thickness, line style)
			 * is replicated in the legend entry.
			 */
			template < typename LabelT, typename SourceT >
			void addItemGeneric( const LabelT& label, SourceT* source );

			/**
			 * @brief Creates a legend item with a line sample and a label.
			 *
			 * This method constructs the actual legend entry, combining:
			 * - a small line segment drawn with the style of the source,
			 * - a text label rendered with the legend's font and character size.
			 *
			 * @tparam T Type of the label (std::string or std::wstring).
			 * @param label The label text to display.
			 * @param line A unique pointer to a LineEntity representing the legend symbol.
			 */
			template< typename T >
			void createItem( const T& label, std::unique_ptr< LineEntity > line );

			std::vector< LegendItem > mItems;
			const sf::Font& mFont;
			unsigned int mCharacterSize = 30;
			FrameEntity mFrame;
	};

} // namespace wPlot2D

#endif