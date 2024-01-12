#pragma once
#include "App.h"
#include <vector>
#include <algorithm>


namespace rhythm_display
{

	bool Init();

	struct Line 
	{ 
		constexpr inline Line(int x1, int y1, int x2, int y2) : p1{ x1, y1 }, p2{ x2, y2 } {};
		SDL_Point p1, p2; 
	};

	static constexpr SDL_Point SCREEN_CENTER = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

	static constexpr Line CENTER_LINE = { 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 };

	static constexpr int TARGET_RECT_W = 160;
	static constexpr int TARGET_RECT_H = 160;

	static constexpr SDL_Rect TARGET_RECT_1 = { SCREEN_CENTER.x - (TARGET_RECT_W / 2), 
											    SCREEN_CENTER.y - (TARGET_RECT_H / 2), 
											    TARGET_RECT_W,
											    TARGET_RECT_H };

	static constexpr SDL_Rect TARGET_RECT_2 = { SCREEN_CENTER.x - (TARGET_RECT_W / 2),
												SCREEN_CENTER.y - (TARGET_RECT_H / 2),
												TARGET_RECT_W,
												TARGET_RECT_H };

	static std::vector<SDL_Rect> target_display_rects;
	static std::vector<Line> lines_in_between;

	int get_x_for_target_ms_rect(int target_ms, int loop_duration);
	void set_target_rects(int hit_ms_targets[], int loop_duration);

	void draw_display(SDL_Renderer* renderer);

	std::vector<Line> break_up_line_between_rects(std::vector<SDL_Rect>& rects);


};

