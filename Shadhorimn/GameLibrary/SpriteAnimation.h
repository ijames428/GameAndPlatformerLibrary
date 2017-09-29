#ifdef GAMELIBRARY_EXPORTS  
#define GAMELIBRARY_API __declspec(dllexport)   
#else  
#define GAMELIBRARY_API __declspec(dllimport)   
#endif 

#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H 

using namespace std;
#include <SFML/Graphics.hpp>
#include "AssetManager.h" 
#include "Singleton.h"

namespace GameLibrary
{
	class SpriteAnimation {
	private:
		int current_frame;
		bool facing_right;
		int sprite_frame_height;
		int sprite_frame_width;
		int number_of_frames;
		int number_of_columns;
		int number_of_rows;
		float sprite_scale;
		sf::Texture* texture;
		sf::Sprite* sprite;
		sf::IntRect texture_rect;
	public:
		sf::RenderWindow *render_window;
		GAMELIBRARY_API SpriteAnimation(sf::RenderWindow* window, std::string file_path_and_name, int frame_width, int frame_height, int total_frames, int columns_count, int rows_count, float scale, sf::Color color);
		GAMELIBRARY_API void Draw(sf::Vector2f camera_position, sf::Vector2f parent_object_mid_position);
		GAMELIBRARY_API void Flip();
		GAMELIBRARY_API bool IsFacingRight();
		GAMELIBRARY_API void SetColor(sf::Color new_color);
	};
}

#endif