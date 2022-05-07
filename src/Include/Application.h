//
// Created by Mateus on 5/6/2022.
//

#include <stdio.h>
#include <iostream>
#include <iterator>
#include <list>
#include <SDL.h>
#include <windows.h>
#include <Eigen/Dense>
#include <unordered_map>
#include <cmath>
#include "../Include/LAVector3d.h"

#ifndef LINEARALGEBRA_APPLICATION_H
#define LINEARALGEBRA_APPLICATION_H


class Application {
private:
    bool running;
    SDL_Window* window;
    std::list<LAVector3d*> vectorList;
    std::list<LAVector3d*> vectorsToPrint;
public:
    const std::list<LAVector3d *> &getVectorList() const;

    void setVectorList(const std::list<LAVector3d *> &vectorList);

public:
    Application();
    int Run();

private:
    SDL_Renderer* renderer;

public:
    void setRunning(int value);
    int getRunning();

    SDL_Window *getWindow() const;

    void setWindow(SDL_Window *window);

    SDL_Renderer *getRenderer() const;

    void setRenderer(SDL_Renderer *renderer);

    void PrintGrid(SDL_Renderer* renderer );

    const std::list<LAVector3d *> &getVectorsToPrint() const;

    void setVectorsToPrint(const std::list<LAVector3d *> &vectorsToPrint);

    void clearVectorsToPrint();
};


#endif //LINEARALGEBRA_APPLICATION_H
