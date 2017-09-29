#ifndef SETTINGS_H
#define SETTINGS_H

#ifdef GAMELIBRARY_EXPORTS  
#define GAMELIBRARY_API __declspec(dllexport)   
#else  
#define GAMELIBRARY_API __declspec(dllimport)   
#endif  

using namespace std;
#include <SFML/Graphics.hpp>

namespace GameLibrary
{
	class Settings {
	public:
		float music_volume;
		float effects_volume;
		GAMELIBRARY_API Settings();
	};
}

#endif