#include "HitboxRects.h"

ActiveRect::ActiveRect() : mRect(nullptr), resizer_quad(Quad::NULL_QUAD)
{}


HitboxRects::HitboxRects()
{
	clear_resizers();
}

void HitboxRects::draw(SDL_Renderer* renderer)
{
	//for (int i = 0; i < stored_rects.size(); i++)
	//{
	//	std::cout << "RECT " << i + 1 << ": {" << stored_rects[i].x << ", " <<
	//		stored_rects[i].y << ", " << stored_rects[i].w << ", " << stored_rects[i].h << '\n';
	//}
	//std::cout << '\n';

	if (stored_rects.size() > 0)
		SDL_RenderDrawRects(renderer, &stored_rects[0], stored_rects.size());

	if (resizers[0].w > 0 && active.mRect)
		SDL_RenderDrawRects(renderer, &resizers[0], 4);
}

SDL_Rect* HitboxRects::add_new_draw_rect(const SDL_Point orig_p)
{
	stored_rects.emplace_back();
	active.mRect = &stored_rects.back();
	active.orig_point = orig_p;

	return active.mRect;
}

void HitboxRects::set_active(SDL_Rect* rect)
{
	active.mRect = rect;

	if (active.mRect)
	{
		active.orig_point = { rect->x, rect->y };
		update_resizers();
	}

}

//void HitboxRects::update_active_rect()
//{
//}

void HitboxRects::update_active_rect_vals()
{
}

void HitboxRects::update_resizers()
{
	int active_shortest_side = (active.mRect->w < active.mRect->h) ? active.mRect->w : active.mRect->h;
	int resizer_len = active_shortest_side * RESIZER_TO_ACTIVE_RECT_RATIO;

	resizers[Quad::TOP_RIGHT] = { active.mRect->x + (active.mRect->w - resizer_len), active.mRect->y, resizer_len, resizer_len };
	resizers[Quad::TOP_LEFT]  = { active.mRect->x, active.mRect->y, resizer_len, resizer_len }; 
	resizers[Quad::BOT_LEFT]  = { active.mRect->x, active.mRect->y + (active.mRect->h - resizer_len), resizer_len, resizer_len }; 
	resizers[Quad::BOT_RIGHT] = { active.mRect->x + (active.mRect->w - resizer_len), active.mRect->y + (active.mRect->h - resizer_len), resizer_len, resizer_len }; 
}

void HitboxRects::clear_resizers()
{
	for (int i = 0; i < 4; i++)
		resizers[i] = { 0, 0, 0, 0 };
}

void HitboxRects::clear_active()
{
	active.mRect = nullptr;
	//active.orig_point = { 0, 0 };
	active.resizer_quad = Quad::NULL_QUAD;
}


void HitboxRects::add_to_active_rect_xy(int x_add, int y_add)
{
	active.mRect->x += x_add;
	active.mRect->y += y_add;
}

SDL_Rect* HitboxRects::get_active_rect()
{
	return active.mRect;
}

void HitboxRects::set_active_orig_point(const SDL_Point p)
{
	active.orig_point = p;
}

SDL_Point HitboxRects::get_active_orig_point() const
{
	return active.orig_point;
}

void HitboxRects::set_active_resizer_quad(Quad quad)
{
	active.resizer_quad = quad;
}

void HitboxRects::set_active_resizer(SDL_Rect* resizer)
{
	active.pResizer = resizer;
}

void HitboxRects::clear_active_resizer()
{
	active.pResizer = nullptr;
}

Quad HitboxRects::get_active_resizer_quad() const
{
	return active.resizer_quad;
}

SDL_Rect* HitboxRects::get_active_resizer()
{
	return active.pResizer;
}

bool HitboxRects::has_active()
{
	return active.mRect;
}

SDL_Rect* HitboxRects::find_rect_at(const SDL_Point p)
{
	for (auto& rect : stored_rects)
	{
		if (point_inside_rect(p, rect))
			return &rect;
	}

	return nullptr;
}

SDL_Rect* HitboxRects::find_resizer_rect_at(const SDL_Point p)
{
	for (int i = 0; i < 4; i++)
	{
		if (point_inside_rect(p, resizers[i]))
			return &resizers[i];
	}

	return nullptr;
}

