using namespace std;
#include <iostream>
#include "Gunner.h"
#include "World.h"
#include "AssetManager.h"
#include "Settings.h"
#define PI 3.14159265

Gunner::Gunner(sf::RenderWindow *window, sf::Vector2f position, sf::Vector2f dimensions, bool subject_to_gravity) : Creature::Creature(window, position, dimensions, subject_to_gravity) {
	SetEntityType(GameLibrary::Singleton<World>::Get()->ENTITY_TYPE_GUNNER);
	hit_points = 2;

	jump_power = 1.0f;
	aggro_radius = 500.0f;
	is_aggroed = false;
	fire_duration = 200;
	movement_speed = 1.0f;
	gunner_color = sf::Color::Green;

	idle_sprite_scale = 0.12f;
	//idle_texture.loadFromFile("Images/Kaltar_Idle.png");
	idle_texture = *GameLibrary::Singleton<AssetManager>().Get()->GetTexture("Images/Kaltar_Idle.png");
	idle_sprite = sf::Sprite(idle_texture);
	//idle_sprite = sf::Sprite(GameLibrary::Singleton<AssetManager>().Get()->GetTexture("Images/Kaltar_Idle.png"));
	idle_sprite.setScale(idle_sprite_scale, idle_sprite_scale);
	idle_sprite.setColor(gunner_color);

	running_animation = new SpriteAnimation(render_window, "Images/Kaltar_Running.png", 582, 522, 91, 9, 11, 0.12f, gunner_color);

	fire_texture = *GameLibrary::Singleton<AssetManager>().Get()->GetTexture("Images/Kaltar_Fire.png");
	//fire_texture.loadFromFile("Images/Kaltar_Fire.png");
	fire_sprite = sf::Sprite(fire_texture);
	//fire_sprite = sf::Sprite(GameLibrary::Singleton<AssetManager>().Get()->GetTexture("Images/Kaltar_Fire.png"));
	fire_sprite.setScale(idle_sprite_scale, idle_sprite_scale);
	fire_sprite.setColor(gunner_color);

	taking_damage_texture = *GameLibrary::Singleton<AssetManager>().Get()->GetTexture("Images/kaltar_taking_damage.png");
	taking_damage_sprite = sf::Sprite(taking_damage_texture);
	taking_damage_sprite.setScale(idle_sprite_scale, idle_sprite_scale);
	taking_damage_sprite.setColor(gunner_color);

	dead_on_ground_texture = *GameLibrary::Singleton<AssetManager>().Get()->GetTexture("Images/kaltar_dead_on_ground.png");
	dead_on_ground_sprite = sf::Sprite(dead_on_ground_texture);
	dead_on_ground_sprite.setScale(idle_sprite_scale, idle_sprite_scale);
	dead_on_ground_sprite.setColor(gunner_color);

	target = GameLibrary::Singleton<World>::Get()->main_character;

	time_between_firing = 1500;
	time_of_last_firing = 0;
	for (int i = 0; i < 15; i++) {
		projectiles.push_back(new Projectile(window, position, sf::Vector2f(20.0f, 20.0f), false));
		projectiles[i]->ExcludeFromCollision(GameLibrary::Singleton<World>::Get()->ENTITY_TYPE_GUNNER);
	}

	if (!firing_projectile_buffer.loadFromFile("Sound/gunner_firing.wav")) {
		throw exception("Sound file not found");
	} else {
		firing_projectile_sound.setBuffer(firing_projectile_buffer);
		firing_projectile_sound.setVolume(GameLibrary::Singleton<Settings>().Get()->effects_volume);
	}
}

void Gunner::UpdateBehavior(sf::Int64 curr_time) {
	current_time = curr_time;

	if (hit_points > 0) {
		if (hit_stun_start_time + hit_stun_duration <= current_time) {
			UnlockFacingDirection();
			is_aggroed = RigidBody::GetDistanceBetweenTwoPoints(sf::Vector2f(target->GetCurrentPosition().x + target->GetCurrentDimensions().x / 2.0f, target->GetCurrentPosition().y + target->GetCurrentDimensions().y / 2.0f), sf::Vector2f(GetCurrentPosition().x, GetCurrentPosition().y)) < aggro_radius;

			if (is_aggroed) {
				if (target->GetCurrentPosition().x > GetCurrentPosition().x) {
					SetVelocity(movement_speed, GetVelocity().y);
				} else if (target->GetCurrentPosition().x < GetCurrentPosition().x) {
					SetVelocity(-movement_speed, GetVelocity().y);
				}

				std::vector<Projectile*> shotgun_projectiles_to_be_fired = std::vector<Projectile*>();

				if (time_of_last_firing + time_between_firing < current_time) {
					for (int i = 0; i < (int)(projectiles.size()); i++) {
						if (!projectiles[i]->is_active) {
							shotgun_projectiles_to_be_fired.push_back(projectiles[i]);
						}

						if (shotgun_projectiles_to_be_fired.size() >= 3) {
							break;
						}
					}

					for (int i = 0; i < 3; i++) {
						float spread = 1.5f;
						sf::Vector2f vel = sf::Vector2f(6.0f, -spread + spread * i);
						sf::Vector2f starting_position = sf::Vector2f(GetCurrentPosition().x - shotgun_projectiles_to_be_fired[i]->GetCurrentDimensions().x, GetCurrentPosition().y);

						if (target->GetCurrentPosition().x > GetCurrentPosition().x) {
							starting_position.x += GetCurrentDimensions().x + shotgun_projectiles_to_be_fired[i]->GetCurrentDimensions().x;
						} else {
							vel.x *= -1.0f;
						}

						shotgun_projectiles_to_be_fired[i]->Fire(current_time, starting_position, vel);
						shotgun_projectiles_to_be_fired[i]->ExcludeFromCollision(GetEntityType());

						time_of_last_firing = current_time;
						
						firing_projectile_sound.play();
					}
				}
			} else if (!IsInTheAir()) {
				SetVelocity(0.0f, 0.0f);
			}
		} else {
			LockFacingDirection();
			rectangle_shape.setFillColor(sf::Color::Red);
		}
	}
}

