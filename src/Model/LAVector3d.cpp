//
// Created by Mateus on 5/6/2022.
//

#include "../Include/LAVector3d.h"
#include "../Include/Constants.h"

int _cdecl LAVector3d::RenderDrawLine(SDL_Renderer *renderer, LAVector3d *vec, Array<int, 3, 1> color) {
    Matrix<float, 2, 3> projectionMatrix{{1, 0, 0},
                                         {0, 0, 1}};
    Matrix<float, 2, 1> c{10, 10};

    Matrix<float, 2, 1> projectedVectorOrigin {{Constants::ORIGIN_X + vec->getOrigin()(0)}, {Constants::ORIGIN_Y + vec->getOrigin()(1)}};
    Matrix<float, 2, 1> projectedVectorTip {{Constants::ORIGIN_X + vec->getTip()(0)}, {Constants::ORIGIN_Y + vec->getTip()(1)}};
    printf("vec ---- origin: %f, %f; tip: %f, %f \n", projectedVectorOrigin(0),projectedVectorOrigin(1), projectedVectorTip(0), projectedVectorTip(1));
    SetVectorColor(renderer, color);
    drawcircle(renderer, projectedVectorTip(0), projectedVectorTip(1), 3);
    return SDL_RenderDrawLineF(renderer,
                               projectedVectorOrigin(0),
                               projectedVectorOrigin(1),
                               projectedVectorTip(0),
                               projectedVectorTip(1));
}

void LAVector3d::SetVectorColor(SDL_Renderer *renderer, Array<int, 3, 1> color) {
    SDL_SetRenderDrawColor(renderer, color(0), color(1), color(2), SDL_ALPHA_OPAQUE);
}

void LAVector3d::drawcircle(SDL_Renderer *renderer, int x0, int y0, int radius) {
    int x = radius - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while (x >= y) {
        SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
        SDL_RenderDrawPoint(renderer, x0 + y, y0 + x);
        SDL_RenderDrawPoint(renderer, x0 - y, y0 + x);
        SDL_RenderDrawPoint(renderer, x0 - x, y0 + y);
        SDL_RenderDrawPoint(renderer, x0 - x, y0 - y);
        SDL_RenderDrawPoint(renderer, x0 - y, y0 - x);
        SDL_RenderDrawPoint(renderer, x0 + y, y0 - x);
        SDL_RenderDrawPoint(renderer, x0 + x, y0 - y);

        if (err <= 0) {
            y++;
            err += dy;
            dy += 2;
        }

        if (err > 0) {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}

LAVector3d::LAVector3d() {
    LAVector3d::origin = Matrix<float, 3, 1>{{0, 0}};
    LAVector3d::tip = Matrix<float, 3, 1>{{0, 0}};
    LAVector3d::color = Matrix<float, 3, 1>{{0, 0, 0}};
}

LAVector3d::LAVector3d(const Matrix<float, 3, 1> &tip) : tip(tip) {
    LAVector3d::tip = tip;
    if (this->getNextVector() == nullptr) {
        LAVector3d::origin = Matrix<float, 3, 1>{{0, 0, 0}};
    } else {
        LAVector3d::origin = this->nextVector->getTip();
    }
    LAVector3d::color = Matrix<float, 3, 1>{{255, 0, 0}};
}

LAVector3d::LAVector3d(const Matrix<float, 3, 1> &origin, const Matrix<float, 3, 1> &tip) : origin(origin), tip(tip) {
    LAVector3d::tip = tip;
    LAVector3d::origin = origin;
    LAVector3d::color = Matrix<float, 3, 1>{{255, 0, 0}};
}

const Matrix<float, 3, 1> &LAVector3d::getOrigin() const {
    return origin;
}

void LAVector3d::setOrigin(const Matrix<float, 3, 1> &origin) {
    LAVector3d::origin = origin;
}

const Matrix<float, 3, 1> &LAVector3d::getTip() const {
    return tip;
}

void LAVector3d::setTip(const Matrix<float, 3, 1> &tip) {
    LAVector3d::tip = tip;
}

const Matrix<float, 3, 1> &LAVector3d::getColor() const {
    return color;
}

void LAVector3d::setColor(const Matrix<float, 3, 1> &color) {
    LAVector3d::color = color;
}

LAVector3d *LAVector3d::getNextVector() const {
    return nextVector;
}

void LAVector3d::setNextVector(LAVector3d *nextVector) {
    LAVector3d::nextVector = nextVector;
}

LAVector3d::LAVector3d(LAVector3d *nextVector, const Matrix<float, 3, 1> &tip) : nextVector(nextVector), tip(tip) {
    LAVector3d::origin = nextVector->getTip();
    LAVector3d::tip = tip + nextVector->getTip();
    LAVector3d::color = Matrix<float, 3, 1>{{255, 0, 0}};
}

