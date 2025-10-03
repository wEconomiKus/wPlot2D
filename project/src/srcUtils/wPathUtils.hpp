/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_PATH_UTILS_HPP
#define W_PATH_UTILS_HPP

#include <string>

namespace wEngine
{

	/**
	 * @class PathUtils
	 * @brief Utility class providing static functions for managing executable and resource paths across platforms.
	 *
	 * This class retrieves the absolute path of the current executable or its parent directory,
	 * in a portable way (macOS, Windows, Linux). It is particularly useful for locating
	 * resources such as fonts, images, or configuration files relative to the application binary.
	 *
	 * All methods are static and do not require instantiation.
	 *
	 * @note If the path cannot be determined, a std::runtime_error is thrown.
	 * 
	 * ### Notes on unusual headers:
	 * - `<mach-o/dyld.h>` (macOS): provides `_NSGetExecutablePath`, part of the Mach-O dynamic loader API.
	 *   Documentation: see Apple Developer docs (man page: `man 3 dyld`).
	 * - `<windows.h>` (Windows): provides `GetModuleFileNameA`, part of the Win32 API.
	 *   Documentation: see Microsoft Learn (GetModuleFileName function).
	 * - `<unistd.h>` + `/proc/self/exe` (Linux): `/proc/self/exe` is a symbolic link exposing
	 *   the running executable, documented in `man 5 proc`.
	 *
	 * These APIs are not C++ standard and must be used with care, as they are platform-dependent.
	 * 
	 * @see std::filesystem for path manipulations.
	 *
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 * 
	 */
	class PathUtils
	{
		public:
			/**
			 * @brief Returns the absolute path to the current executable.
			 *
			 * Platform-specific APIs are used:
			 * 	- macOS: `_NSGetExecutablePath`
			 * 	- Windows: `GetModuleFileNameA`
			 * 	- Linux: `/proc/self/exe`
			 *
			 * @return Absolute path to the binary (e.g., "/path/to/MyApp.app/Contents/MacOS/MyApp").
			 *
			 * @throws std::runtime_error if the path cannot be resolved.
			 */
			[[nodiscard]] static std::string getExecutablePath( );

			/**
			 * @brief Returns the directory containing the current executable.
			 *
			 * This is often used as a base path to resolve relative resource paths.
			 *
			 * @return Directory containing the binary (e.g., "/path/to/MyApp.app/Contents/MacOS").
			 *
			 * @throws std::runtime_error if the path cannot be resolved.
			 */
			[[nodiscard]] static std::string getExecutableDir( );
	};

}//End of namespace wEngine

#endif