#include "Utils.h"

Utils::PPoint::~PPoint() { delete ppt; }

const SDL_Point* Utils::PPoint::operator=(const SDL_Point& p)
{
    if (!ppt)
        ppt = new SDL_Point(p);
    else
        *ppt = p;

    return ppt;
}

const SDL_Point* Utils::PPoint::operator=(const SDL_Point* p)
{
    if (!p)
        ppt = nullptr;
    else
        *ppt = *p;

    return ppt;
}

Utils::PPoint::operator const SDL_Point* () { return ppt; }


//const SDL_Point Utils::MouseCoords::get()
//{
//    SDL_GetMouseState(&m_point.x, &m_point.y);
//    return m_point;
//}