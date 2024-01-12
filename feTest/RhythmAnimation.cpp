#include "RhythmAnimation.h"



int rhythm_anim::get_x_pos(Uint64 timer_count, Uint64 loop_duration)
{
    return ((timer_count * SCREEN_WIDTH) / loop_duration) - (MOVING_RECT_W / 2);
}

void rhythm_anim::move_anim_rect(Uint64 timer_count, Uint64 loop_duration)
{
    moving_rect.x = ((timer_count * SCREEN_WIDTH) / loop_duration) - (MOVING_RECT_W / 2);
}

void rhythm_anim::draw_anim_rects(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &moving_rect);
}
