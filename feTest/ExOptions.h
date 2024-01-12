#pragma once
#include "SDL.h"
#include "Utils.h"
#include <iostream>

using namespace Utils;

struct ExOptions
{
	struct Scale
	{
		struct DimensionPair
		{
			DimensionPair(unsigned perW, unsigned perH);
			double percentWidth, percentHeight;
		};

		Scale();
		Scale(const DimensionPair&& dp);
		Scale(int x_scale, int y_scale);

		const SDL_Rect* get_scaled(const SDL_Rect& orig);
		Scale& operator=(const DimensionPair&& dp);

	private:
		DimensionPair dimPair;
		SDL_Rect scaledRect;
	};

	Scale scale = { {100, 100} };
	double rotation_angle = 0.0;
	SDL_RendererFlip flip_type = SDL_FLIP_NONE;
	PPoint rotation_center;
};

