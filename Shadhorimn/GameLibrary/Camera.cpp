#pragma once

using namespace std;
#include "stdafx.h"
#include <iostream>
#include "Camera.h"
//#include "..\PlatformerLibrary\Test.h"
#include "..\GameLibrary\GameLibrary.h"

namespace GameLibrary
{
	Camera::Camera(sf::Vector2f position, sf::Vector2f dimensions) {
		viewport_position = position;
		viewport_dimensions = dimensions;

		double test_double = GameLibrary::Functions::Add(2.0, 3.0);
		//Test test = Test();
		//test.test_int = 70;
	}
}