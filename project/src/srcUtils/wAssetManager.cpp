/**
 * @file wAssetManager.cpp
 * @brief Implementation of the AssetManager class.
 */

#include "wAssetManager.hpp"

#include <iostream>

namespace wEngine
{

/*
+----------------------------------------------------------------------------------------------------------------------+
-> Public methods. Font management.
+----------------------------------------------------------------------------------------------------------------------+
*/

void AssetManager::LoadFont( const std::string& name, const std::string& fileName )
{
	sf::Font font;
	if( !font.openFromFile( fileName ) )
	{
		throw std::runtime_error( "AssetManager error: unable to load font '" + name + "' at '" + fileName + "'" );
	}
	mFont.emplace( name, std::move( font ) );
}

void AssetManager::LoadFont( const std::string& name, const std::vector< std::string >& possiblePaths )
{
	sf::Font font;
	bool loaded = false;

#if defined(_WIN32)
	// On Windows, we cannot reassign stderr, so just skip silencing.
	for (const auto& path : possiblePaths)
	{
		if (font.openFromFile( path ))
		{
			loaded = true;
			break;
		}
	}
#else
	// On Unix/macOS, temporarily silence SFML error output.
	FILE* old_stderr = stderr;
	FILE* nullout = fopen( "/dev/null", "w" );
	if (nullout)
	{
		stderr = nullout;
	}

	// Try all possible paths until one succeeds.
	for (const auto& path : possiblePaths)
	{
		if (font.openFromFile( path ))
		{
			loaded = true;
			break;
		}
	}

	if (nullout)
	{
		// Restore normal stderr output.
		fclose( stderr );
		stderr = old_stderr;
	}
#endif

	// If no path succeeded, build a detailed error message.
	if (!loaded)
	{
		std::string msg = "AssetManager error: unable to load font '" + name + "' from any of the following paths:\n";

		for (const auto& p : possiblePaths)
		{
			msg += "  - " + p + "\n";
		}

		throw std::runtime_error( msg );
	}

	// Store the loaded font in the internal map.
	mFont.emplace( name, std::move( font ) );
}

sf::Font& AssetManager::getFont( const std::string& name )
{
	EnsureExists( mFont, name, "Font" );
	return mFont.at( name );
}

void AssetManager::RemoveFont( const std::string& name )
{
	EnsureExists( mFont, name, "Font" );
	mFont.erase( name );
}

void AssetManager::debugPrintFonts( ) const
{
	if (mFont.empty( ))
	{
		std::cout << "AssetManager: no fonts loaded.\n";
	}
	else
	{
		std::cout << "AssetManager: loaded fonts:\n";
		for (const auto& [name, font] : mFont)
		{
			std::cout << " - " << name << "\n";
		}
	}
}

/*
+----------------------------------------------------------------------------------------------------------------------+
-> Private methods.
+----------------------------------------------------------------------------------------------------------------------+
*/

template < typename Map >
void AssetManager::EnsureExists( const Map& map, const std::string& name, const std::string& type )
{
	if (map.find( name ) == map.end( ))
	{
		throw std::runtime_error( "AssetManager error: " + type + " not found with key '" + name + "'" );
	}
}

}//End of namespace wEngine