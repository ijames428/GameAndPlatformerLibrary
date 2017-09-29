#ifndef CONSTANTS_H
#define CONSTANTS_H

#ifdef GAMELIBRARY_EXPORTS  
#define GAMELIBRARY_API __declspec(dllexport)   
#else  
#define GAMELIBRARY_API __declspec(dllimport)   
#endif  

#include <SFML/System.hpp>

namespace GameLibrary
{
	const int ENTITY_TYPE_CHARGER = 0;
	const int ENTITY_TYPE_CHECKPOINT = 1;
	const int ENTITY_TYPE_CREATURE = 2;
	const int ENTITY_TYPE_DRONE = 3;
	const int ENTITY_TYPE_END_OF_THE_GAME = 4;
	const int ENTITY_TYPE_GRUNT = 5;
	const int ENTITY_TYPE_GUNNER = 6;
	const int ENTITY_TYPE_PLATFORM = 7;
	const int ENTITY_TYPE_PLAYER_CHARACTER = 8;
	const int ENTITY_TYPE_PROJECTILE = 9;
	const int ENTITY_TYPE_RIGID_BODY = 10;
	const int ENTITY_TYPE_HIT_BOX = 11;
	const int ENTITY_TYPE_WALL_DETECTOR = 12;
	const int ENTITY_TYPE_STALAGTITE = 13;
	const int ENTITY_TYPE_BOSS_TRIGGER = 14;
}

#endif