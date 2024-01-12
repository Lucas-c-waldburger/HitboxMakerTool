#include "HitboxManager.h"

HitboxManager::HitboxManager() : hb_rects(), interaction_state(NONE)
{}

void HitboxManager::event_loop(SDL_Event* ev)
{
	mouse_coords.update();

	switch (ev->type)
	{
	case SDL_MOUSEBUTTONDOWN:
	{
		switch (ev->button.button)
		{
		case SDL_BUTTON_MIDDLE:

			if (interaction_state == MOVING)
				state_behavior_moving();

			else if (interaction_state == NONE && hb_rects.has_active())
				start_move_state();

			break;

		case SDL_BUTTON_LEFT:

			if (interaction_state == DRAWING)
				state_behavior_drawing();

			else if (interaction_state == RESIZING)
				state_behavior_resizing();

			else if (interaction_state == NONE)
			{
				if (hb_rects.has_active() && hb_rects.get_active_resizer_quad() != Quad::NULL_QUAD)
					start_resize_state();

				else
					start_draw_state();
			}

			break;
		}

		break;
	}
	case SDL_MOUSEBUTTONUP:
	{
		reset_state();
		break;
	}
	case SDL_MOUSEMOTION:
	{
		perform_motion_state_behavior();
		break;
	}
	}
}

void HitboxManager::draw_rects(SDL_Renderer* renderer)
{
	hb_rects.draw(renderer);
}

void HitboxManager::state_behavior_none()
{
	// if mouse over rect, switch it to active spot
	hb_rects.set_active(hb_rects.find_rect_at(mouse_coords.current()));

	if (hb_rects.has_active())
		hb_rects.set_active_resizer_quad(hb_rects.find_resizer_at(mouse_coords.current()));

	//App::app_cursors->set(get_arrow_for_quad(hb_rects.get_active_resizer_quad()));
}

void HitboxManager::state_behavior_drawing() // assume active rect loaded 
{
	//std::cout << "Performing state bhx: DRAWING\n\n";

	HitboxTransform::calc_active_rect_from_point(hb_rects, mouse_coords.current());
}

void HitboxManager::state_behavior_moving()
{
	//std::cout << "Performing state bhx: MOVING\n\n";

	HitboxTransform::adjust_active_rect_position(hb_rects, mouse_coords.current(), mouse_coords.last_frame());
	hb_rects.update_resizers();
}

void HitboxManager::state_behavior_resizing()
{
	//std::cout << "Performing state bhx: RESIZING\n\n";
 
	HitboxTransform::calc_active_rect_from_point(hb_rects, mouse_coords.current());
	hb_rects.update_resizers();

}

void HitboxManager::start_draw_state()
{
	std::cout << "STARTING DRAW STATE\n" << mouse_coords.current();

	hb_rects.add_new_draw_rect(mouse_coords.current());
	interaction_state = DRAWING;
}



void HitboxManager::start_move_state()
{
	HitboxTransform::adjust_active_rect_position(hb_rects, mouse_coords.current(), mouse_coords.last_frame());
	interaction_state = MOVING;
}



void HitboxManager::start_resize_state()
{
	HitboxTransform::invert_origin_point(hb_rects, hb_rects.get_active_resizer_quad());
	HitboxTransform::calc_active_rect_from_point(hb_rects, mouse_coords.current());
	hb_rects.update_resizers();
	interaction_state = RESIZING;
}

void HitboxManager::reset_state()
{
	hb_rects.clear_active();
	hb_rects.clear_resizers();
	hb_rects.clear_active_resizer();
	App::app_cursors->set(App::AppCursors::ArrowType::DEFAULT);
	interaction_state = NONE;
}

void HitboxManager::perform_motion_state_behavior()
{
	switch (interaction_state)
	{
	case NONE:
		state_behavior_none(); break;

	case DRAWING:
		state_behavior_drawing(); break;

	case MOVING:
		state_behavior_moving(); break;

	case RESIZING:
		state_behavior_resizing(); break;
	}
}



//void HitboxManager::perform_rect_target_upkeep( 
//{
//	if (auto stored_rect = hb_rects.find_rect_at(mouse_coords.current()))
//	{
//		hb_rects.make_active(stored_rect);
//
//}
