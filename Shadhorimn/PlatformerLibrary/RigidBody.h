#pragma once

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

// RigidBody.h - Contains declaration of Function class  

#ifdef PLATFORMERLIBRARY_EXPORTS  
#define PLATFORMERLIBRARY_API __declspec(dllexport)   
#else  
#define PLATFORMERLIBRARY_API __declspec(dllimport)   
#endif 

using namespace std;

#include <SFML/Graphics.hpp>
#include "..\GameLibrary\Singleton.h"
#include "..\GameLibrary\Constants.h"

namespace PlatformerLibrary
{
	class RigidBody {
	protected:
		sf::Int64 current_time;
	private:
		int entity_type;
		sf::Vector2f velocity;
		sf::Vector2f current_position;
		sf::Vector2f current_dimensions;
		sf::Vector2f future_position;
		sf::Vector2f future_dimensions;
		sf::Vector2f past_position;
		sf::Vector2f past_dimensions;
		sf::Vector2i grid_top_left;
		sf::Vector2i grid_bot_right;
		float gravity_acceleration;
		float terminal_velocity;
		float weight;
		bool gravity_enabled;
		bool collision_enabled;
		bool only_collide_with_platforms;
		bool in_the_air;
		int id = rand();
		bool facing_right;
		bool facing_right_when_hit;
		bool lock_facing_direction_when_hit;
		std::vector<int> entities_excluded_from_collision;
		PLATFORMERLIBRARY_API bool AreTheRigidBodiesCollidingHorizontally(RigidBody* rb1, RigidBody* rb2, bool just_check_no_response = false);
		PLATFORMERLIBRARY_API bool AreTheRigidBodiesCollidingVertically(RigidBody* rb1, RigidBody* rb2, bool just_check_no_response = false);
	public:
		PLATFORMERLIBRARY_API void OnlyCollideWithPlatforms(bool only_colliding_with_platforms_now);
		PLATFORMERLIBRARY_API bool IsFacingRight();
		PLATFORMERLIBRARY_API bool IsInTheAir();
		PLATFORMERLIBRARY_API bool WasFacingRightWhenHit();
		PLATFORMERLIBRARY_API void SetFacingRightWhenHit(bool facing_right_when_hit);
		PLATFORMERLIBRARY_API void SetInTheAir(bool in_the_air_now);
		PLATFORMERLIBRARY_API sf::Vector2f GetVelocity();
		PLATFORMERLIBRARY_API sf::Vector2f GetCurrentPosition();
		PLATFORMERLIBRARY_API sf::Vector2f GetCurrentDimensions();
		PLATFORMERLIBRARY_API std::vector<int> GetEntitiesExcludedFromCollision();
		PLATFORMERLIBRARY_API bool WillOnlyCollidingWithPlatforms();
		PLATFORMERLIBRARY_API int GetEntityType();
		PLATFORMERLIBRARY_API void EnableCollision();
		PLATFORMERLIBRARY_API void DisableCollision();
		PLATFORMERLIBRARY_API void EnableGravity();
		PLATFORMERLIBRARY_API void DisableGravity();
		PLATFORMERLIBRARY_API void SetVelocity(sf::Vector2f new_velocity);
		PLATFORMERLIBRARY_API void SetVelocity(float x, float y);
		PLATFORMERLIBRARY_API void SetCurrentPosition(sf::Vector2f new_position);
		PLATFORMERLIBRARY_API void SetCurrentPosition(float x, float y);
		PLATFORMERLIBRARY_API void SetEntityType(int new_entity_type);
		PLATFORMERLIBRARY_API int GetID();
		PLATFORMERLIBRARY_API int GetGridTopLeftX();
		PLATFORMERLIBRARY_API int GetGridTopLeftY();
		PLATFORMERLIBRARY_API int GetGridBotRightX();
		PLATFORMERLIBRARY_API int GetGridBotRightY();
		PLATFORMERLIBRARY_API void SetGridTopLeftX(int new_value);
		PLATFORMERLIBRARY_API void SetGridTopLeftY(int new_value);
		PLATFORMERLIBRARY_API void SetGridBotRightX(int new_value);
		PLATFORMERLIBRARY_API void SetGridBotRightY(int new_value);
		PLATFORMERLIBRARY_API void LockFacingDirection();
		PLATFORMERLIBRARY_API void UnlockFacingDirection();
		PLATFORMERLIBRARY_API bool IsFacingDirectionLocked();
		PLATFORMERLIBRARY_API RigidBody(sf::Vector2f position, sf::Vector2f dimensions, bool subject_to_gravity = false, bool subject_to_collision = true);
		PLATFORMERLIBRARY_API virtual void Update(sf::Int64 curr_time, sf::Int64 delta_time);
		PLATFORMERLIBRARY_API void ChangeFutureValuesAndVelocityBasedOnCollisions();
		PLATFORMERLIBRARY_API std::vector<RigidBody*> GetCollidersRigidBodyIsCollidingWith();
		PLATFORMERLIBRARY_API static float GetDistanceBetweenTwoPoints(sf::Vector2f point_a, sf::Vector2f point_b);
		PLATFORMERLIBRARY_API void ExcludeFromCollision(int ent_typ);
		PLATFORMERLIBRARY_API void ClearEntitiesExcludedFromCollision();
	};
}

#endif