#include "App.h"

// APP
App::App::App()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        throw std::runtime_error(SDL_GetError());

    if (!IMG_Init(IMG_INIT_PNG))
        throw std::runtime_error(SDL_GetError());
    
    if (TTF_Init() < 0)
        throw std::runtime_error(SDL_GetError());

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        throw std::runtime_error(SDL_GetError());

    app_cursors = std::make_unique<AppCursors>();
}

App::App::~App()
{
    TTF_Quit();
    IMG_Quit();
    SDL_VideoQuit();
    SDL_Quit();
}


// WINDOW
App::Window::Window(const char* title)
{
    pWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (!pWindow)
        throw std::runtime_error(SDL_GetError());

}


App::Window::Window(const char* title, int w, int h, int x, int y, Uint32 flags)
{

    pWindow = SDL_CreateWindow(title, x, y, w, h, flags);

    if (!pWindow)
        throw std::runtime_error(SDL_GetError());
}

App::Window::~Window()
{
    SDL_DestroyWindow(pWindow);
}

App::Window::operator SDL_Window* ()
{
    return pWindow;
}


// RENDERER
App::Renderer::Renderer(SDL_Window* win)
{
    pRenderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!pRenderer)
        throw std::runtime_error(SDL_GetError());
}

App::Renderer::~Renderer()
{
    SDL_DestroyRenderer(pRenderer);
}

void App::Renderer::clear()
{
    SDL_SetRenderDrawColor(pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(pRenderer);
}

void App::Renderer::present()
{
    SDL_RenderPresent(pRenderer);
}

App::Renderer::operator SDL_Renderer* ()
{
    return pRenderer;
}


App::AppCursors::AppCursors() : cursor_map
    {
        { DEFAULT, SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW) },
        { NW_SE,   SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENWSE) },
        { NE_SW,   SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENESW) },
        { WE,      SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE) },
        { NS,      SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS) }
    }
    //: arrow_default(SDL_SYSTEM_CURSOR_ARROW),
    //  arrow_nw_se(SDL_SYSTEM_CURSOR_SIZENWSE),
    //  arrow_ne_sw(SDL_SYSTEM_CURSOR_SIZENESW),
    //  arrow_we(SDL_SYSTEM_CURSOR_SIZEWE),
    //  arrow_ns(SDL_SYSTEM_CURSOR_SIZENS)
{
    for (auto& cursors : cursor_map)
    {
        if (!cursors.second)
            throw std::runtime_error(SDL_GetError());

        SDL_SetCursor(cursor_map[DEFAULT]);
    }

}

App::AppCursors::~AppCursors()
{
    for (auto& cursors : cursor_map)
    {
        SDL_FreeCursor(cursors.second);
    }
}

void App::AppCursors::set(ArrowType type)
{
    SDL_SetCursor(cursor_map[type]);
}

App::AppCursors::ArrowType App::AppCursors::current() const
{
    SDL_Cursor* current_ = SDL_GetCursor();
    
    for (auto& cursors : cursor_map)
    {
        if (current_ == cursors.second)
            return cursors.first;
    }

    throw std::runtime_error("No mouse");
}


