#pragma once
#include "HitboxRects.h"
#include <iostream>


class HitboxManager
{
public:
	HitboxManager();

	enum InteractionState
	{
		NONE,
		DRAWING,
		MOVING,
		RESIZING
	};

	void event_loop(SDL_Event* ev);
	void draw_rects(SDL_Renderer* renderer);

	void state_behavior_none();
	void state_behavior_drawing();
	void state_behavior_moving();
	void state_behavior_resizing();

	void start_draw_state();
	void start_move_state();
	void start_resize_state();

	void reset_state();

	void perform_motion_state_behavior();

	void change_arrow_for_active_quad();

private:
	HitboxRects hb_rects;
	InteractionState interaction_state;

	
};

