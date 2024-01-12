#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <SDL_mixer.h>
#include <stdexcept>
#include <map>
#include <memory>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

namespace App
{
    class App
    {
    public:
        App();
        ~App();
    };

    class Window
    {
    public:
        Window(const char* title);
        Window(const char* title, int w, int h, int x = SDL_WINDOWPOS_UNDEFINED,
            int y = SDL_WINDOWPOS_UNDEFINED, Uint32 flags = SDL_WINDOW_SHOWN);
        ~Window();

        operator SDL_Window* ();

    private:
        SDL_Window* pWindow;
    };

    class Renderer
    {
    public:
        Renderer(SDL_Window* win);
        ~Renderer();

        void clear();
        void present();

        operator SDL_Renderer* ();

    private:
        SDL_Renderer* pRenderer;
    };

    class AppCursors
    {
    public:
        AppCursors();
        ~AppCursors();

        enum ArrowType
        {
            DEFAULT = 0,
            NW_SE = 5,
            NE_SW = 6,
            WE = 7,
            NS = 8
        };

        void set(ArrowType type);
        ArrowType current() const;

    private:
        std::map<ArrowType, SDL_Cursor*> cursor_map;
    };

    static inline std::unique_ptr<AppCursors> app_cursors{};
}