//
// Created by Mateus on 5/6/2022.
//

#include "../Include/LAVector3d.h"
#include "../Include/Constants.h"

int _cdecl LAVector3d::RenderDrawLine(SDL_Renderer *renderer, Matrix<float, 2, 1> vec, Array<int, 3, 1> color) {
    SetVectorColor(renderer, color);
    drawcircle(renderer, Constants::ORIGIN_X + vec(0), Constants::ORIGIN_Y - vec(1),3);
    return SDL_RenderDrawLineF(renderer, Constants::ORIGIN_X, Constants::ORIGIN_Y, Constants::ORIGIN_X + vec(0), Constants::ORIGIN_Y - vec(1));
}

void LAVector3d::SetVectorColor(SDL_Renderer *renderer, Array<int, 3, 1> color) {
    SDL_SetRenderDrawColor(renderer, color(0), color(1), color(2), SDL_ALPHA_OPAQUE);
}

void LAVector3d::drawcircle(SDL_Renderer *renderer, int x0, int y0, int radius) {
    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while (x >= y)
    {
        SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
        SDL_RenderDrawPoint(renderer, x0 + y, y0 + x);
        SDL_RenderDrawPoint(renderer, x0 - y, y0 + x);
        SDL_RenderDrawPoint(renderer, x0 - x, y0 + y);
        SDL_RenderDrawPoint(renderer, x0 - x, y0 - y);
        SDL_RenderDrawPoint(renderer, x0 - y, y0 - x);
        SDL_RenderDrawPoint(renderer, x0 + y, y0 - x);
        SDL_RenderDrawPoint(renderer, x0 + x, y0 - y);

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }

        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}

LAVector3d::LAVector3d() {
    LAVector3d::origin = Matrix<float, 2, 1> {{ 0, 0 }};
    LAVector3d::tip = Matrix<float, 2, 1> {{ 0, 0 }};
    LAVector3d::color = Matrix<float, 3, 1> {{ 0, 0, 0 }};
}

LAVector3d::LAVector3d(const Matrix<float, 2, 1> &tip) : tip(tip) {
    LAVector3d::tip = tip;
    LAVector3d::origin = Matrix<float, 2, 1> {{ 0, 0 }};
    LAVector3d::color = Matrix<float, 3, 1> {{ 255, 0, 0 }};
}

LAVector3d::LAVector3d(const Matrix<float, 2, 1> &origin, const Matrix<float, 2, 1> &tip) : origin(origin), tip(tip) {
    LAVector3d::tip = tip;
    LAVector3d::origin = origin;
    LAVector3d::color = Matrix<float, 3, 1> {{ 255, 0, 0 }};
}

const Matrix<float, 2, 1> &LAVector3d::getOrigin() const {
    return origin;
}

void LAVector3d::setOrigin(const Matrix<float, 2, 1> &origin) {
    LAVector3d::origin = origin;
}

const Matrix<float, 2, 1> &LAVector3d::getTip() const {
    return tip;
}

void LAVector3d::setTip(const Matrix<float, 2, 1> &tip) {
    LAVector3d::tip = tip;
}

const Matrix<float, 3, 1> &LAVector3d::getColor() const {
    return color;
}

void LAVector3d::setColor(const Matrix<float, 3, 1> &color) {
    LAVector3d::color = color;
}

