#ifndef CHECKPOINT_H
#define CHECKPOINT_H

using namespace std;
#include "..\PlatformerLibrary\RigidBody.h"
#include <SFML/Graphics.hpp>

class Checkpoint : public PlatformerLibrary::RigidBody {
public:
	sf::RenderWindow *render_window;
	sf::RectangleShape rectangle_shape;
	Checkpoint(sf::RenderWindow *window, sf::Vector2f position = sf::Vector2f(0.0f, 0.0f), sf::Vector2f dimensions = sf::Vector2f(0.0f, 0.0f), bool subject_to_gravity = true);
	void Draw(sf::Vector2f camera_position);
	void UpdateCheckPoint();
};

#endif