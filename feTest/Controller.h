#pragma once
#include "Texture.h"
#include <stdexcept>


class Controller
{
public:
	Controller();


private:
	SDL_GameController* pController;
	SDL_Joystick* pJoystick;
	SDL_JoystickID joystickID;

	static SDL_GameController* findController();
};

