#pragma once
#include "SDL_ttf.h"
#include "Texture.h"
#include <vector>



namespace widgets
{
	class TextTexture : public Texture
	{
	public:
		TextTexture();
		virtual ~TextTexture();

		bool open_font(const std::string& file_path, int size);
		bool load(SDL_Renderer* renderer, const std::string& text, SDL_Color color = { 0, 0, 0 });
		 
	private:
		TTF_Font* font;
	};


	// widget factory
	// global widget observer




	//class WidgetBase
	//{
	//public:
	//	virtual ~WidgetBase() {};
	//	template <typename T> T& get_texture();
	//};

	//template <typename T>
	//class Widget : public WidgetBase
	//{
	//	Widget() {};
	//	virtual ~Widget() = default;

	//	T& get_texture() { return mTexture; }

	//protected:
	//	T mTexture;
	//};


	//template <typename T>
	//T& WidgetBase::get_texture() { return dynamic_cast<Widget<T>&>(*this).get_texture(); }

	//
	//class TextLabel
	//{
	//public:

	//private:
	//	std::unique_ptr<WidgetBase> mWidget;
	//};




};

