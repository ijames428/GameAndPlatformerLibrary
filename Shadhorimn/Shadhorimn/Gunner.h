#pragma once

#ifndef GUNNER_H
#define GUNNER_H

using namespace std;
//#include "..\PlatformerLibrary\RigidBody.h"
//#include "..\GameLibrary\Singleton.h"
//#include "..\GameLibrary\SpriteAnimation.h"
//#include "..\GameLibrary\Settings.h"
//#include "..\GameLibrary\AssetManager.h"
//#include "World.h"
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include "Creature.h"
#include "PlayerCharacter.h"
//#include "Projectile.h"

class Gunner : public Creature {
private:
	sf::Sound firing_projectile_sound;
	sf::SoundBuffer firing_projectile_buffer;
	std::vector<Projectile*> projectiles = std::vector<Projectile*>();
	float movement_speed;
	bool is_aggroed;
	float aggro_radius;
	sf::Int64 time_between_firing;
	sf::Int64 time_of_last_firing;
	sf::Int64 fire_duration;
	PlayerCharacter* target;
	sf::Color gunner_color;
	GameLibrary::SpriteAnimation* running_animation;
	sf::Texture idle_texture;
	sf::Sprite idle_sprite;
	float idle_sprite_scale;
	sf::Texture fire_texture;
	sf::Sprite fire_sprite;
	sf::Texture taking_damage_texture;
	sf::Sprite taking_damage_sprite;
	sf::Texture dead_on_ground_texture;
	sf::Sprite dead_on_ground_sprite;
public:
	Gunner(sf::RenderWindow *window, sf::Vector2f position = sf::Vector2f(0.0f, 0.0f), sf::Vector2f dimensions = sf::Vector2f(0.0f, 0.0f), bool subject_to_gravity = true);
	virtual void Update(sf::Int64 curr_time, sf::Int64 delta_time);
	void Draw(sf::Vector2f camera_position);
	void DrawProjectiles(sf::Vector2f camera_position, sf::Int64 curr_time);
};

#endif