void Gunner::UpdateProjectiles(sf::Int64 curr_time, sf::Int64 frame_delta) {
	for (int i = 0; i < (int)(projectiles.size()); i++) {
		if (projectiles[i]->is_active) {
			projectiles[i]->Update(frame_delta);
			projectiles[i]->UpdateProjectile(curr_time);
		}
	}
}

void Gunner::DrawProjectiles(sf::Vector2f camera_position, sf::Int64 curr_time) {
	for (int i = 0; i < (int)(projectiles.size()); i++) {
		projectiles[i]->Draw(camera_position, curr_time);
	}
}

void Gunner::Draw(sf::Vector2f camera_position) {
	if (IsFacingRight()) {
		idle_sprite.setScale(idle_sprite_scale, idle_sprite.getScale().y);
		fire_sprite.setScale(idle_sprite_scale, idle_sprite.getScale().y);
		taking_damage_sprite.setScale(idle_sprite_scale, idle_sprite.getScale().y);
		dead_on_ground_sprite.setScale(idle_sprite_scale, idle_sprite.getScale().y);
	} else {
		idle_sprite.setScale(-idle_sprite_scale, idle_sprite.getScale().y);
		fire_sprite.setScale(-idle_sprite_scale, idle_sprite.getScale().y);
		taking_damage_sprite.setScale(-idle_sprite_scale, idle_sprite.getScale().y);
		dead_on_ground_sprite.setScale(-idle_sprite_scale, idle_sprite.getScale().y);
	}

	if (IsFacingRight() != running_animation->IsFacingRight()) {
		running_animation->Flip();
	}

	if (hit_points <= 0) {
		if (IsFacingRight()) {
			taking_damage_sprite.setPosition(sf::Vector2f(GetCurrentPosition().x - camera_position.x, GetCurrentPosition().y - camera_position.y));
			dead_on_ground_sprite.setPosition(sf::Vector2f(GetCurrentPosition().x - camera_position.x, GetCurrentPosition().y - camera_position.y));
		}
		else {
			taking_damage_sprite.setPosition(sf::Vector2f(GetCurrentPosition().x + GetCurrentDimensions().x - camera_position.x, GetCurrentPosition().y - camera_position.y));
			dead_on_ground_sprite.setPosition(sf::Vector2f(GetCurrentPosition().x + GetCurrentDimensions().x - camera_position.x, GetCurrentPosition().y - camera_position.y));
		}

		if (IsInTheAir()) {
			render_window->draw(taking_damage_sprite);
		}
		else {
			render_window->draw(dead_on_ground_sprite);
		}
	} else if (hit_stun_start_time + hit_stun_duration > current_time) {
		if (IsFacingRight()) {
			taking_damage_sprite.setPosition(sf::Vector2f(GetCurrentPosition().x - camera_position.x, GetCurrentPosition().y - camera_position.y));
		}
		else {
			taking_damage_sprite.setPosition(sf::Vector2f(GetCurrentPosition().x + GetCurrentDimensions().x - camera_position.x, GetCurrentPosition().y - camera_position.y));
		}
		render_window->draw(taking_damage_sprite);
	} else if (time_of_last_firing + fire_duration > current_time) {
		if (IsFacingRight()) {
			fire_sprite.setPosition(sf::Vector2f(GetCurrentPosition().x - camera_position.x, GetCurrentPosition().y - camera_position.y));
		} else {
			fire_sprite.setPosition(sf::Vector2f(GetCurrentPosition().x + GetCurrentDimensions().x - camera_position.x, GetCurrentPosition().y - camera_position.y));
		}
		render_window->draw(fire_sprite);
	} else if (GetVelocity().x == 0) {
		if (IsFacingRight()) {
			idle_sprite.setPosition(sf::Vector2f(GetCurrentPosition().x - camera_position.x, GetCurrentPosition().y - camera_position.y));
		}
		else {
			idle_sprite.setPosition(sf::Vector2f(GetCurrentPosition().x + GetCurrentDimensions().x - camera_position.x, GetCurrentPosition().y - camera_position.y));
		}
		render_window->draw(idle_sprite);
	} else {
		running_animation->Draw(camera_position, sf::Vector2f(GetCurrentPosition().x + GetCurrentDimensions().x / 2.0f, GetCurrentPosition().y + GetCurrentDimensions().y / 2.0f));
	}

#ifdef _DEBUG
	sf::Color base_color(sf::Color::Blue);
	if (is_aggroed) {
		base_color = sf::Color::Red;
	}
	sf::Color circle_color(base_color.r, base_color.g, base_color.b, 65);
	sf::CircleShape aggro_circle(aggro_radius);
	aggro_circle.setFillColor(circle_color);
	aggro_circle.setPosition(sf::Vector2f(GetCurrentPosition().x + (GetCurrentDimensions().x / 2) - (aggro_radius)-camera_position.x, GetCurrentPosition().y + (GetCurrentDimensions().y / 2) - (aggro_radius)-camera_position.y));
	render_window->draw(aggro_circle);
#endif
}