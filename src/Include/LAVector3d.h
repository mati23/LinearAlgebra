//
// Created by Mateus on 5/6/2022.
//
#include <Eigen/Dense>
#include <SDL.h>
#ifndef LINEARALGEBRA_VECTOR3D_H
#define LINEARALGEBRA_VECTOR3D_H

using namespace Eigen;

class LAVector3d {
private:
    Matrix<float, 2, 1> origin;
    Matrix<float, 2, 1> tip;
    Matrix<float, 3, 1> color;
public:
    LAVector3d();

    LAVector3d(const Matrix<float, 2, 1> &tip);

    LAVector3d(const Matrix<float, 2, 1> &origin, const Matrix<float, 2, 1> &tip);

public:
    int _cdecl RenderDrawLine(SDL_Renderer* renderer, Matrix<float, 2, 1> vec, Array<int,3,1> color);
    void SetVectorColor(SDL_Renderer* renderer, Array<int, 3, 1> color);
    void drawcircle(SDL_Renderer* renderer, int x0, int y0, int radius);

    const Matrix<float, 2, 1> &getOrigin() const;

    void setOrigin(const Matrix<float, 2, 1> &origin);

    const Matrix<float, 2, 1> &getTip() const;

    void setTip(const Matrix<float, 2, 1> &tip);

    const Matrix<float, 3, 1> &getColor() const;

    void setColor(const Matrix<float, 3, 1> &color);
};


#endif //LINEARALGEBRA_VECTOR3D_H
