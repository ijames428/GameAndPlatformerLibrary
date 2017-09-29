#pragma once

#ifndef CHARGER_H
#define CHARGER_H

using namespace std;
//#include "..\GameLibrary\Singleton.h"
//#include "..\PlatformerLibrary\RigidBody.h"
//#include "..\GameLibrary\Settings.h"
//#include "World.h"
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include "Creature.h"
#include "PlayerCharacter.h"
//#include "Projectile.h"

class Charger : public Creature {
private:
	sf::Sound hitting_player_sound;
	sf::SoundBuffer hitting_player_buffer;
	sf::Sound hitting_wall_sound;
	sf::SoundBuffer hitting_wall_buffer;
	std::vector<Projectile*> projectiles = std::vector<Projectile*>();
	float movement_speed;
	bool is_charging;
	float aggro_radius;
	float charge_speed;
	float charge_speed_second_stage;
	//sf::Int64 time_between_firing;
	//sf::Int64 time_of_last_firing;
	PlayerCharacter* target;
	float attack_radius;
	sf::Int64 time_of_last_attack;
	sf::Int64 duration_of_attack;
	sf::Int64 time_between_attacks;
	PlatformerLibrary::RigidBody* HitBox;
	PlatformerLibrary::RigidBody* WallDetector;
	sf::Vector2f charge_velocity;
	int starting_hit_points;
public:
	Charger(sf::RenderWindow *window, sf::Vector2f position = sf::Vector2f(0.0f, 0.0f), sf::Vector2f dimensions = sf::Vector2f(0.0f, 0.0f), bool subject_to_gravity = true);
	virtual void Update(sf::Int64 curr_time, sf::Int64 delta_time);
	void Draw(sf::Vector2f camera_position);
	void DrawProjectiles(sf::Vector2f camera_position, sf::Int64 curr_time);
	void StartCharge();
	bool IsInSecondStage();
	void FireSecondStageProjectiles();
};

#endif