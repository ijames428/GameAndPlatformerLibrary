#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef PLATFORMERLIBRARY_EXPORTS  
#define PLATFORMERLIBRARY_API __declspec(dllexport)   
#else  
#define PLATFORMERLIBRARY_API __declspec(dllimport)   
#endif  

#include "..\GameLibrary\Singleton.h"
#include "RigidBody.h"

namespace PlatformerLibrary
{
	class Platform : public RigidBody {
	public:
		sf::RectangleShape rectangle_shape;
		sf::RenderWindow *render_window;
		PLATFORMERLIBRARY_API Platform(sf::RenderWindow *window, sf::Vector2f position, sf::Vector2f dimensions, bool subject_to_gravity = false);
		PLATFORMERLIBRARY_API void Draw(sf::Vector2f camera_position);
	};
}

#endif