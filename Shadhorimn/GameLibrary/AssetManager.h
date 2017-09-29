#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#ifdef GAMELIBRARY_EXPORTS  
#define GAMELIBRARY_API __declspec(dllexport)   
#else  
#define GAMELIBRARY_API __declspec(dllimport)   
#endif  

using namespace std;
#include <SFML/Graphics.hpp>

namespace GameLibrary
{
	class AssetManager {
	private:
		std::map<std::string, sf::Texture*> textures = std::map<std::string, sf::Texture*>();
	public:
		GAMELIBRARY_API AssetManager();
		GAMELIBRARY_API sf::Texture* GetTexture(std::string file_path);
	};
}

#endif