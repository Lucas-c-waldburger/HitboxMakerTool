#pragma once
#include "App.h"
#include "ExOptions.h"
#include <memory>
#include <vector>

namespace render_fmt
{
	struct Line 
	{ 
		inline Line() : p1{ 0, 0 }, p2{ 0, 0 } {};
		inline Line(SDL_Point p1, SDL_Point p2) : p1(p1), p2(p2) {};
		inline Line(int x1, int y1, int x2, int y2) : p1{ x1, x2 }, p2{ x1, x2 } {};

		SDL_Point p1, p2; 
	};

	struct BaseColor
	{
		BaseColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) : mColor{ r, g, b, a } {};
		BaseColor(const SDL_Color& c) : mColor(c) {};
		BaseColor(SDL_Color&& c) : mColor(std::forward<SDL_Color>(c)) {};
		virtual ~BaseColor() = default;



	protected:
		SDL_Color mColor;
	};

	struct LineColor : public BaseColor { virtual ~LineColor() = default; };
	struct FillColor : public BaseColor { virtual ~FillColor() = default; };

	//template <typename T, typename FUNC>
	//struct GeoStore
	//{

	//	inline void add_geo(const T& geo) { geos.push_back(geo); }
	//	inline void add_geo(T&& geo) { geos.push_back(std::forward<T>(geo)); }

	//	std::vector<T> geos;

	//	using ColorIndex = std::vector<std::pair<std::unique_ptr<BaseColor>, int>>;
	//	ColorIndex color_index;

	//	template <typename...Args>
	//	struct ColorApplyWrap
	//	{
	//		template <typename FUNC>
	//		ColorApplyWrap()

	//		void (*color_apply_func)(Args&&...args);
	//	};



	//};

	class End
	{

	};


	template <class Deriv, class T>
	struct DrawStreamObj
	{
		inline T* get() { return static_cast<Deriv*>(this)->impl(); }
	};

	struct TextureDSO : public DrawStreamObj<TextureDSO, SDL_Texture>
	{
		SDL_Texture* pTexture;

		inline SDL_Texture* impl() { return pTexture; }
	};

	struct RectDSO : public DrawStreamObj<RectDSO, SDL_Rect>
	{
		SDL_Rect* pRect;
	};



	class GeoDraw
	{
	public:
		GeoDraw(SDL_Renderer* renderer);


	private:
		SDL_Renderer* pRenderer;


	};


	//class Draw
	//{
	//public:
	//	Draw(SDL_Renderer* renderer);

	//	void perform_draw();

	//	friend Draw& operator<<(Draw& draw, SDL_Rect& rect);
	//	friend Draw& operator<<(Draw& draw, SDL_Point& p);
	//	friend Draw& operator<<(Draw& draw, End& end);

	//private:
	//	std::unique_ptr<SDL_Renderer> pRenderer;
	//	std::unique_ptr<SDL_Rect> pRect;
	//	std::unique_ptr<SDL_Texture> pTexture;
	//	std::unique_ptr<SDL_Color> pColor;
	//	std::unique_ptr<ExOptions::Scale> pScale;


	//};

	// Draw << my_rect << SDL_Color{ 255, 0, 0 255 } << SDL_Point{ 100, 200 } << end;
	

	struct Loc
	{
		Loc(int x, int y) : mPoint({ x, y }) {};
		Loc(const SDL_Point& p) : mPoint(p) {};
		Loc(SDL_Point&& p) : mPoint(std::forward<SDL_Point>(p)) {};

		SDL_Point mPoint;
	};







};

