<p align=center> <img src="project/Resources/Images/wPlot2D_logo.png" alt="Project Logo" width="500"/> </p>

# Changelog: wPlot2D

![Version](https://img.shields.io/badge/version-0.0.0-blue) &nbsp;
![License](https://img.shields.io/badge/license-Proprietary-lightgrey)

All notable changes to this project will be documented in this file.  

## [0.0.0] - October 02, 2025

### Added
- Initial project setup  
- Git repository initialized  
- Generated \'.gitignore\', \'README.md\' and \'CHANGELOG.md\'


## [0.1.0] - October 03, 2025

### Added
- Initial release of **wPlot2D**, a lightweight 2D plotting engine built on **SFML 3.0.0**.
- **Core ECS architecture**: entities, components, and systems designed for extensibility.
- **GraphicsEntity**:  
  - Central manager for window creation, origin, scale, and offset handling.  
  - High-level API to add axes, titles, functions, datasets, legends, and annotations.  
  - Export capability (`saveToFile`) to save rendered plots as images.
- **AxisEntity**:  
  - Support for **X** and **Y** axes with customizable color, thickness, arrowheads, and ranges.  
  - Configurable **tick marks (notches)** with position options (Center, Above, Below).  
  - Automatic label generation with decimal precision or custom text.  
  - Integrated axis titles with flexible positioning and styling.
- **NotchEntity**:  
  - Independent tick marks with configurable length, color, and thickness.  
  - Managed alignment relative to the axis line.
- **LabelEntity**:  
  - Flexible text rendering for axis ticks and custom labels.  
  - Support for numeric formatting (decimal places) and user-defined labels.
- **TitleEntity**:  
  - Standalone text entity with frame, padding, and customizable style.  
  - Used for axis titles, main plot titles, and additional annotations.
- **FunctionEntity**:  
  - Plot of mathematical functions with configurable domain and sampling resolution.  
  - Supports color, line style, and thickness customization.
- **DataPlotEntity**:  
  - Rendering of datasets from `(x, y)` points with adjustable visual style.  
  - Useful for experimental or simulation data.
- **LegendEntity**:  
  - Simple legend box with optional frame, supporting multiple line/function entries.  
  - Positioned relative to the window size.
- **LineEntity**:  
  - General-purpose line rendering with optional arrowheads.  
  - Reusable for axes, annotations, and custom plot elements.
