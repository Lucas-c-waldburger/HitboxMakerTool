#include "RhythmDisplay.h"

//int rhythm_display::get_x_for_target_ms_rect(int target_ms)
//{
//	return (target_ms * SCREEN_WIDTH) / loop_duration) - (TARGET_RECT_W / 2),
//}



void rhythm_display::set_target_rects(int hit_ms_targets[], int loop_duration)
{
	for (int i = 0; i < sizeof(hit_ms_targets) / sizeof(int); i++)
	{
		target_display_rects.emplace_back
		(
			((hit_ms_targets[i] * SCREEN_WIDTH) / loop_duration) - (TARGET_RECT_W / 2),
			SCREEN_CENTER.y - (TARGET_RECT_H / 2),
			TARGET_RECT_W,
			TARGET_RECT_H
		);
	}



}

void rhythm_display::draw_display(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	//SDL_RenderDrawLine(renderer, 0, SCREEN_CENTER.y, SCREEN_CENTER.x - (TARGET_RECT_1.w / 2), SCREEN_CENTER.y);
	//SDL_RenderDrawLine(renderer, SCREEN_CENTER.x + (TARGET_RECT_1.w / 2), SCREEN_CENTER.y, SCREEN_WIDTH, SCREEN_CENTER.y);

	

	SDL_RenderDrawRects(renderer, &target_display_rects[0], target_display_rects.size());
}

std::vector<rhythm_display::Line> rhythm_display::break_up_line_between_rects(std::vector<SDL_Rect>& rects)
{

	std::vector<Line> lines;
	int x_pos = 0;

	for (int i = 0; i < lines.size() - 1; i++)
	{
		lines.emplace_back(x_pos, SCREEN_CENTER.y, rects[i].x, SCREEN_CENTER.y);
		x_pos += rects[i].w;
	}

	lines.emplace_back(x_pos, SCREEN_CENTER.y, SCREEN_WIDTH, SCREEN_CENTER.y);

}
