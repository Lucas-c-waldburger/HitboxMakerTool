#include "Controller.h"

Controller::Controller() : pController(nullptr), pJoystick(nullptr)
{
    if 
    ( 
        !(pController = findController()) ||
        !(pJoystick = SDL_GameControllerGetJoystick(pController)) ||
         (joystickID = SDL_JoystickInstanceID(pJoystick)) < 0
    )
    {
        std::string err = SDL_GetError();
        throw std::runtime_error(err);
    }
}


SDL_GameController* Controller::findController()
{
    for (int i = 0; i < SDL_NumJoysticks(); i++)
    {
        if (SDL_IsGameController(i))
            return SDL_GameControllerOpen(i);
    }

    return nullptr;
}