Quad HitboxRects::find_resizer_at(const SDL_Point p)
{
	for (int i = 0; i < 4; i++)
	{
		if (point_inside_rect(p, resizers[i]))
			return static_cast<Quad>(i);
	}

	return NULL_QUAD;
}

void HitboxRects::calc_resize()
{
	//// we know mouse is inside a resizer
	//Quad rszr_quad = find_resizer_at(mouse_coords.current()); 
	//SDL_Point p1, p2;

	//switch (rszr_quad)
	//{
	//case TOP_RIGHT:
	//	p1 = { active.mRect->x, active.mRect->y + active.mRect->h } // move anchor point to bot left
	//	p2 = {}

	//}


}


// is point inside rect?
	// yes -> load rect into active
	// is point inside a resizer?
		// yes -> return quad



void HitboxTransform::calc_active_rect_from_point(HitboxRects& hb_rects, const SDL_Point p)
{
	SDL_Point orig_p = hb_rects.active.orig_point;
	Quad current_quad = calc_quad(p.x - orig_p.x, p.y - orig_p.y);

	*(hb_rects.active.mRect) = calc_rect_change(orig_p, p, current_quad);
}

void HitboxTransform::calc_active_rect_from_point_RESIZER(HitboxRects& hb_rects, const SDL_Point p)
{
	SDL_Point orig_p = hb_rects.active.orig_point;
	Quad current_quad = calc_quad(p.x - orig_p.x, p.y - orig_p.y);

	SDL_Rect temp = calc_rect_change(orig_p, p, current_quad);
	*(hb_rects.active.mRect) = calc_rect_change(orig_p, p, current_quad);
}


//void HitboxTransform::calc_active_rect_from_resizer_quad_NEW(HitboxRects& hb_rects, const SDL_Point new_p, const SDL_Rect* resizer)
//{
//	SDL_Point orig_p = hb_rects.active.orig_point;
//	SDL_Point p1, p2;
//	//auto& rszr = hb_rects.resizers[hb_rects.get_active_resizer_quad()];
//
//	SDL_Point stable_point;
//
//	//switch (hb_rects.get_active_resizer_quad())
//	//{
//	//case TOP_RIGHT:
//	//	p1 = 
//	//case TOP_LEFT:
//	//	orig_p = { rszr.x + rszr.w, rszr.y + rszr.h }; break;
//	//case BOT_LEFT:
//	//	orig_p = { rszr.x + rszr.w, rszr.y }; break;
//	//case BOT_RIGHT:
//	//	orig_p = { rszr.x, rszr.y };
//	//}
//
//	//switch (hb_rects.get_active_resizer_quad())
//	//{
//	//case TOP_RIGHT:
//	//	orig_p = { rszr.x, rszr.y + rszr.h }; break;
//	//case TOP_LEFT:
//	//	orig_p = { rszr.x + rszr.w, rszr.y + rszr.h }; break;
//	//case BOT_LEFT:
//	//	orig_p = { rszr.x + rszr.w, rszr.y }; break;
//	//case BOT_RIGHT:
//	//	orig_p = { rszr.x, rszr.y }; 
//	//}
//
//
//
//
//	Quad current_quad = calc_quad(new_p.x - orig_p.x, new_p.y - orig_p.y);
//	//Quad current_quad = hb_rects.get_active_resizer_quad();
//
//	/*SDL_Point p1, p2;
//	SDL_Point resizer_vert;*/
//
//	//int x_dist_from_resizer_vert, y_dist_from_resizer_vert;
//
//	//// get xy distance from mouse pos to resizer vert
//	//x_dist_from_resizer_vert = resizer_vert.x - new_p.x;
//	//y_dist_from_resizer_vert = resizer_vert.y - new_p.y;
//
//
//	//std::cout << *hb_rects.active.mRect << '\n';
//	//std::cout << "X DIST FROM VERT: " << x_dist_from_resizer_vert << "\nY DIST FROM VERT: " << y_dist_from_resizer_vert << '\n';
//
//
//	std::cout << "ACTIVE RESIZER QUAD: " << hb_rects.get_active_resizer_quad() << '\n';
//	std::cout << "ACTIVE COMPUTED QUAD: " << current_quad << '\n';
//	//auto flip_quad = [](Quad q) { return static_cast<Quad>(~(static_cast<int>(q))); };
//	SDL_Rect temp = calc_rect_change(orig_p, new_p, current_quad);
//	//temp.x += (hb_rects.active.mRect->x + hb_rects.active.mRect->w - temp.x);
//	//temp.y += (hb_rects.active.mRect->y + hb_rects.active.mRect->h - temp.y);
//
//	*(hb_rects.active.mRect) = temp;
//	hb_rects.update_resizers();
//}

