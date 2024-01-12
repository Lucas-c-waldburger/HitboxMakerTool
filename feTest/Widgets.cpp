#include "Widgets.h"

widgets::TextTexture::TextTexture() : Texture(), font(nullptr)
{}

widgets::TextTexture::~TextTexture()
{
	TTF_CloseFont(font);
}

bool widgets::TextTexture::open_font(const std::string& file_path, int size)
{
	font = TTF_OpenFont(file_path.c_str(), size);
    return font;
}

bool widgets::TextTexture::load(SDL_Renderer* renderer, const std::string& text, SDL_Color color)
{
    free();

    if (!font)
    {
        SDL_Log("Font not opened");
        return false;
    }

    SDL_Surface* temp = TTF_RenderUTF8_Blended(font, text.c_str(), color);
    pTexture = SDL_CreateTextureFromSurface(renderer, temp);

    this->render_rect.w = temp->w;
    this->render_rect.h = temp->h;

    SDL_FreeSurface(temp);

    return pTexture;
}
