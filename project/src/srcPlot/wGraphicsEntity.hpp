/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_GRAPHICS_ENTITY_HPP
#define W_GRAPHICS_ENTITY_HPP

#include "../srcEntity/wEntity.hpp"

#include "../srcUtils/wAssetManager.hpp"
#include "../srcUtils/wPathUtils.hpp"

#include "wAxisEntity.hpp"
#include "wTitleEntity.hpp"
#include "wFunctionEntity.hpp"
#include "wDataPlotEntity.hpp"
#include "wLegendEntity.hpp"
#include "wLineEntity.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wswitch-default"
#include <SFML/Graphics.hpp>
#pragma GCC diagnostic pop

namespace wPlot2D
{

	/**
	 * @enum TitleAlignment
	 * @brief Defines the vertical placement of the main plot title.
	 */
	enum class TitleAlignment
	{
		Top,
		Bottom
	};

	/**
	 * @class GraphicsEntity
	 * @brief Central entity responsible for graphical rendering in wPlot2D.
	 *
	 * The `GraphicsEntity` manages the creation and control of the SFML rendering window.
	 * It provides high-level methods to add and configure graphical entities:
	 * - Axes (X and Y),
	 * - Titles (main or custom text),
	 * - Functions and raw data plots,
	 * - Legends,
	 * - Lines (with or without arrows).
	 *
	 * It also handles window configuration (title, size, background color) and
	 * allows exporting the final rendering to an image file.
	 *
	 * @note This class is intended to be the main entry point for user interaction
	 * with the rendering system.
	 *
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 * 
	 */
	class GraphicsEntity : public wEngine::Entity
	{
		public:
			/**
			 * @brief Constructs the graphics entity and initializes the rendering window and components.
			 * @param windowTitle	The title displayed on the window (default: "wPlot2D").
			 * @param windowSize	Window dimensions in pixels (default: 1600×1600).
			 * @param originFactor	Normalized factor in [0,1]x[0,1] specifying the origin’s relative position
			 *						(default: ( 0.5f, 0.5f ).
			 * @param scaleFactor	Normalized factor specifying the size of one logical unit
			 *						relative to window dimensions (default: ( 0.1f, 0.1f )).
			 * @throws std::invalid_argument if originFactor not in [0,1].
			 */
			GraphicsEntity(
				const std::string& windowTitle  = "wPlot2D",
				const sf::Vector2u& windowSize = { 1600, 1600 },
				const sf::Vector2f& originFactor = { 0.5f, 0.5f },
				const sf::Vector2f& scaleFactor  = { 0.1f, 0.1f } );

			/**
			 * @brief Virtual destructor.
			 */
			virtual ~GraphicsEntity( ) = default;

			/** 
			 * @brief Gives access to the internal SFML window.
			 * @return Reference to the internal `sf::RenderWindow`.
			 */
			[[nodiscard]] sf::RenderWindow& getWindow( );

			/**
			 * @brief Retrieves the current window size.
			 * @return Window size in pixels.
			 */
			[[nodiscard]] sf::Vector2u getWindowSize( ) const;

			/**
			 * @brief Sets a new window size.
			 * @param newSize Window dimensions in pixels.
			 */
			void setWindowSize( const sf::Vector2u& newSize );

			/**
			 * @brief Updates the window title.
			 * @param title New window title.
			 */
			void setWindowTitle( const std::string& title );

			/**
			 * @brief Clears the window with a background color.
			 * @param color Background fill color.
			 */
			void setBackgroundColor( const sf::Color& color );

			/**
			 * @brief Adds a font to the AssetManager.
			 * @param name Identifier string for the font.
			 * @param fileName Path to the font file.
			 */
			void addFont( const std::string& name, const std::string& fileName );

			/**
			 * @brief Retrieves a previously loaded font.
			 * @param name Identifier of the font.
			 * @return Reference to the `sf::Font`.
			 * @throws std::runtime_error if the font is not found.
			 */
			sf::Font& getFont( const std::string name );