void HitboxTransform::adjust_active_rect_position(HitboxRects& hb_rects, const SDL_Point new_p, const SDL_Point p_last_frame)
{
	auto& act_rect = *(hb_rects.active.mRect);
	int change_x = new_p.x - p_last_frame.x,
		change_y = new_p.y - p_last_frame.y;

	SDL_Point new_p1 = keep_point_in_bounds({ act_rect.x + change_x, act_rect.y + change_y }),
			  new_p2 = { new_p1.x + act_rect.w, new_p1.y + act_rect.h };

	if (point_out_of_bounds(new_p2))
	{
		new_p2 = keep_point_in_bounds(new_p2);
		new_p1 = { new_p2.x - act_rect.w, new_p2.y - act_rect.h };
	}

	act_rect.x = new_p1.x;
	act_rect.y = new_p1.y;
}

void HitboxTransform::invert_origin_point(HitboxRects& hb_rects, Quad quad)
{
	switch (quad)
	{
	case TOP_RIGHT:
		hb_rects.active.orig_point.y += hb_rects.active.mRect->h; break;
	case TOP_LEFT:
		hb_rects.active.orig_point.x += hb_rects.active.mRect->w; 
		hb_rects.active.orig_point.y += hb_rects.active.mRect->h; 
		break;
	case BOT_LEFT:
		hb_rects.active.orig_point.x += hb_rects.active.mRect->w; break;
	}
}

SDL_Point HitboxTransform::calc_point_dist_from_active_resizer_vertex(HitboxRects& hb_rects, const SDL_Point p)
{
	Quad q = hb_rects.active.resizer_quad;
	SDL_Point vert = get_rect_vertex_for_quad(hb_rects.resizers[q], q);

	return vert - p;
}



// resizers are only for detecting when to turn on resizing
// find out which quad they represent in the active rect
// and scale from there



void HitboxTransform::snap_to_nearby_rect(HitboxRects& hb_rects)
{
	//if (!hb_rects.active.mRect)
	//	return;

	////RectVerticies active_rect_vertices{ *hb_rects.active.mRect };
	//RectVerticies padded_rect_vertices{ pad_rect(*hb_rects.active.mRect, SNAP_DISTANCE) };

	//for (auto& rect : hb_rects.stored_rects)
	//{
	//	if (hb_rects.active.mRect == &rect) // skip self
	//		continue;

	//	for (int i = 0; i < 4; i++)
	//	{
	//		if (!point_inside_rect(padded_rect_vertices[i], rect))
	//			continue;

	//		int active_vert_quad = static_cast<Quad>(i);

	//		// if the current padded vertex's x is inside the rect,
	//		// set that quad's x to the rect's left x (rect.x)(active_vert_quad == TOP_LEFT or BOT_LEFT), else 
	//		// set active quad's x to rect's right x (rect.x + rect.w)
	//		if (padded_rect_vertices[i].x >= rect.x && padded_rect_vertices[i].x <= rect.x + rect.w)
	//		{
	//			if (active_vert_quad == TOP_LEFT || BOT_LEFT) // touching on rect's right side
	//				hb_rects.active.mRect->x = rect.x + rect.w;
	//			else // touching on rect's right side
	//				hb_rects.active.mRect->w += rect.x - (hb_rects.active.mRect->)
	//		}

	//			//hb_rects.active.mRect->x = (active_vert_quad == TOP_RIGHT || active_vert_quad == BOT_RIGHT) ? 
	//										//rect.x - hb_rects.active.mRect->w : rect.x + rect.w;

	//		else if (snap_added.y >= rect.y && snap_added.y <= rect.y + rect.h)
	//			hb_rects.active.mRect->y = (vert_quad == TOP_RIGHT || vert_quad == BOT_RIGHT) ? 
	//	}
	//}


}


