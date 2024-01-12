#pragma once
#include "App.h"
#include "HitboxUtils.h"
#include <vector>
#include <iostream>

using namespace hitbox_utils;

struct ActiveRect
{
	ActiveRect();

	SDL_Rect* mRect;
	SDL_Point orig_point;
	SDL_Rect* pResizer;
	Quad resizer_quad;
	SDL_Point mouse_dist_from_resizer_vertex;
};

class HitboxRects
{
public:
	friend class HitboxTransform;

	HitboxRects();

	void draw(SDL_Renderer* renderer);

	SDL_Rect* add_new_draw_rect(const SDL_Point orig_point);
	void set_active(SDL_Rect* rect);
	
	void update_active_rect_vals();
	void update_resizers();
	void clear_resizers();
	void clear_active();

	void add_to_active_rect_xy(int x_add, int y_add);
	SDL_Rect* get_active_rect();
	void set_active_orig_point(const SDL_Point p);
	SDL_Point get_active_orig_point() const;
	void set_active_resizer_quad(Quad quad);
	void set_active_resizer(SDL_Rect* resizer);
	void clear_active_resizer();
	Quad get_active_resizer_quad() const;
	SDL_Rect* get_active_resizer();
	bool has_active();

	static constexpr float RESIZER_TO_ACTIVE_RECT_RATIO = 0.10;
	static constexpr SDL_Point MIN_RECT_RESIZE_DIMENSIONS = { 5, 5 };

	SDL_Rect* find_rect_at(const SDL_Point p);
	SDL_Rect* find_resizer_rect_at(const SDL_Point p);

	Quad find_resizer_at(const SDL_Point p);


	void calc_resize();

private:
	ActiveRect active;
	SDL_Rect resizers[4];
	std::vector<SDL_Rect> stored_rects;
};

struct HitboxTransform
{
	static void calc_active_rect_from_point(HitboxRects& hb_rects, const SDL_Point p);
	static void calc_active_rect_from_point_RESIZER(HitboxRects& hb_rects, const SDL_Point p);
	static void adjust_active_rect_position(HitboxRects& hb_rects, const SDL_Point new_p, const SDL_Point p_last_frame);
	static void invert_origin_point(HitboxRects& hb_rects, Quad quad);
	static SDL_Point calc_point_dist_from_active_resizer_vertex(HitboxRects& hb_rects, const SDL_Point p);

	static constexpr int SNAP_DISTANCE = 5;
	static void snap_to_nearby_rect(HitboxRects& hb_rects);
};