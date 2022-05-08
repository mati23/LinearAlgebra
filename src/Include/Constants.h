//
// Created by Mateus on 5/6/2022.
//

#ifndef LINEARALGEBRA_CONSTANTS_H
#define LINEARALGEBRA_CONSTANTS_H


class Constants{
public:
    int WINDOW_X_POS = 500;
    int WINDOW_Y_POS =500;

    static const int WINDOW_X_SIZE = 1280;
    static const int WINDOW_Y_SIZE = 800;
    static const int ORIGIN_X = WINDOW_X_SIZE / 2;
    static const int ORIGIN_Y = (WINDOW_Y_SIZE / 2);
    static const int ASPECT = (WINDOW_Y_SIZE / WINDOW_X_SIZE);
    constexpr static const float VIEW_DEGREE = (90 * (M_PI / 180.0));
    constexpr static const float ZFAR = 100;
    constexpr static const float ZNEAR = 10;

};
#endif //LINEARALGEBRA_CONSTANTS_H
