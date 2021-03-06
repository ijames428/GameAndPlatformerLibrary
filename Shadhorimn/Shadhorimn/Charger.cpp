using namespace std;
#include <iostream>
#include "Charger.h"
#define PI 3.14159265

Charger::Charger(sf::RenderWindow *window, sf::Vector2f position, sf::Vector2f dimensions, bool subject_to_gravity) : Creature::Creature(window, position, dimensions, subject_to_gravity) {
	SetEntityType(GameLibrary::ENTITY_TYPE_CHARGER);
	starting_hit_points = 20;
	hit_points = starting_hit_points;

	jump_power = 1.0f;
	aggro_radius = 200.0f;
	is_charging = false;
	attack_radius = 75.0f;

	time_of_last_attack = 0;
	duration_of_attack = 1000;
	time_between_attacks = 1500;

	HitBox = new RigidBody(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(40.0f, 10.0f), false, false);
	HitBox->SetEntityType(GameLibrary::ENTITY_TYPE_HIT_BOX);

	WallDetector = new RigidBody(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(5.0f, dimensions.y - 5.0f), false, false);
	WallDetector->DisableCollision();
	WallDetector->SetEntityType(GameLibrary::ENTITY_TYPE_WALL_DETECTOR);
	WallDetector->ExcludeFromCollision(GetEntityType());
	WallDetector->ExcludeFromCollision(HitBox->GetEntityType());
	WallDetector->ExcludeFromCollision(GameLibrary::ENTITY_TYPE_PROJECTILE);
	WallDetector->ExcludeFromCollision(GameLibrary::ENTITY_TYPE_END_OF_THE_GAME);
	WallDetector->ExcludeFromCollision(GameLibrary::ENTITY_TYPE_BOSS_TRIGGER);

	movement_speed = 1.0f;
	charge_speed = 7.0f;
	charge_speed_second_stage = 10.0f;

	charge_velocity = sf::Vector2f(0.0f, 0.0f);

	sf::RectangleShape shape(dimensions);
	shape.setFillColor(sf::Color::White);
	shape.setPosition(position);

	rectangle_shape = shape;

	//target = GameLibrary::Singleton<World>::Get()->main_character;

	for (int i = 0; i < 5; i++) {
		projectiles.push_back(new Projectile(window, position, sf::Vector2f(20.0f, 20.0f), false));
		projectiles[i]->ExcludeFromCollision(GetEntityType());
		projectiles[i]->ExcludeFromCollision(HitBox->GetEntityType());
		projectiles[i]->ExcludeFromCollision(GameLibrary::ENTITY_TYPE_PROJECTILE);
		projectiles[i]->ExcludeFromCollision(GameLibrary::ENTITY_TYPE_END_OF_THE_GAME);
		projectiles[i]->ExcludeFromCollision(GameLibrary::ENTITY_TYPE_BOSS_TRIGGER);
	}

	if (!hitting_wall_buffer.loadFromFile("Sound/charger_hitting_wall.wav")) {
		throw exception("Sound file not found");
	} else {
		hitting_wall_sound.setBuffer(hitting_wall_buffer);
		hitting_wall_sound.setVolume(50 * (GameLibrary::Singleton<GameLibrary::Settings>().Get()->effects_volume / 100.0f));
		hitting_wall_sound.setLoop(false);
	}

	if (!hitting_player_buffer.loadFromFile("Sound/charger_hitting_player.wav")) {
		throw exception("Sound file not found");
	} else {
		hitting_player_sound.setBuffer(hitting_player_buffer);
		hitting_player_sound.setVolume(50 * (GameLibrary::Singleton<GameLibrary::Settings>().Get()->effects_volume / 100.0f));
		hitting_player_sound.setLoop(false);
	}
}

