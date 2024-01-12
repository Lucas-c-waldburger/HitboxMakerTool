#pragma once
#include "App.h"
#include <iostream>
#include <SDL_mixer.h>

namespace Timing
{

	struct Timer
	{
		Uint64 end = 0;
		int count = 0;

		void set(double music_duration);
		void update();
		void reset();
		bool need_reset(double music_pos);

		void start_timing(double music_duration);

		Uint64 duration;
	};

	inline Timer timer{};
};

