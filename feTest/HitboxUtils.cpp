#include "HitboxUtils.h"

SDL_Point hitbox_utils::MouseCoords::current() const
{
	return current_;
}

SDL_Point hitbox_utils::MouseCoords::last_frame() const
{
	return last_frame_;
} 

void hitbox_utils::MouseCoords::update()
{
	last_frame_ = current_;
	SDL_GetMouseState(&current_.x, &current_.y);
}


hitbox_utils::Quad hitbox_utils::calc_quad(int x_change, int y_change)
{
	if (x_change < 0)
		return (y_change < 0) ? Quad::TOP_LEFT : Quad::BOT_LEFT;

	return (y_change < 0) ? Quad::TOP_RIGHT : Quad::BOT_RIGHT;
}

bool hitbox_utils::point_inside_rect(const SDL_Point p, const SDL_Rect& rect)
{
	return ((p.x >= rect.x && p.x <= rect.x + rect.w) &&
			(p.y >= rect.y && p.y <= rect.y + rect.h));
}

bool hitbox_utils::point_out_of_bounds(const SDL_Point p)
{
	auto oob = [](const int n, const int upper_bound)
	{
		return (n < 0 || n > upper_bound);
	};

	return oob(p.x, SCREEN_WIDTH) || oob(p.y, SCREEN_HEIGHT);
}

SDL_Point hitbox_utils::keep_point_in_bounds(const SDL_Point p)
{
	auto adjust = [](const int n, const int upper_bound)
	{
		return (n < 0) ? 0 : (n > upper_bound ? upper_bound : n);
	};

	return { adjust(p.x, SCREEN_WIDTH), adjust(p.y, SCREEN_HEIGHT) };
}

SDL_Rect hitbox_utils::make_rect_from_points(const SDL_Point p1, const SDL_Point p2)
{
	return { p1.x, p1.y, p2.x - p1.x, p2.y - p1.y };
}

SDL_Rect hitbox_utils::calc_rect_change(const SDL_Point orig_p, const SDL_Point new_p, const Quad current_quad)
{
	SDL_Point p1, p2;

	switch (current_quad)
	{
	case Quad::TOP_RIGHT:

		p1 = { orig_p.x, new_p.y };
		p2 = { new_p.x, orig_p.y };
		break;

	case Quad::TOP_LEFT:

		p1 = new_p;
		p2 = orig_p;
		break;

	case Quad::BOT_LEFT:

		p1 = { new_p.x, orig_p.y };
		p2 = { orig_p.x, new_p.y };
		break;

	case Quad::BOT_RIGHT:

		p1 = orig_p;
		p2 = new_p;
	}

	p1 = keep_point_in_bounds(p1);
	p2 = keep_point_in_bounds(p2);

	return make_rect_from_points(p1, p2);
}

SDL_Point hitbox_utils::get_rect_vertex_for_quad(const SDL_Rect rect, const Quad quad)
{
	SDL_Point vert;

	switch (quad)
	{
	case TOP_RIGHT:
		vert = { rect.x + rect.w, rect.y }; break;
	case TOP_LEFT:
		vert = { rect.x, rect.y }; break;
	case BOT_LEFT:
		vert = { rect.x, rect.y + rect.h }; break;
	case BOT_RIGHT:
		vert = { rect.x + rect.w, rect.y + rect.h };
	}

	return vert;
}

int hitbox_utils::squared_dist(SDL_Point p1, SDL_Point p2)
{
	return ((p2.x - p1.x) * (p2.x - p1.x)) + ((p2.y - p1.y) * (p2.y - p1.y));
}

int hitbox_utils::comp_dist_to_val(SDL_Point p1, SDL_Point p2, int comp_val)
{
	int sq_dist = squared_dist(p1, p2), sq_comp = comp_val * comp_val;

	return (sq_dist > sq_comp) ? 1 : (sq_dist < sq_comp) ? -1 : 0;
}

SDL_Rect hitbox_utils::pad_rect(const SDL_Rect rect, int x_pad, int y_pad)
{
	return { rect.x - x_pad, rect.y - y_pad, rect.w + (x_pad << 1), rect.h + (y_pad << 1) };
}

SDL_Rect hitbox_utils::pad_rect(const SDL_Rect rect, int pad)
{
	return { rect.x - pad, rect.y - pad, rect.w + (pad << 1), rect.h + (pad << 1) };
}

App::AppCursors::ArrowType hitbox_utils::get_arrow_for_quad(Quad quad)
{
	return (quad == TOP_RIGHT || quad == BOT_LEFT) ? App::AppCursors::ArrowType::NE_SW :
		   (quad == TOP_LEFT || quad == BOT_RIGHT) ? App::AppCursors::ArrowType::NW_SE :
													 App::AppCursors::ArrowType::DEFAULT;
}

hitbox_utils::RectVerticies::RectVerticies(const SDL_Rect rect)
{
	mVertices[TOP_RIGHT] = { rect.x + rect.w, rect.y };
	mVertices[TOP_LEFT] = { rect.x, rect.y };
	mVertices[BOT_LEFT] = { rect.x, rect.y + rect.h };
	mVertices[BOT_RIGHT] = { rect.x + rect.w, rect.y + rect.h };
}

SDL_Rect hitbox_utils::RectVerticies::to_rect() const
{
	return { mVertices[TOP_LEFT].x, mVertices[TOP_LEFT].y,
			 mVertices[TOP_LEFT].x + (mVertices[BOT_RIGHT].x - mVertices[TOP_LEFT].x),
			 mVertices[TOP_LEFT].y + (mVertices[BOT_RIGHT].y - mVertices[TOP_LEFT].y) };
}

hitbox_utils::RectVerticies::operator SDL_Point* ()
{
	return mVertices;
}
