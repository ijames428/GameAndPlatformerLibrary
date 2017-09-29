#pragma once

#ifndef GRID_HANDLER_H
#define GRID_HANDLER_H

#ifdef PLATFORMERLIBRARY_EXPORTS  
#define PLATFORMERLIBRARY_API __declspec(dllexport)   
#else  
#define PLATFORMERLIBRARY_API __declspec(dllimport)   
#endif  

using namespace std;
#include "..\GameLibrary\Singleton.h"
#include <SFML/Graphics.hpp>
#include "Checkpoint.h"
#include "EndOfTheGame.h"
#include "Platform.h"

namespace PlatformerLibrary
{
	class GridHandler {
	private:
		int grid_width = 100;
		int grid_height = 100;
		int grid_depth = 10;
		int cell_width = 100;
		int cell_height = 100;
		float combat_music_range;
		std::vector<std::vector<std::vector<RigidBody*>>> Grid = std::vector<std::vector<std::vector<RigidBody*>>>(grid_width, std::vector<std::vector<RigidBody*>>(grid_height, std::vector<RigidBody*>()));
	public:
		PLATFORMERLIBRARY_API GridHandler();
		PLATFORMERLIBRARY_API void AddRigidBodyToGrid(RigidBody* rb);
		PLATFORMERLIBRARY_API void MoveRigidBodyInGrid(RigidBody* rb);
		PLATFORMERLIBRARY_API std::vector<RigidBody*> GetObjectsInGridLocation(int grid_x, int grid_y);
	};
}

#endif