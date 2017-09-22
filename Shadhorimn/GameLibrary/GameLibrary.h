// GameLibrary.h - Contains declaration of Function class  
#pragma once  

#ifdef GAMELIBRARY_EXPORTS  
#define GAMELIBRARY_API __declspec(dllexport)   
#else  
#define GAMELIBRARY_API __declspec(dllimport)   
#endif  

namespace GameLibrary
{
	// This class is exported from the GameLibrary.dll  
	class Functions
	{
	public:
		// Returns a + b  
		static GAMELIBRARY_API double Add(double a, double b);

		// Returns a * b  
		static GAMELIBRARY_API double Multiply(double a, double b);

		// Returns a + (a * b)  
		static GAMELIBRARY_API double AddMultiply(double a, double b);
	};
}