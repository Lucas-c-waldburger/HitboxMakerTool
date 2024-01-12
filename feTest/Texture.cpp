#include "Texture.h"



Texture::Texture() : pTexture(nullptr), render_rect({0, 0, 0, 0})
{}

Texture::~Texture() { free(); }


bool Texture::load(SDL_Renderer* renderer, const std::string& filePath)
{
    free();

    SDL_Surface* temp = IMG_Load(filePath.c_str());
    SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, 0, 0xFF, 0xFF));

    pTexture = SDL_CreateTextureFromSurface(renderer, temp);

    this->render_rect.w = temp->w;
    this->render_rect.h = temp->h;

    SDL_FreeSurface(temp);

    return pTexture;
}

void Texture::draw_all(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, pTexture, nullptr, &render_rect);
}

void Texture::draw_all(SDL_Renderer* renderer, ExOptions* exOp)
{
    SDL_RenderCopyEx(renderer, pTexture, nullptr, exOp->scale.get_scaled(render_rect), exOp->rotation_angle, exOp->rotation_center, exOp->flip_type);
}

void Texture::draw_all(SDL_Renderer* renderer, double rAngle = 0.0, const SDL_Point* rCenter = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE)
{
    SDL_RenderCopyEx(renderer, pTexture, nullptr, nullptr, rAngle, rCenter, flip);
}

void Texture::free()
{
    if (pTexture)
    {
        SDL_DestroyTexture(pTexture);
        pTexture = nullptr;
        this->render_rect.w = this->render_rect.h = 0;
    }
}

int Texture::x() const { return render_rect.x; }
int Texture::y() const { return render_rect.y; }
int Texture::width() const { return render_rect.w; }
int Texture::height() const { return render_rect.h; }

void Texture::setX(int newX) { render_rect.x = newX; }
void Texture::setY(int newY) { render_rect.x = newY; }

SDL_Rect* Texture::get_render_rect() { return nullptr; }


