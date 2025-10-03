/*
+---------------------------------------------------------------------------------------------------------------------------------------------------+
Created by Wilfried Koch.
Copyright @ 2025 Wilfried Koch. All rights reserved.
+---------------------------------------------------------------------------------------------------------------------------------------------------+
*/

#ifndef W_ASSET_MANAGER_HPP
#define W_ASSET_MANAGER_HPP

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wswitch-default"
#include <SFML/Graphics.hpp>
#pragma GCC diagnostic pop

#include <string>
#include <map>
#include <stdexcept>
#include <iostream>

namespace wEngine
{

	/**
	 * @class AssetManager
	 * @brief Manages graphical assets such as fonts for reuse across the application.
	 *
	 * This class provides a centralized way to load, access, and manage graphical assets,
	 * currently supporting fonts via SFML. Assets are identified by string keys and stored
	 * internally to avoid reloading them multiple times.
	 *
	 * ### Key features:
	 * - Load fonts from file and associate them with a name.
	 * - Access loaded fonts via their name.
	 * - Remove fonts from memory when no longer needed.
	 * - Debug printing of loaded assets.
	 *
	 * This manager is non-copyable to ensure centralized ownership and avoid
	 * accidental duplication of resources.
	 * 
	 * @note If an asset fails to load or is accessed without being loaded first,
	 *       a `std::runtime_error` is thrown.
	 *
	 * @author Wilfried Koch
	 * @copyright © 2025 Wilfried Koch. All rights reserved.
	 * 
	 */
	class AssetManager
	{
		public:
			AssetManager( ) = default;
			AssetManager( const AssetManager& ) = delete;
			AssetManager& operator=( const AssetManager& ) = delete;
			~AssetManager( ) = default;

			/**
			 * @brief Loads a font from file and stores it under a given name.
			 *
			 * If successful, the font is stored under the given `name` and can later
			 * be retrieved with `getFont( name )`. If loading fails, an exception is thrown.
			 *
			 * @param name The unique name used to identify the font.
			 * @param fileName The path to the font file on disk.
			 *
			 * @throws std::runtime_error if the font cannot be loaded from file.
			 */
			void LoadFont( const std::string& name, const std::string& fileName );

			/**
			 * @brief Retrieves a reference to a previously loaded font.
			 * @param name The name of the font previously loaded.
			 * @return Reference to the corresponding sf::Font object.
			 * @throws std::runtime_error if the font does not exist.
			 */
			sf::Font& getFont( const std::string& name );

			/**
			 * @brief Removes a previously loaded font from memory.
			 * @param name The name of the font to remove.
			 * @throws std::runtime_error if the font does not exist.
			 */
			void RemoveFont( const std::string& name );

			/**
			 * @brief Prints the list of loaded fonts to standard output.
			 */
			void debugPrintFonts( ) const;
		private:
			std::map< std::string, sf::Font > mFont;

			/**
			 * @brief Checks whether a given key exists in a map and throws if not.
			 *
			 * Used internally to validate that a given asset (e.g., a font) has been loaded
			 * before attempting to access or remove it.
			 *
			 * @tparam Map A map-like container (e.g., std::map or std::unordered_map).
			 * @param map The container to search in.
			 * @param name The key to look for.
			 * @param type A string describing the type of asset (used in the error message).
			 *
			 * @throws std::runtime_error if the key is not found in the map.
			 */
			template < typename Map >
			static void EnsureExists( const Map& map, const std::string& name, const std::string& type );
	};

}//End of namespace wEngine

#endif