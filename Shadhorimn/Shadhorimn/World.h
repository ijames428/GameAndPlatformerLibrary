#pragma once

using namespace std;
//using namespace PlatformerLibrary;
//#include "..\GameLibrary\Singleton.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include "PlayerCharacter.h"
#include "..\PlatformerLibrary\Checkpoint.h"
#include "..\PlatformerLibrary\EndOfTheGame.h"
#include "..\PlatformerLibrary\Platform.h"
//#include "..\GameLibrary\Settings.h"
#include "Charger.h"
#include "..\GameLibrary\Camera.h"
#include "Gunner.h"
#include "Drone.h"
#include "Grunt.h"

class World {
private:
	sf::Text loading_text;
	sf::Int64 time_of_death;
	sf::Int64 time_before_continue_screen_appears;
	float door_opening_volume;
	sf::Sound door_opening_sound;
	sf::SoundBuffer door_opening_buffer;
	sf::Sound sound_stalagtite_landing;
	sf::SoundBuffer buffer_stalagtite_landing;
	sf::Vector2f screen_shake_amount;
	sf::Vector2f camera_position;
	sf::Vector2f viewport_position_with_screen_shake;
	sf::Vector2f parallax_background_viewport_position;
	bool player_is_in_combat;
	PlatformerLibrary::EndOfTheGame* end_of_the_game_trigger;
	bool go_to_credits = false;
	bool player_beat_the_game = false;
	PlatformerLibrary::Checkpoint* starting_checkpoint;
	PlatformerLibrary::Checkpoint* current_checkpoint;
	sf::Font ringbearer_font = sf::Font();
	sf::Text continue_text;
	sf::Text lives_counter_text;
	sf::Text paused_text;
	int game_over_screen_sprite_transparency;
	int end_game_fade_transparency;
	sf::Texture level_art_texture;
	sf::Sprite level_art_sprite;
	sf::Texture game_over_texture;
	sf::Sprite game_over_sprite;
	sf::Texture blank_screen_texture;
	sf::Sprite blank_screen_sprite;
	sf::Texture hit_point_texture;
	sf::Texture parallax_background_texture;
	sf::Sprite parallax_background_sprite;
	sf::Texture foreground_behind_layer_texture;
	sf::Sprite foreground_behind_layer_sprite;
	std::vector<sf::Sprite> players_hit_point_sprites = std::vector<sf::Sprite>();
	std::vector<sf::Sprite> chargers_hit_point_sprites = std::vector<sf::Sprite>();
	sf::Int64 current_time;
	bool screen_shaking;
	sf::Int64 screen_shake_start_time;
	sf::Int64 screen_shake_duration;
	float screen_shake_magnitude;
	GameLibrary::Camera* camera;
	sf::RenderWindow* render_window;
	std::vector<PlatformerLibrary::Checkpoint*> checkpoints = std::vector<PlatformerLibrary::Checkpoint*>();
	std::vector<PlatformerLibrary::Platform*> platforms = std::vector<PlatformerLibrary::Platform*>();
	std::vector<Gunner*> gunners = std::vector<Gunner*>();
	std::vector<Grunt*> grunts = std::vector<Grunt*>();
	std::vector<Drone*> drones = std::vector<Drone*>();
	PlatformerLibrary::RigidBody* boss_health_trigger;
	PlatformerLibrary::Platform* end_of_game_door;
	PlatformerLibrary::Platform* stalagtite;
	int stalagtite_hit_points = 3;
	bool fighting_boss;
	Charger* charger;
	int grid_width = 100;
	int grid_height = 100;
	int grid_depth = 10;
	int cell_width = 100;
	int cell_height = 100;
	float combat_music_range;
	std::vector<std::vector<std::vector<PlatformerLibrary::RigidBody*>>> Grid = std::vector<std::vector<std::vector<PlatformerLibrary::RigidBody*>>>(grid_width, std::vector<std::vector<PlatformerLibrary::RigidBody*>>(grid_height, std::vector<PlatformerLibrary::RigidBody*>()));
public:
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
	int starting_number_of_lives = 2;
	int current_number_of_lives = 2;
	bool paused;
	PlayerCharacter* main_character;
	World();
	void Init(sf::RenderWindow* window, GameLibrary::Camera* cam, PlayerCharacter* character);
	void Update(sf::Int64 current_time, sf::Int64 frame_delta);
	void ScreenShake(float magnitude);
	void SetCurrentCheckPoint(PlatformerLibrary::Checkpoint* cp);
	void EndTheGame();
	bool DidThePlayerBeatTheGame();
	bool ShouldGoToCredits();
	bool IsPlayerInCombat();
	void BuildReleaseLevel();
	bool IsObjectInUpdateRange(PlatformerLibrary::RigidBody* rb);
	bool IsNewGame();
	void StartNewGame();
	void HitStalagtite();
	void PlayerDied();
	bool CanContinue();
	void UpdateLoadingText(sf::String loading_text);
};