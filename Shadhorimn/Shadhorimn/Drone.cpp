using namespace std;
#include <iostream>
#include "Drone.h"
#include "World.h"
#include "Settings.h"
#define PI 3.14159265

Drone::Drone(sf::RenderWindow *window, sf::Vector2f position, sf::Vector2f dimensions, bool subject_to_gravity) : Creature::Creature(window, position, dimensions, subject_to_gravity) {
	SetEntityType(GameLibrary::Singleton<World>::Get()->ENTITY_TYPE_DRONE);
	hit_points = 2;

	jump_power = 1.0f;
	aggro_radius = 500.0f;
	is_aggroed = false;

	movement_speed = 1.0f;

	sf::RectangleShape shape(dimensions);
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition(position);

	rectangle_shape = shape;

	target = GameLibrary::Singleton<World>::Get()->main_character;

	time_between_firing = 750;
	time_of_last_firing = 0;
	for (int i = 0; i < 10; i++) {
		projectiles.push_back(new Projectile(window, position, sf::Vector2f(20.0f, 20.0f), false));
		projectiles[i]->ExcludeFromCollision(GameLibrary::Singleton<World>::Get()->ENTITY_TYPE_DRONE);
	}

	if (!firing_projectile_buffer.loadFromFile("Sound/drone_firing.wav")) {
		throw exception("Sound file not found");
	} else {
		firing_projectile_sound.setBuffer(firing_projectile_buffer);
		firing_projectile_sound.setVolume(GameLibrary::Singleton<Settings>().Get()->effects_volume);
	}
}

void Drone::UpdateBehavior(sf::Int64 curr_time) {
	current_time = curr_time;

	if (hit_points <= 0) {
		EnableGravity();
	} else {
		if (hit_stun_start_time + hit_stun_duration > curr_time) {
			EnableGravity();
		} else {
			DisableGravity();

			is_aggroed = RigidBody::GetDistanceBetweenTwoPoints(sf::Vector2f(target->GetCurrentPosition().x + target->GetCurrentDimensions().x / 2.0f, target->GetCurrentPosition().y + target->GetCurrentDimensions().y / 2.0f), sf::Vector2f(GetCurrentPosition().x, GetCurrentPosition().y)) < aggro_radius;

			if (is_aggroed) {
				if (target->GetCurrentPosition().x > GetCurrentPosition().x) {
					SetVelocity(movement_speed, GetVelocity().y);
				}
				else if (target->GetCurrentPosition().x < GetCurrentPosition().x) {
					SetVelocity(-movement_speed, GetVelocity().y);
				}

				if (target->GetCurrentPosition().y > GetCurrentPosition().y) {
					SetVelocity(GetVelocity().x, movement_speed);
				}
				else if (target->GetCurrentPosition().y < GetCurrentPosition().y) {
					SetVelocity(GetVelocity().x, -movement_speed);
				}

				if (time_of_last_firing + time_between_firing < current_time) {
					for (int i = 0; i < (int)(projectiles.size()); i++) {
						if (!projectiles[i]->is_active) {
							float deltaX = target->GetCurrentPosition().x - GetCurrentPosition().x;
							float deltaY = target->GetCurrentPosition().y - GetCurrentPosition().y;
							sf::Vector2f vel = sf::Vector2f(deltaX, deltaY);
							sf::Vector2f starting_position = sf::Vector2f(GetCurrentPosition().x + GetCurrentDimensions().x / 2.0f - ((RigidBody*)projectiles[i])->GetCurrentDimensions().x / 2.0f, GetCurrentPosition().y + GetCurrentDimensions().y / 2.0f - ((RigidBody*)projectiles[i])->GetCurrentDimensions().y / 2.0f);
							float length = sqrt(deltaX * deltaX + deltaY * deltaY);

							if (length != 0) {
								vel.x = vel.x / length;
								vel.y = vel.y / length;
							}

							projectiles[i]->Fire(current_time, starting_position, vel * 4.0f);
							projectiles[i]->ExcludeFromCollision(GameLibrary::Singleton<World>::Get()->ENTITY_TYPE_DRONE);

							time_of_last_firing = current_time;
							firing_projectile_sound.play();

							break;
						}
					}
				}
			} else {
				SetVelocity(0.0f, 0.0f);
			}
		}
	}
}

void Drone::UpdateProjectiles(sf::Int64 curr_time, sf::Int64 frame_delta) {
	for (int i = 0; i < (int)(projectiles.size()); i++) {
		if (projectiles[i]->is_active) {
			((RigidBody*)projectiles[i])->Update(frame_delta);
			projectiles[i]->UpdateProjectile(curr_time);
		}
	}
}

void Drone::DrawProjectiles(sf::Vector2f camera_position, sf::Int64 curr_time) {
	for (int i = 0; i < (int)(projectiles.size()); i++) {
		projectiles[i]->Draw(camera_position, curr_time);
	}
}

void Drone::Draw(sf::Vector2f camera_position) {
	rectangle_shape.setPosition(sf::Vector2f(GetCurrentPosition().x - camera_position.x, GetCurrentPosition().y - camera_position.y));
	render_window->draw(rectangle_shape);

#ifdef _DEBUG
	sf::Color base_color(sf::Color::Blue);
	if (is_aggroed) {
		base_color = sf::Color::Red;
	}
	sf::Color circle_color(base_color.r, base_color.g, base_color.b, 65);
	sf::CircleShape aggro_circle(aggro_radius);
	aggro_circle.setFillColor(circle_color);
	aggro_circle.setPosition(sf::Vector2f(GetCurrentPosition().x + (GetCurrentDimensions().x / 2) - (aggro_radius) - camera_position.x, GetCurrentPosition().y + (GetCurrentDimensions().y / 2) - (aggro_radius) - camera_position.y));
	render_window->draw(aggro_circle);
#endif
}