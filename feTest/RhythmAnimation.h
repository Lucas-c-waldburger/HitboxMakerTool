#pragma once
#include "RhythmDisplay.h"
#include "Sounds.h"
#include <vector>


namespace rhythm_anim
{
	int get_x_pos(Uint64 timer_count, Uint64 loop_duration);


	static constexpr int MOVING_RECT_W = 150;
	static constexpr int MOVING_RECT_H = 150;
	static inline SDL_Rect moving_rect = { 0 - (MOVING_RECT_W / 2), (SCREEN_HEIGHT / 2) - (MOVING_RECT_H / 2), MOVING_RECT_W, MOVING_RECT_H };

	void move_anim_rect(Uint64 timer_count, Uint64 loop_duration);

	void draw_anim_rects(SDL_Renderer* renderer);

	





};

