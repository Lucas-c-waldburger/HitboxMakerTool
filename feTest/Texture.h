#pragma once
#include "ExOptions.h"
#include "SDL_image.h"
#include <iostream>



struct ExOptions;

class Texture
{
public:
	Texture();
	virtual ~Texture();

	virtual bool load(SDL_Renderer* renderer, const std::string& filePath);

	void draw_all(SDL_Renderer* renderer);
	void draw_all(SDL_Renderer*, ExOptions* exOp);
	void draw_all(SDL_Renderer* renderer, double rAngle, const SDL_Point* rCenter, SDL_RendererFlip flip);

	void free();

	int x() const;
	int y() const;
	int width() const;
	int height() const;

	void setX(int newX);
	void setY(int newY);

	SDL_Rect* get_render_rect();
	//void set_render_rect(SDL_Rect* rect_ptr);
	//void free_render_rect();

protected:
	SDL_Texture* pTexture;
	SDL_Rect render_rect;
	//std::shared_ptr<SDL_Rect> render_rect;
};



