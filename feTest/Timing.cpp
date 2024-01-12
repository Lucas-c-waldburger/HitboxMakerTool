#include "Timing.h"


void Timing::Timer::set(double music_duration)
{
	end = SDL_GetTicks64() + music_duration;
	count = -1;
}

void Timing::Timer::update()
{
	count = duration - (end - SDL_GetTicks64());
}

void Timing::Timer::reset()
{
	end = SDL_GetTicks64() + duration;
}

void Timing::Timer::start_timing(double music_duration)
{
	duration = static_cast<Uint64>(music_duration);
	end = SDL_GetTicks64() + duration;
}
