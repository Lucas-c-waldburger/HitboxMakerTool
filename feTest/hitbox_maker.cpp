//#include "hitbox_maker.h"
//
//
//hbm::EventHandler::EventHandler(App::AppCursors& acs) : rect_manager(acs)
//{}
//
//void hbm::EventHandler::handle_mouse_events(SDL_Event* ev)
//{
//	// if (interaction_state != InteractionState::NONE)
//		// mouse_coords.update();
//
//	switch (ev->type)
//	{
//	case SDL_MOUSEBUTTONDOWN:
//	{
//		switch (ev->button.button)
//		{
//		case SDL_BUTTON_MIDDLE:
//
//			if (interaction_state == InteractionState::NONE)
//				start_move_rect();
//
//			break;
//
//		case SDL_BUTTON_LEFT:
//
//			if (interaction_state == InteractionState::RESIZING) // check if still on a resizer
//			{
//
//			}
//
//			if (interaction_state == InteractionState::NONE)
//			{ 
//				if (auto selected_rect = rect_manager.mouse_inside_saved_rect())
//				{
//					rect_manager.get_active_rect().link_main_rect_to_saved(selected_rect);
//
//					if (auto selected_resizer = ActiveRect::point_inside_resizer(mouse_coords.get(),
//																				 rect_manager.get_active_rect()))
//					{
//						interaction_state = InteractionState::RESIZING;
//						start_resize_rect();
//					}
//				}
//				
//				else
//					start_draw_rect();
//			}
//
//		}
//
//		break;
//	}
//	case SDL_MOUSEBUTTONUP:
//	{
//		switch (ev->button.button)
//		{
//		case SDL_BUTTON_MIDDLE:
//
//			if (interaction_state == InteractionState::MOVING)
//				end_move_rect();
//
//			break;
//
//		case SDL_BUTTON_LEFT:
//
//			if (interaction_state == InteractionState::DRAWING)
//				end_draw_rect();
//		}
//
//		break;
//	}
//	case SDL_MOUSEMOTION:
//	{
//		if (interaction_state == (InteractionState::DRAWING | InteractionState::RESIZING))
//			rect_manager.update_active_rect();
//
//		else if (interaction_state == InteractionState::MOVING)
//		{
//			rect_manager.adjust_rect_position(rect_manager.rect_move.moving_rect);
//			rect_manager.rect_move.mouse_coords_last_frame = mouse_coords.get();
//		}
//	}
//	}
//}
//
//void hbm::EventHandler::draw_rects(SDL_Renderer* renderer)
//{
//	if (rect_manager.has_active_rect())
//	{
//		if (interaction_state == InteractionState::RESIZING)
//			ActiveRect::draw_resizers(renderer, rect_manager.get_active_rect());
//
//		if (!rect_manager.active_rect_owns_ptr())
//			ActiveRect::draw_main_rect(renderer, rect_manager.get_active_rect());
//	}
//
//	rect_manager.draw_saved_rects(renderer);
//}
//
//void hbm::EventHandler::start_move_rect()
//{
//	if (rect_manager.rect_move.moving_rect = rect_manager.mouse_inside_saved_rect())
//	{
//		rect_manager.rect_move.mouse_coords_last_frame = mouse_coords.get();
//		interaction_state = InteractionState::MOVING;
//	}
//}
//
//void hbm::EventHandler::start_draw_rect()
//{
//	rect_manager.rect_draw.set_orig_p(mouse_coords.get());
//	rect_manager.update_active_rect();
//	interaction_state = InteractionState::DRAWING;
//}
//
//void hbm::EventHandler::end_move_rect()
//{
//	interaction_state = InteractionState::NONE;
//	rect_manager.rect_move.moving_rect = nullptr;
//}
//
//void hbm::EventHandler::end_draw_rect()
//{
//	interaction_state = InteractionState::NONE;
//	rect_manager.update_active_rect();
//	rect_manager.push_active_to_saved();
//	rect_manager.reset_active_rect();
//}
//
//
//hbm::RectManager::RectManager(App::AppCursors& acs) : rect_draw(), rect_move(), app_cursors(acs)
//{}
//
//hbm::RectManager::~RectManager()
//{
//	if (active_rect_owns_ptr())
//		delete active_rect.main_rect;
//}
//
//SDL_Rect hbm::RectManager::calc_rect(SDL_Point orig_p, Quad current_quad)
//{
//	SDL_Point p1, p2;
//
//	switch (current_quad)
//	{
//	case Quad::TOP_LEFT:
//
//		p1 = mouse_coords.get();
//		p2 = orig_p;
//		break;
//
//	case Quad::BOT_LEFT:
//
//		p1 = { mouse_coords.get().x, orig_p.y };
//		p2 = { orig_p.x, mouse_coords.get().y };
//		break;
//
//	case Quad::TOP_RIGHT:
//		
//		p1 = { orig_p.x, mouse_coords.get().y };
//		p2 = { mouse_coords.get().x, orig_p.y };
//		break;
//
//	default: // BOT_RIGHT
//
//		p1 = orig_p;
//		p2 = mouse_coords.get();
//
//	}
//
//	p1 = keep_in_bounds(p1.x, p1.y);
//	p2 = keep_in_bounds(p2.x, p2.y);
//
//	return make_rect_from_ps(p1, p2);
//}
//
//SDL_Rect hbm::RectManager::calc_active_rect(SDL_Point orig_p)
//{
//	Quad current_quad = RectDraw::calc_quad(mouse_coords.get().x - orig_p.x,
//						mouse_coords.get().y - orig_p.y);
//
//	return calc_rect(orig_p, current_quad);
//}
//
//
//void hbm::RectManager::master_draw(SDL_Renderer* renderer)
//{
//
//	if (active_rect.main_rect)
//		ActiveRect::draw_all(renderer, active_rect);
//
//	if (saved_rects.size() > 0)
//		SDL_RenderDrawRects(renderer, &saved_rects[0], saved_rects.size());
//		
//}
//
//void hbm::RectManager::draw_saved_rects(SDL_Renderer* renderer)
//{
//	if (saved_rects.size() > 0)
//		SDL_RenderDrawRects(renderer, &saved_rects[0], saved_rects.size());
//}
//
//void hbm::RectManager::update_active_rect()
//{
//	active_rect.set_main_rect_val(calc_active_rect(rect_draw.get_orig_p()));
//}
//
//void hbm::RectManager::push_active_to_saved()
//{
//	if (active_rect)
//		saved_rects.push_back(static_cast<SDL_Rect>(*active_rect));
//}
//
//void hbm::RectManager::reset_active_rect()
//{
//	active_rect.reset();
//}
//
//SDL_Rect* hbm::RectManager::mouse_inside_saved_rect()
//{
//	auto selected_rect = std::find_if(saved_rects.begin(), saved_rects.end(), [](const SDL_Rect& rect)
//		{
//			SDL_Point mouse_pos = mouse_coords.get();
//			return point_inside_rect(mouse_pos, rect);
//		});
//
//	return (selected_rect != saved_rects.end()) ? &(*selected_rect) : nullptr;
//}
//
//void hbm::RectManager::adjust_rect_position(SDL_Rect* rect)
//{
//	if (rect)
//	{
//		int change_x = mouse_coords.get().x - rect_move.mouse_coords_last_frame.x,
//			change_y = mouse_coords.get().y - rect_move.mouse_coords_last_frame.y;
//
//		SDL_Point new_p1 = keep_p_in_bounds({ rect->x + change_x, rect->y + change_y }),
//				  new_p2 = { new_p1.x + rect->w, new_p1.y + rect->h };
//
//		if (point_out_of_bounds(new_p2))
//		{
//			new_p2 = keep_p_in_bounds(new_p2);
//			new_p1 = { new_p2.x - rect->w, new_p2.y - rect->h };
//		}
//
//		rect->x = new_p1.x;
//		rect->y = new_p1.y;
//	}
//}
//
////void hbm::RectManager::print_rec_data()
////{
////	saved_rects.print_rect_data();
////}
//
//SDL_Point hbm::RectManager::keep_in_bounds(const int rect_x, const int rect_y)
//{
//	auto adjust = [](const int n, const int upper_bound)
//	{
//		return (n < 0) ? 0 : (n > upper_bound ? upper_bound : n);
//	};
//
//	return { adjust(rect_x, SCREEN_WIDTH), adjust(rect_y, SCREEN_HEIGHT) };
//}
//
//SDL_Rect hbm::RectManager::make_rect_from_ps(SDL_Point p1, SDL_Point p2)
//{
//	return { p1.x, p1.y, p2.x - p1.x, p2.y - p1.y };
//}
//
//std::pair<SDL_Point, SDL_Point> hbm::RectManager::get_rect_ps(const SDL_Rect rect)
//{
//	return std::make_pair(SDL_Point{ rect.x, rect.y }, SDL_Point{ rect.x + rect.w, rect.y + rect.h });
//}
//
//bool hbm::RectManager::point_out_of_bounds(const SDL_Point p)
//{
//	auto oob = [](const int n, const int upper_bound)
//	{
//		return (n < 0 || n > upper_bound);
//	};
//
//	return oob(p.x, SCREEN_WIDTH) || oob(p.y, SCREEN_HEIGHT);
//}
//
//SDL_Point hbm::RectManager::keep_p_in_bounds(const SDL_Point p)
//{
//	auto adjust = [](const int n, const int upper_bound)
//	{
//		return (n < 0) ? 0 : (n > upper_bound ? upper_bound : n);
//	};
//
//	return { adjust(p.x, SCREEN_WIDTH), adjust(p.y, SCREEN_HEIGHT) };
//}
//
//bool hbm::RectManager::point_inside_rect(const SDL_Point p, const SDL_Rect rect)
//{
//	return ((p.x >= rect.x && p.x <= rect.x + rect.w) &&
//		    (p.y >= rect.y && p.y <= rect.y + rect.h));
//}
//
//bool hbm::RectManager::has_active_rect()
//{
//	return active_rect.main_rect != nullptr;
//}
//
//hbm::ActiveRect& hbm::RectManager::get_active_rect()
//{
//	return active_rect;
//}
//
//bool hbm::RectManager::active_rect_owns_ptr()
//{
//	for (auto& rect : saved_rects)
//	{
//		if (active_rect.main_rect == &rect)
//			return false;
//	}
//
//	return true;
//}
//
//hbm::HitboxRect::HitboxRect(const SDL_Rect rect)
//{
//	set_x(rect.x);
//	set_y(rect.y);
//	this->w = rect.w;
//	this->h = rect.h;
//}
//
//hbm::HitboxRect::HitboxRect(int x, int y, int w, int h) : SDL_Rect{ x, y, w, h }
//{
//	int rz_w = RESIZER_MIN.x;
//	int rz_h = RESIZER_MIN.y;
//
//	resizers[0] = { this->x + (this->w - rz_w), this->y, rz_w, rz_h }; // TOP_RIGHT
//	resizers[1] = { this->x, this->y, rz_w, rz_h }; // TOP_LEFT
//	resizers[2] = { this->x, this->y + (this->h - rz_h), rz_w, rz_h}; // BOT_LEFT
//	resizers[3] = { this->x + (this->w - rz_w), this->y + (this->h - rz_h), rz_w, rz_h }; // BOT_RIGHT
//}
//hbm::HitboxRect& hbm::HitboxRect::operator=(SDL_Rect rect)
//{
//	set_x(rect.x);
//	set_y(rect.y);
//	this->w = rect.w;
//	this->h = rect.h;
//
//	return *this;
//}
//;
// 
//void hbm::HitboxRect::set_x(int new_x)
//{
//	adjust_resizer_positions(new_x - this->x, 0);
//	this->x = new_x;
//}
//
//void hbm::HitboxRect::set_y(int new_y)
//{
//	adjust_resizer_positions(0, new_y - this->y);
//	this->y = new_y;
//}
//
//void hbm::HitboxRect::draw_all(SDL_Renderer* renderer, HitboxRect& hb_rect)
//{
//	SDL_RenderDrawRect(renderer, &hb_rect);
//	if (hb_rect.resizers[0].w > 0)
//		SDL_RenderDrawRects(renderer, hb_rect.resizers, 4);
//}
//
//
//SDL_Rect* hbm::HitboxRect::point_inside_resizer(const SDL_Point p, HitboxRect* hb_rect)
//{
//	for (int i = 0; i < 4; i++)
//	{
//		if (RectManager::point_inside_rect(p, hb_rect->resizers[i]))
//			return &hb_rect->resizers[i];
//	}
//
//	return nullptr;
//}
//
//void hbm::HitboxRect::adjust_resizer_positions(int x_adjust, int y_adjust)
//{
//	for (int i = 0; i < 4; i++)
//	{
//		resizers[i].x += x_adjust;
//		resizers[i].y += y_adjust;
//	}
//}
//
//hbm::ActiveRect::ActiveRect()
//{
//	reset();
//}
//
//hbm::ActiveRect::~ActiveRect()
//{}
//
//hbm::ActiveRect::operator SDL_Rect* ()
//{
//	return main_rect; 
//}
//
//void hbm::ActiveRect::reset()
//{
//	main_rect = nullptr;
//	//main_rect_last_frame = { 0, 0, 0, 0 };
//
//	for (int i = 0; i < 4; i++)
//		resizers[i] = { 0, 0, 0, 0 };
//}
//
//void hbm::ActiveRect::set_main_rect_val(const SDL_Rect& rect)
//{
//	if (!main_rect) // either starting being drawn this frame or loaded from saved rect
//		main_rect = new SDL_Rect(rect);
//
//	else
//		*main_rect = rect;
//
//	if (main_rect_moved())
//	{
//		if (main_rect_resized())
//			scale_and_position_resizers();
//		else
//			move_resizers_only(main_rect->x - resizers[1].x, main_rect->y - resizers[1].y);
//	}
//
//	else if (main_rect_resized())
//		scale_and_position_resizers();
//
//	main_rect_last_frame = *main_rect;
//}
//
//void hbm::ActiveRect::link_main_rect_to_saved(SDL_Rect* rect)
//{
//	if (main_rect)
//		throw std::runtime_error("Must clear main rect before linking to avoid mem leak");
//
//	main_rect = rect;
//	scale_and_position_resizers();
//	main_rect_last_frame = *main_rect;
//}
//
//
//SDL_Rect* hbm::ActiveRect::point_inside_resizer(const SDL_Point p, ActiveRect& active_rect)
//{
//	for (int i = 0; i < 4; i++)
//	{
//		if (RectManager::point_inside_rect(p, active_rect.resizers[i]))
//			return &active_rect.resizers[i];
//	}
//
//	return nullptr;
//}
//
//void hbm::ActiveRect::draw_all(SDL_Renderer* renderer, ActiveRect& active_rect)
//{
//	SDL_RenderDrawRect(renderer, active_rect);
//	if (active_rect.resizers[0].w > 0)
//		SDL_RenderDrawRects(renderer, active_rect.resizers, 4);
//}
//
//void hbm::ActiveRect::draw_main_rect(SDL_Renderer* renderer, ActiveRect& active_rect)
//{
//	SDL_RenderDrawRect(renderer, active_rect);
//}
//
//void hbm::ActiveRect::draw_resizers(SDL_Renderer* renderer, ActiveRect& active_rect)
//{
//	if (active_rect.resizers[0].w > 0)
//		SDL_RenderDrawRects(renderer, active_rect.resizers, 4);
//}
//
//void hbm::ActiveRect::clear_rect(SDL_Rect& rect)
//{
//	rect.x = 0;
//	rect.y = 0;
//	rect.w = 0;
//	rect.h = 0;
//}
//
//bool hbm::ActiveRect::main_rect_moved() const
//{
//	return main_rect->w != main_rect_last_frame.w || 
//		   main_rect->h != main_rect_last_frame.h;
//}
//
//bool hbm::ActiveRect::main_rect_resized() const
//{
//	return main_rect->x != main_rect_last_frame.x ||
//		   main_rect->y != main_rect_last_frame.y;
//}
//
//void hbm::ActiveRect::move_resizers_only(int x_adjust, int y_adjust)
//{
//	for (int i = 0; i < 4; i++)
//	{
//		resizers[i].x += x_adjust;
//		resizers[i].y += y_adjust;
//	}
//}
//
//void hbm::ActiveRect::scale_and_position_resizers()
//{
//	int main_rect_shortest_side = (main_rect->w < main_rect->h) ? main_rect->w : main_rect->h;
//	int side_len = main_rect_shortest_side * RESIZER_TO_RECT_RATIO;
//
//	resizers[0] = { main_rect->x + (main_rect->w - side_len), main_rect->y, side_len, side_len }; // TOP_RIGHT
//	resizers[1] = { main_rect->x, main_rect->y, side_len, side_len }; // TOP_LEFT
//	resizers[2] = { main_rect->x, main_rect->y + (main_rect->h - side_len), side_len, side_len }; // BOT_LEFT
//	resizers[3] = { main_rect->x + (main_rect->w - side_len), main_rect->y + (main_rect->h - side_len), side_len, side_len }; // BOT_RIGHT
//}
