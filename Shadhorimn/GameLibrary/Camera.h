#ifndef CAMERA_H
#define CAMERA_H

#ifdef GAMELIBRARY_EXPORTS  
#define GAMELIBRARY_API __declspec(dllexport)   
#else  
#define GAMELIBRARY_API __declspec(dllimport)   
#endif  

using namespace std;
#include <SFML/Graphics.hpp>

namespace GameLibrary
{
	class Camera {
	public:
		sf::Vector2f viewport_position;
		sf::Vector2f viewport_dimensions;
		GAMELIBRARY_API Camera(sf::Vector2f position, sf::Vector2f dimensions);
	};
}

#endif