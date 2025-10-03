/**
 * @file wPathUtils.cpp
 * @brief Implementation of the PathUtils class.
 */

#include "wPathUtils.hpp"

#if defined(__APPLE__)
	#include <mach-o/dyld.h>
	#include <vector>
#elif defined(_WIN32)
	#include <windows.h>
#else
	#include <unistd.h>
	#include <limits.h>
#endif

#include <filesystem>

namespace wEngine
{

/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
-> Public static methods.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

std::string PathUtils::getExecutablePath( )
{
	std::string path{ };

#if defined(__APPLE__)
	// macOS: use _NSGetExecutablePath
	char buffer[1024];
	uint32_t size = sizeof( buffer );
	if (_NSGetExecutablePath( buffer, &size ) == 0)
	{
		path = std::string( buffer );
	}
	else
	{
		// Fallback if buffer too small
		std::vector< char > dynamicBuffer( size );
		if (_NSGetExecutablePath( dynamicBuffer.data( ), &size) == 0)
		{
			path = std::string( dynamicBuffer.data( ));
		}
	}
#elif defined(_WIN32)
	// Windows: use GetModuleFileNameA
	char buffer[ MAX_PATH ];
	if (GetModuleFileNameA( NULL, buffer, MAX_PATH ) > 0)
	{
		path = std::string( buffer );
	}
#else
	// Linux: read /proc/self/exe symbolic link
	char buffer[ PATH_MAX ];
	ssize_t count = readlink( "/proc/self/exe", buffer, PATH_MAX );
	if (count != -1)
	{
		path = std::string( buffer, static_cast< size_t >( count ) );
	}
#endif

	if (path.empty( ))
	{
		throw std::runtime_error( "PathUtils::getExecutablePath: unable to determine executable path" );
	}

	return std::filesystem::absolute( path ).string( );
}

std::string PathUtils::getExecutableDir( )
{
	return std::filesystem::path( getExecutablePath( ) ).parent_path( ).string( );
}

}//End of namespace wEngine