			/**
			 * @brief Returns the current logical origin (in pixels).
			 * @return Origin position in pixel coordinates.
			 * @throws std::runtime_error if the PositionComponent is missing.
			 */
			[[nodiscard]] sf::Vector2f getOrigin( ) const;

			/**
			 * @brief Sets a new logical origin (normalized).
			 * @param originFactor in [0,1]×[0,1] new relative origin.
			 * @throws std::invalid_argument if originFactor is outside [0,1].
			 */
			void setOrigin( sf::Vector2f originFactor );

			/**
			 * @brief Returns the scale factors (pixels per logical unit).
			 * @return Scaling vector.
			 * @throws std::runtime_error if the ScaleComponent is missing.
			 */
			[[nodiscard]] sf::Vector2f getScale( ) const;

			/**
			 * @brief Sets new scale factors (normalized).
			 * @param scaleFactor new scaling factor
			 */
			void setScale( sf::Vector2f scaleFactor );

			/**
			 * @brief Returns the current logical offset.
			 * @return Offset vector in logical units.
			 * @throws std::runtime_error if the OffsetComponent is missing.
			 */
			[[nodiscard]] sf::Vector2f getOffset( ) const;

			/**
			 * @brief Sets the logical offset applied to the axes.
			 * @param offset Displacement in logical units.
			 */
			void setOffset( sf::Vector2f offset );

			/**
			 * @brief Adds an axis (X or Y) to the scene.
			 * @param type Axis type.
			 * @param axisRange Logical range for the axis.
			 * @return Pointer to the created AxisEntity.
			 */
			[[nodiscard]] AxisEntity* addAxis( AxisType type, sf::Vector2f axisRange );

			/**
			 * @brief Adds a main plot title (top or bottom).
			 * @param title Title text (UTF-8).
			 * @param alignment Vertical alignment (default: bottom).
			 * @return Pointer to the created TitleEntity.
			 */
			[[nodiscard]] TitleEntity* addTitle( const std::string& title, TitleAlignment alignment = TitleAlignment::Bottom );

			/**
			 * @brief Adds a main plot title (top or bottom).
			 * @param title Title text (UTF-16/32).
			 * @param alignment Vertical alignment (default: bottom).
			 * @return Pointer to the created TitleEntity.
			 */
			[[nodiscard]] TitleEntity* addTitle( const std::wstring& title, TitleAlignment alignment = TitleAlignment::Bottom );

			/**
			 * @brief Adds a mathematical function to the scene.
			 * @param func Function of type double(double).
			 * @param startX Domain start (logical).
			 * @param endX Domain end (logical).
			 * @param nbPoints Sampling resolution (default 1000).
			 * @return Pointer to the created FunctionEntity.
			 */
			[[nodiscard]] FunctionEntity* addFunction( std::function< double( double )> func, 
				double startX, double endX, size_t nbPoints = 1000 );

			/**
			 * @brief Adds a raw data plot (connected points).
			 * @param dataPoints Vector of (x,y) coordinates.
			 * @return Pointer to the created DataPlotEntity.
			 */
			[[nodiscard]] DataPlotEntity* addDataPlot( const std::vector< sf::Vector2f >& dataPoints );

			/**
			 * @brief Adds a legend box at a given position.
			 * @param position Normalized position inside window [0,1]x[0,1].
			 * @param hasFrame Whether the legend frame is visible (default true).
			 * @return Pointer to the created LegendEntity.
			 */
			[[nodiscard]] LegendEntity* addLegend( const sf::Vector2f& position, bool hasFrame = true );

			/**
			 * @brief Adds arbitrary text to the scene.
			 * @param text Text string (UTF-8).
			 * @param position Normalized position in [0,1]x[0,1].
			 * @return Pointer to the created TitleEntity.
			 */
			[[nodiscard]] TitleEntity* addText( const std::string& text, sf::Vector2f position );

