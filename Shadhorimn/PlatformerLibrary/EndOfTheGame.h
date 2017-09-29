#ifndef END_OF_THE_GAME_H
#define END_OF_THE_GAME_H

#ifdef PLATFORMERLIBRARY_EXPORTS  
#define PLATFORMERLIBRARY_API __declspec(dllexport)   
#else  
#define PLATFORMERLIBRARY_API __declspec(dllimport)   
#endif  

using namespace std;
#include "..\GameLibrary\Singleton.h"
#include <SFML/Graphics.hpp>
#include "RigidBody.h"

namespace PlatformerLibrary
{
	class EndOfTheGame : public RigidBody {
	public:
		sf::RenderWindow *render_window;
		sf::RectangleShape rectangle_shape;
		PLATFORMERLIBRARY_API EndOfTheGame(sf::RenderWindow *window, sf::Vector2f position = sf::Vector2f(0.0f, 0.0f), sf::Vector2f dimensions = sf::Vector2f(0.0f, 0.0f), bool subject_to_gravity = true);
		PLATFORMERLIBRARY_API void Draw(sf::Vector2f camera_position);
		PLATFORMERLIBRARY_API void UpdateEndOfTheGame();
	};
}

#endif