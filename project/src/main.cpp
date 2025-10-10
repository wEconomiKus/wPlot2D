/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

/**
 * @mainpage wPlot2D - ECS-Based 2D Plotting Engine
 *
 * \image html "./Resources/Images/wPlot2D_logo.png" width=500px
 * 
 * @section title wPlot2D
 * 
 * @subsection intro_sec Introduction
 *
 *  <div align="justify">wPlot2D is a lightweight C++ plotting library designed to create clean and customizable 2D visualizations. It provides
 * essential features such as axes, labels, titles, legends, and annotations, while allowing users to export high-quality graphics for reports,
 * teaching, or research. The library is built with a modular design, making it easy to integrate into existing C++ projects. Its focus is on
 * clarity, precision, and reproducibility, providing an accessible tool for academic and scientific work. </div>
 *
 * @subsection features_sec Features
 * - Entity and Component system
 * - Dynamic component management with type-safe access
 * - Support for SFML-based rendering
 * 
 * @subsection minimal example
 * @code
 * #include <wPlot2D.hpp>
 * #include <cmath>
 *
 * int main( )
 * {
 *     // --- Graph creation ------------------------------------------------------
 *     auto graph = wPlot2D::GraphicsEntity( );
 *     graph.setOrigin( { 0.5f, 0.5f } );
 *     graph.setScale( { 0.1f, 0.1f } );
 *
 *     // --- Graph title ---------------------------------------------------------
 *     auto title = graph.addTitle( "wPlot2D", wPlot2D::TitleAlignment::Top );
 *     title->setFont( graph.getFont( "Inconsolata" ) );
 *     title->setFrameThickness( 5.0f );
 *     title->setPadding( { 20.0f, 20.0f } );
 *
 *     // --- X axis --------------------------------------------------------------
 *     auto xAxis = graph.addAxis( wPlot2D::AxisType::X_AXIS, { -3.8f, 3.8f } );
 *     xAxis->addTitle( "x" );
 *     xAxis->addNotches( 0.5f, wPlot2D::NotchPosition::Center, true );
 *
 *     // --- Y axis --------------------------------------------------------------
 *     auto yAxis = graph.addAxis( wPlot2D::AxisType::Y_AXIS, { -3.8f, 3.8f } );
 *     yAxis->addTitle( "f(x)" );
 *     yAxis->addNotches( 0.5f, wPlot2D::NotchPosition::Center, true );
 *
 *     // --- Function (sinus) ----------------------------------------------------
 *     auto fSinus = graph.addFunction( [ ](double x ) { return std::sin( x ); }, -3.3, 3.3 );
 *     fSinus->setColor( sf::Color::Red );
 *
 *     // --- Legend --------------------------------------------------------------
 *     auto legend = graph.addLegend( { 0.2f, 0.8f }, true );
 *     legend->addItem( "Sinus", fSinus );
 *     legend->setCharacterSize( 30.0f );
 *     legend->setFont( graph.getFont( "Courier" ) );
 *
 *     // --- Save the graph ------------------------------------------------------
 *     graph.saveToFile( "/../output/Example.png" );
 *
 *     return 0;
 * }
 * @endcode
 *
 * @subsection links_sec Links
 * - [GitHub Repository](https://github.com/wEconomiKus/wPlot2D)
 * - [itch.io Page](https://wEconomiKus.itch.io/wPlot2D)
 * - [Project Website](https://weconomikus.github.io/wilfried-koch-page/wPlot2D)
 *
 * @subsection author_sec Author
 * Created by Wilfried Koch. <br>
 * Copyright @ 2025 Wilfried Koch. All rights reserved.
 */

#include <iostream>

int main( )
{
	std::cout << "wPlot2D" << std::endl;
}