			/**
			 * @brief Adds arbitrary text to the scene.
			 * @param text Text string (UTF-16/32).
			 * @param position Normalized position in [0,1]x[0,1].
			 * @return Pointer to the created TitleEntity.
			 */
			[[nodiscard]] TitleEntity* addText( const std::wstring& text, sf::Vector2f position );

			/**
			 * @brief Adds a line segment to the scene.
			 * @param start Start point in logical coordinates.
			 * @param end   End point in logical coordinates.
			 * @param withArrow Whether to render an arrowhead at the end.
			 * @return Pointer to the created LineEntity.
			 */
			[[nodiscard]] LineEntity* addLine( const sf::Vector2f& start, const sf::Vector2f& end, bool withArrow = false );

			/**
			 * @brief Saves a screenshot of the current window.
			 * @param filename Output file path (supported: png, bmp, tga, jpg).
			 * @throws std::runtime_error if saving fails.
			 */
			void saveToFile( const std::string& filename );
		private:
			sf::RenderWindow mWindow;
			wEngine::AssetManager mAssets;
			std::unique_ptr< AxisEntity > mAxisX;
			std::unique_ptr< AxisEntity > mAxisY;
			std::unique_ptr< TitleEntity > mTitle;
			TitleAlignment mAlignment;

			template < typename T >
			TitleEntity* addTitleImpl( const T& title, TitleAlignment alignment );

			template < typename T >
			TitleEntity* initText( const T& title, sf::Vector2f position );

			struct FunctionData
			{
				std::unique_ptr< FunctionEntity > entity;
				double startX;
				double endX;
				size_t nbPoints;
			};
			std::vector< FunctionData > mFunctions;

			struct DataPlotData
			{
				std::unique_ptr< DataPlotEntity > entity;
			};
			std::vector< DataPlotData > mDataPlots;

			std::unique_ptr< LegendEntity > mLegend;

			struct TextData
			{
				std::unique_ptr< TitleEntity > entity;
			};
			std::vector< TextData > mTexts;

			struct LineData
			{
			    std::unique_ptr< LineEntity > entity;
			};
			std::vector< LineData > mLines;

			/**
			 * @brief Renders all visual elements managed by the `GraphicsEntity`.
			 *
			 * This method is responsible for drawing every entity attached to the scene:
			 * - all functions, data plots, and lines,
			 * - the X and Y axes (if present),
			 * - the main title (with optional frame),
			 * - the legend (if present),
			 * - any additional text entities.
			 *
			 * It uses SFML’s rendering system and is called internally before exporting
			 * the scene with `saveToFile( )`.
			 *
			 * @note The `GraphicsEntity` does not maintain its own event/rendering loop. This
			 * method must be invoked explicitly each time a redraw is required.
			 */
			void render( );

			/**
			 * @brief Validates that a normalized factor lies in the [0,1] interval.
			 *
			 * This method is typically used to ensure that input parameters such as
			 * `originFactor` or `scaleFactor` are within the expected normalized range
			 * before conversion into pixel coordinates.
			 *
			 * @param factor 2D vector with normalized components (x,y).
			 * @throws std::invalid_argument if any component is outside the [0,1] interval.
			 */
			void validateNormalizedFactor( const sf::Vector2f& factor ) const;

			/**
			 * @brief Converts a normalized factor in [0,1] into absolute pixel coordinates.
			 *
			 * This utility function multiplies the normalized factor by the current window
			 * size to yield a position in pixels. It is used internally when computing the
			 * origin, scale, or custom placements based on relative factors.
			 *
			 * @param factor Normalized vector (x,y) with values in [0,1].
			 *
			 * @return A 2D vector representing the equivalent pixel coordinates.
			 */
			[[nodiscard]] sf::Vector2f convertNormalizedToPixels( const sf::Vector2f& factor ) const;
	};

}//End of namespace wPlot2D

#endif