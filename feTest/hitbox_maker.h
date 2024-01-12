//#pragma once
//#include "Texture.h"
//#include "rect_draw_calc.h"
//#include "rect_move.h"
//#include "rect_collection.h"
//#include "App.h"
//#include <memory>
//#include <map>
//
///// <TODO>
///// change app_cursors to a uniq ptr inside whatever the main
///// rect manager things becomes.
///// change active_rect to non-const. dont recreate it each frame, just update it
///// 
///// 
///// 
///// </TODO>
//
//namespace hbm
//{
//	
//
//	static constexpr SDL_Point CLEARED_POINT = { INT_MAX, INT_MAX };
//	inline bool operator!=(const SDL_Point& p1, const SDL_Point& p2) { return p1.x != p2.x || p1.y != p2.y; }
//	inline SDL_Point operator-(const SDL_Point& p1, const SDL_Point& p2) { return { p1.x - p2.x, p1.y - p2.y }; }
//	inline SDL_Rect& operator+=(SDL_Rect& rect, const SDL_Point& p_adjustment)
//	{
//		rect.x += p_adjustment.x;
//		rect.y += p_adjustment.y;	
//		return rect;
//	}
//	inline SDL_Rect operator+(const SDL_Rect& rect, const SDL_Point& p_adjustment)
//	{
//		return { rect.x + p_adjustment.x, rect.y + p_adjustment.y, rect.w, rect.h };
//	}
//
//	inline bool operator==(SDL_Rect& lhs, const SDL_Rect& rhs)
//	{
//		return lhs.x == rhs.x &&
//			   lhs.y == rhs.y &&
//			   lhs.w == rhs.w &&
//			   lhs.h == rhs.h;
//	}
//
//
//	struct HitboxRect : public SDL_Rect // make active rect
//	{
//		HitboxRect() = default;
//		HitboxRect(const SDL_Rect rect);
//		HitboxRect(int x, int y, int w, int h);
//		HitboxRect& operator=(const SDL_Rect rect);
//
//		void set_x(int new_x);
//		void set_y(int new_x);
//		void set_w(int new_x);
//		void set_h(int new_x);
//
//		//SDL_Rect main_rect;
//		SDL_Rect resizers[4];
//
//		static void draw_all(SDL_Renderer* renderer, HitboxRect& hb_rect);
//		static SDL_Rect* point_inside_resizer(const SDL_Point p, HitboxRect* hb_rect);
//
//
//	private:
//		void adjust_resizer_positions(int x_adjust, int y_adjust);
//
//		static constexpr SDL_Point MIN_HITBOX_RECT_DIMENSIONS_FOR_RESIZERS = { 15, 15 };
//		static constexpr SDL_Point MAX_HITBOX_RECT_DIMENSIONS_FOR_RESIZERS = { 200, 200 };
//		static constexpr SDL_Point RESIZER_MIN = { 5, 5 };
//		static constexpr SDL_Point RESIZER_MAX = { 30, 30 };
//		static constexpr float RESIZER_SCALE_TO_RECT_RATE = 0.10;
//
//		static constexpr float RESIZER_TO_MAIN_RECT_RATIO = 0.10;
//
//		//static constexpr int MIN_MAX_DIFF_HITBOX_RECT = (MAX_HITBOX_RECT_DIMENSIONS_FOR_RESIZERS.x - MIN_HITBOX_RECT_DIMENSIONS_FOR_RESIZERS.x);
//		//static constexpr int MIN_MAX_DIFF_RESIZERS = (RESIZER_MAX.x - RESIZER_MIN.x);
//
//		//SDL_Rect main_rect;
//
//		//std::map<Quad, SDL_Rect> resizers;
//
//		//SDL_Rect resizer_TR;
//		//SDL_Rect resizer_TL;
//		//SDL_Rect resizer_BL;
//		//SDL_Rect resizer_BR;
//	};
//
//
//	class ActiveRect
//	{
//	public:
//		ActiveRect();
//		~ActiveRect();
//		
//		operator SDL_Rect* ();
//
//		void reset();
//		void set_main_rect_val(const SDL_Rect& rect);
//		void link_main_rect_to_saved(SDL_Rect* rect);
//		void update_resizers();
//
//		static SDL_Rect* point_inside_resizer(const SDL_Point p, ActiveRect& active_rect);
//
//		static void draw_all(SDL_Renderer* renderer, ActiveRect& active_rect);
//		static void draw_main_rect(SDL_Renderer* renderer, ActiveRect& active_rect);
//		static void draw_resizers(SDL_Renderer* renderer, ActiveRect& active_rect);
//
//		static void clear_rect(SDL_Rect& rect);
//		static bool is_cleared(const SDL_Rect rect);
//
//		bool main_rect_moved() const;
//		bool main_rect_resized() const;
//
//
//		static constexpr float RESIZER_TO_RECT_RATIO = 0.12;
//		static constexpr SDL_Rect EMPTY_RECT = { 0, 0, 0, 0 };
//
//		SDL_Rect* main_rect;
//		SDL_Rect main_rect_last_frame;
//		SDL_Rect resizers[4];
//
//		//   int get_resizer_quad()
//
//	private:
//		//SDL_Rect* main_rect;
//		//SDL_Rect main_rect_last_frame;
//		//SDL_Rect resizers[4];
//
//		void move_resizers_only(int x_adjust, int y_adjust);
//		void scale_and_position_resizers();
//	};
//
//
//
//	enum InteractionState
//	{
//		NONE,
//		DRAWING,
//		MOVING,
//		RESIZING // loads up active rect with one of the saved ones
//	};
//	
//	class RectManager
//	{
//	public:
//		RectManager(App::AppCursors& acs);
//		~RectManager();
//
//		SDL_Rect calc_rect(SDL_Point orig_p, Quad current_quad);
//		SDL_Rect calc_active_rect(SDL_Point orig_p);
//
//		void master_draw(SDL_Renderer* renderer);
//		void draw_saved_rects(SDL_Renderer* renderer);
//
//		RectDraw rect_draw;
//		RectMove rect_move;
//
//		void update_active_rect();
//		void push_active_to_saved();
//		void reset_active_rect();
//
//		SDL_Rect* mouse_inside_saved_rect();
//
//		void adjust_rect_position(SDL_Rect* rect);
//		//void print_rec_data();
//
//		static SDL_Point keep_in_bounds(const int rect_x, const int rect_y);
//		static SDL_Rect make_rect_from_ps(SDL_Point p1, SDL_Point p2);
//		static std::pair<SDL_Point, SDL_Point> get_rect_ps(const SDL_Rect rect);
//		static bool point_out_of_bounds(const SDL_Point p);
//		static SDL_Point keep_p_in_bounds(const SDL_Point p);
//		static bool point_inside_rect(const SDL_Point p, const SDL_Rect rect);
//
//		App::AppCursors& app_cursors;
//
//
//		bool has_active_rect();
//		ActiveRect& get_active_rect();
//		bool active_rect_owns_ptr();
//
//	private:
//		ActiveRect active_rect;
//		std::vector<SDL_Rect> saved_rects;
//
//	};
//
//
//
//
//	class EventHandler
//	{
//	public:
//		EventHandler(App::AppCursors& acs);
//
//		void handle_mouse_events(SDL_Event* ev);
//		void draw_rects(SDL_Renderer* renderer);
//
//		void start_move_rect();
//		void start_draw_rect();
//		void start_resize_rect();
//		void end_move_rect();
//		void end_draw_rect();
//		void end_resize_rect();
//
//	private:
//		RectManager rect_manager;
//		InteractionState interaction_state;
//	};
//
//
//	//struct MouseLocationKey
//	//{
//	//	enum LOCATION
//	//	{
//	//		NO_RECT,
//
//	//	};
//	//	SDL_Point mouse_pos;
//
//	//};
//
//
//
//
//
//
//};
//
