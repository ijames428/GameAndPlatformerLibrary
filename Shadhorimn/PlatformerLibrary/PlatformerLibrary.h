// PlatformerLibrary.h - Contains declaration of Function class  
#pragma once  

#ifdef PLATFORMERLIBRARY_EXPORTS  
#define PLATFORMERLIBRARY_API __declspec(dllexport)   
#else  
#define PLATFORMERLIBRARY_API __declspec(dllimport)   
#endif  

namespace PlatformerLibrary
{
	// This class is exported from the PlatformerLibrary.dll  
	class Functions
	{
	public:
		static PLATFORMERLIBRARY_API void Test();
	};
}