void Charger::Update(sf::Int64 curr_time, sf::Int64 delta_time) {
	Creature::Update(curr_time, delta_time);

	for (int i = 0; i < (int)(projectiles.size()); i++) {
		if (projectiles[i]->is_active) {
			projectiles[i]->Update(curr_time, delta_time);
		}
	}

	if (hit_points > 0) {
		if (hit_stun_start_time + hit_stun_duration <= current_time) {
			UnlockFacingDirection();

			sf::Vector2f knock_back = sf::Vector2f();
			knock_back.x = 2.0f;
			knock_back.y = 6.0f;

			if (IsFacingRight()) {
				HitBox->SetCurrentPosition(GetCurrentPosition().x + GetCurrentDimensions().x, GetCurrentPosition().y);
				WallDetector->SetCurrentPosition(GetCurrentPosition().x + GetCurrentDimensions().x, GetCurrentPosition().y);
			} else {
				knock_back.x *= -1.0f;
				HitBox->SetCurrentPosition(GetCurrentPosition().x - HitBox->GetCurrentDimensions().x, GetCurrentPosition().y);
				WallDetector->SetCurrentPosition(GetCurrentPosition().x - WallDetector->GetCurrentDimensions().x + GetCurrentDimensions().x, GetCurrentPosition().y);
			}

			HitBox->Update(0, 0);
			WallDetector->Update(0, 0);

			if (is_charging) {
				SetVelocity(charge_velocity);

				knock_back.x = 4.0f * (knock_back.x < 0.0f ? -1.0f : 1.0f);
				knock_back.y = 10.0f;

				std::vector<RigidBody*> hit_objects = WallDetector->GetCollidersRigidBodyIsCollidingWith();

				for (int i = 0; i < (int)hit_objects.size(); i++) {
					if (hit_objects[i]->GetEntityType() == GameLibrary::ENTITY_TYPE_PLATFORM) {
						knock_back.x = -knock_back.x;
						TakeHit(0, 3000, knock_back);
						if (IsInSecondStage()) {
							FireSecondStageProjectiles();
						}
						//GameLibrary::Singleton<World>::Get()->ScreenShake(2.0f);
						hitting_wall_sound.play();
						is_charging = false;
					} else if (hit_objects[i]->GetEntityType() == GameLibrary::ENTITY_TYPE_PLAYER_CHARACTER) {
						if (!((Creature*)(hit_objects[i]))->IsInvincible()) {
							((Creature*)(hit_objects[i]))->TakeHit(2, 1000, knock_back);
							knock_back.x = -knock_back.x;
							TakeHit(0, 1500, knock_back);
							if (IsInSecondStage()) {
								FireSecondStageProjectiles();
							}
							//GameLibrary::Singleton<World>::Get()->ScreenShake(2.0f);
							hitting_player_sound.play();
						}

						is_charging = false;
					}
				}
			} else {
				StartCharge();
			}
		} else {
			LockFacingDirection();
		}
	}
}

void Charger::FireSecondStageProjectiles() {
	sf::Vector2f starting_position = sf::Vector2f(GetCurrentPosition().x + GetCurrentDimensions().x / 2.0f, GetCurrentPosition().y + GetCurrentDimensions().y / 4.0f);
	float projectile_speed = 6.0f;
	float angled_speed = 4.24f;

	projectiles[0]->Fire(current_time, starting_position, sf::Vector2f(-projectile_speed, 0.0f));
	projectiles[1]->Fire(current_time, starting_position, sf::Vector2f(-angled_speed, -angled_speed));
	projectiles[2]->Fire(current_time, starting_position, sf::Vector2f(0.0f, -projectile_speed));
	projectiles[3]->Fire(current_time, starting_position, sf::Vector2f(angled_speed, -angled_speed));
	projectiles[4]->Fire(current_time, starting_position, sf::Vector2f(projectile_speed, 0.0f));

	for (int i = 0; i < (int)(projectiles.size()); i++) {
		projectiles[i]->ExcludeFromCollision(GetEntityType());
		projectiles[i]->ExcludeFromCollision(HitBox->GetEntityType());
	}
}

bool Charger::IsInSecondStage() {
	return hit_points <= starting_hit_points / 3;
}

void Charger::StartCharge() {
	is_charging = true;
	charge_velocity.y = 0.0f;
	float charge_speed_by_stage = charge_speed;

	if (IsInSecondStage()) {
		charge_speed_by_stage = charge_speed_second_stage;
	}

	if (target->GetCurrentPosition().x > GetCurrentPosition().x) {
		charge_velocity.x = charge_speed_by_stage;
		WallDetector->SetCurrentPosition(GetCurrentPosition().x + GetCurrentDimensions().x, WallDetector->GetCurrentPosition().y);
	} else if (target->GetCurrentPosition().x < GetCurrentPosition().x) {
		charge_velocity.x = -charge_speed_by_stage;
		WallDetector->SetCurrentPosition(GetCurrentPosition().x - WallDetector->GetCurrentDimensions().x, WallDetector->GetCurrentPosition().y);
	}
}

void Charger::DrawProjectiles(sf::Vector2f camera_position, sf::Int64 curr_time) {
	for (int i = 0; i < (int)(projectiles.size()); i++) {
		projectiles[i]->Draw(camera_position, curr_time);
	}
}

void Charger::Draw(sf::Vector2f camera_position) {
	rectangle_shape.setPosition(sf::Vector2f(GetCurrentPosition().x - camera_position.x, GetCurrentPosition().y - camera_position.y));
	if (IsInSecondStage()) {
		rectangle_shape.setFillColor(sf::Color::Red);
	}
	render_window->draw(rectangle_shape);
}