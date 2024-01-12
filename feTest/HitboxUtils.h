#pragma once
#include "App.h"
#include <iostream>

namespace hitbox_utils
{
	inline std::ostream& operator<<(std::ostream& os, const SDL_Point& p)
	{
		os << "{ " << p.x << ", " << p.y << " }";
		return os;
	}

	inline std::ostream& operator<<(std::ostream& os, const SDL_Rect& rect)
	{
		os << "{ " << rect.x << ", " << rect.y << ", " << rect.w << ", " << rect.h << " }";
		return os;
	}

	inline SDL_Point operator+(const SDL_Point p1, const SDL_Point p2)
	{
		return { p1.x + p2.x, p1.y + p2.y };
	}

	inline SDL_Point operator-(const SDL_Point p1, const SDL_Point p2)
	{
		return { p1.x - p2.x, p1.y - p2.y };
	}

	inline SDL_Point operator+(const SDL_Point p1, const int adjust)
	{
		return { p1.x + adjust, p1.y + adjust };
	}

	inline SDL_Point operator-(const SDL_Point p1, const int adjust)
	{
		return { p1.x - adjust, p1.y - adjust };
	}

	struct RectVerticies
	{
		RectVerticies(const SDL_Rect rect);
		SDL_Point mVertices[4];
		SDL_Rect to_rect() const;

		operator SDL_Point* ();
	};


	struct MouseCoords
	{
		SDL_Point current() const;
		SDL_Point last_frame() const;
		void update(); 	// will do this at the start of each frame if drawing/moving/resizing
	private:
		SDL_Point current_;
		SDL_Point last_frame_;
	};
	inline static MouseCoords mouse_coords{};


	enum Quad
	{
		TOP_RIGHT,
		TOP_LEFT,
		BOT_LEFT,
		BOT_RIGHT,
		NULL_QUAD
	};

	Quad calc_quad(int x_change, int y_change);

	bool point_inside_rect(const SDL_Point p, const SDL_Rect& rect);

	bool point_out_of_bounds(const SDL_Point p);
	SDL_Point keep_point_in_bounds(const SDL_Point p);

	SDL_Rect make_rect_from_points(const SDL_Point p1, const SDL_Point p2);

	SDL_Rect calc_rect_change(const SDL_Point orig_p, const SDL_Point new_p, const Quad current_quad);

	SDL_Point get_rect_vertex_for_quad(const SDL_Rect rect, const Quad quad);

	int squared_dist(SDL_Point p1, SDL_Point p2);
	int comp_dist_to_val(SDL_Point p1, SDL_Point p2, int comp_val);
	SDL_Rect pad_rect(const SDL_Rect rect, int x_pad, int y_pad);
	SDL_Rect pad_rect(const SDL_Rect rect, int pad);

	App::AppCursors::ArrowType get_arrow_for_quad(Quad quad);

};

