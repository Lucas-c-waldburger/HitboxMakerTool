#pragma once
#include "SDL.h"
#include <iostream>


namespace Utils
{


	// safely access an sdl_point ptr to pass through sdl functions
	struct PPoint
	{
		~PPoint();
		const SDL_Point* operator=(const SDL_Point& p);
		const SDL_Point* operator=(const SDL_Point* p);
		operator const SDL_Point* ();

	private:
		SDL_Point* ppt = nullptr;
	};


	//struct MouseCoords
	//{
	//	const SDL_Point get();
	//private:
	//	SDL_Point m_point;
	//};

	//inline static MouseCoords mouse_coords{};
};

