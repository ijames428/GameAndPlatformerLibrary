#pragma once

#ifndef DRONE_H
#define DRONE_H

using namespace std;
//#include "..\GameLibrary\Singleton.h"
//#include "../GameLibrary/Settings.h"
#include "..\GameLibrary\Settings.h"
//#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Creature.h"
#include "PlayerCharacter.h"
#include "Projectile.h"

class Drone : public Creature {
private:
	sf::Sound firing_projectile_sound;
	sf::SoundBuffer firing_projectile_buffer;
	std::vector<Projectile*> projectiles = std::vector<Projectile*>();
	float movement_speed;
	bool is_aggroed;
	float aggro_radius;
	sf::Int64 time_between_firing;
	sf::Int64 time_of_last_firing;
	PlayerCharacter* target;
public:
	Drone(sf::RenderWindow *window, sf::Vector2f position = sf::Vector2f(0.0f, 0.0f), sf::Vector2f dimensions = sf::Vector2f(0.0f, 0.0f), bool subject_to_gravity = true);
	virtual void Update(sf::Int64 curr_time, sf::Int64 delta_time);
	void Draw(sf::Vector2f camera_position);
	void DrawProjectiles(sf::Vector2f camera_position, sf::Int64 curr_time);
};

#endif