//
// Created by Mateus on 5/6/2022.
//

#include "../Include/Application.h"
#include "../Include/Constants.h"
#include "../Include/LAVector3d.h"
#include <stdio.h>
#include <iostream>
#include <iterator>
#include <list>
#include <SDL.h>
#include <windows.h>
#include <Eigen/Dense>
#include <unordered_map>
#include <cmath>

using namespace std;
using namespace Eigen;

Array<int, 3, 1> RED{{255, 0, 0}};
Matrix<int, 3, 1> GREEN {{0}, {255}, {0}};
Array<int, 3, 1> BLUE{{0, 0, 255}};

unordered_map<string, Matrix<float, 3, 1>>
RemoveResultVectors(unordered_map<string, Matrix<float, 3, 1>> arrayOfVectors) {
    unordered_map<string, Matrix<float, 3, 1>>::const_iterator got = arrayOfVectors.find("result");
    if (got != arrayOfVectors.end()) {
        //printf("array removed");
        arrayOfVectors.erase("result");
    }
    return arrayOfVectors;
}

void Application::setRunning(int value) {
    running = value;
}

int Application::getRunning() {
    return running;
}

Application::Application() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Linear Algebra", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              Constants::WINDOW_X_SIZE, Constants::WINDOW_Y_SIZE, SDL_WINDOW_OPENGL);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Application::PrintGrid(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer, 0, Constants::WINDOW_Y_SIZE / 2, Constants::WINDOW_X_SIZE,
                       Constants::WINDOW_Y_SIZE / 2);
    SDL_RenderDrawLine(renderer, Constants::WINDOW_X_SIZE / 2, 0, Constants::WINDOW_X_SIZE / 2,
                       Constants::WINDOW_Y_SIZE);

    SDL_SetRenderDrawColor(renderer, 25, 25, 25, SDL_ALPHA_TRANSPARENT);
    for (int i = 1; i <= (Constants::WINDOW_Y_SIZE / 100 + 1); i++) {
        SDL_RenderDrawLine(renderer, 0, Constants::WINDOW_Y_SIZE / 2 + i * 100, Constants::WINDOW_X_SIZE,
                           Constants::WINDOW_Y_SIZE / 2 + i * 100);
        SDL_RenderDrawLine(renderer, 0, Constants::WINDOW_Y_SIZE / 2 - i * 100, Constants::WINDOW_X_SIZE,
                           Constants::WINDOW_Y_SIZE / 2 - i * 100);
    }
    for (int i = 1; i <= (Constants::WINDOW_X_SIZE / 100 + 1); i++) {
        SDL_RenderDrawLine(renderer, Constants::WINDOW_X_SIZE / 2 + i * 100, 0, Constants::WINDOW_X_SIZE / 2 + i * 100,
                           Constants::WINDOW_Y_SIZE);
        SDL_RenderDrawLine(renderer, Constants::WINDOW_X_SIZE / 2 - i * 100, 0, Constants::WINDOW_X_SIZE / 2 - i * 100,
                           Constants::WINDOW_Y_SIZE);
    }
}

SDL_Window *Application::getWindow() const {
    return window;
}

void Application::setWindow(SDL_Window *window) {
    Application::window = window;
}

SDL_Renderer *Application::getRenderer() const {
    return renderer;
}

void Application::setRenderer(SDL_Renderer *renderer) {
    Application::renderer = renderer;
}

int Application::Run() {
    LAVector3d *vec1 = new LAVector3d({30, 30, 30},{-30, 30, 30}, {255, 0, 0});
    LAVector3d *vec2 = new LAVector3d(vec1, {-30, -30, 30}, {255, 0, 0});
    LAVector3d *vec3 = new LAVector3d(vec2, {30, -30, 30}, {255, 0, 0});
    LAVector3d *vec4 = new LAVector3d(vec3, {30, 30, 30}, {255, 0, 0});

    LAVector3d *vec5 = new LAVector3d(vec4, {30, 30, -30}, {0, 255, 0});


    LAVector3d *vec6 = new LAVector3d(vec5, {-30, 30, -30}, {0, 0, 255});
    LAVector3d *vec7 = new LAVector3d(vec6, {-30, -30, -30}, {0, 0, 255});
    LAVector3d *vec8 = new LAVector3d(vec7, {-30, -30, -30}, {0, 0, 255});
    LAVector3d *vec9 = new LAVector3d(vec8, {30, -30, -30}, {0, 0, 255});
    LAVector3d *vec10 = new LAVector3d(vec9, {30, 30, -30}, {0, 0, 255});

    LAVector3d *vec20 = new LAVector3d(vec9, {-30, -30, -30}, {0, 0, 255});

    LAVector3d *vec2_7 = new LAVector3d(vec2, vec7->getTip(), {0, 255, 0});
    LAVector3d *vec3_9 = new LAVector3d(vec3, vec9->getTip(), {0, 255, 0});
    LAVector3d *vec4_10 = new LAVector3d(vec1, vec6->getTip(), {0, 255, 0});


    vectorList.insert(vectorList.end(),vec1);
    vectorList.insert(vectorList.end(),vec2);
    vectorList.insert(vectorList.end(),vec3);
    vectorList.insert(vectorList.end(),vec4);
    vectorList.insert(vectorList.end(),vec5);
    vectorList.insert(vectorList.end(),vec6);
    vectorList.insert(vectorList.end(),vec7);
    vectorList.insert(vectorList.end(),vec8);
    vectorList.insert(vectorList.end(),vec9);
    vectorList.insert(vectorList.end(),vec10);
    vectorList.insert(vectorList.end(),vec20);
    vectorList.insert(vectorList.end(),vec2_7);
    vectorList.insert(vectorList.end(),vec3_9);
    vectorList.insert(vectorList.end(),vec4_10);

    unordered_map<string, Matrix<float, 3, 1>> arrayOfVectors;

    if (this->getWindow() == NULL) {
        printf("Coundn't initialize window");
        return 1;
    }
    SDL_Event event;
    int count = 0;
    bool showTransformationMatrix = false;
    Uint64 start;
    Uint64 end;
    float elapsedMS;
    while (this->getRunning()) {
        start = SDL_GetPerformanceCounter();

        RemoveResultVectors(arrayOfVectors);
        if (count < 360) {
            //printf("counter %i", count);
            count++;
        } else {
            count = 0;
        }

        float degree = (count * (M_PI / 180.0));

        Matrix<float, 3, 3> transformationMatrixX
                {{(float) 1, 0, 0},
                 {0, (float) cos(degree), (float) -sin(degree)},
                 {0, (float) sin(degree), (float) cos(degree)}};

        Matrix<float, 3, 3> transformationMatrixY
                {{(float) cos(degree), 0, (float) -sin(degree)},
                 {0, 1, 0},
                 {(float) -sin(degree), 0, (float) cos(degree)}};

        SDL_Texture *texture = SDL_CreateTexture(this->getRenderer(), SDL_PIXELFORMAT_RGBA8888,
                                                 SDL_TEXTUREACCESS_TARGET, 50, 10);
        if (!arrayOfVectors.count("vec1")) {
            arrayOfVectors.insert(pair<string, Matrix<float, 3, 1>>{"vec1", vec1->getTip()});
            arrayOfVectors.insert(pair<string, Matrix<float, 3, 1>>{"vec2", vec2->getTip()});
        }


        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    this->setRunning(false);
            }
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_P:
                    if (!arrayOfVectors.count("result")) {
                        arrayOfVectors.insert(
                                pair<string, Matrix<float, 3, 1>>{"result", vec1->getTip() + vec2->getTip()});
                    }
                    break;

                case SDL_SCANCODE_R:
                    printf("Removing vectors");
                    RemoveResultVectors(arrayOfVectors);
                    break;

                case SDL_SCANCODE_T:
                    printf("Transforming vectors");
                    showTransformationMatrix = true;
                    break;

            }
        }
        SDL_SetRenderDrawColor(this->getRenderer(), 0, 255, 0, SDL_ALPHA_OPAQUE);
        this->PrintGrid(this->getRenderer());

        if (true) {
            std::list<LAVector3d>::iterator it;
            for (const auto& vec : vectorList){
                Matrix<float, 3, 1> resultTip = (transformationMatrixX) * vec->getTip();
                Matrix<float, 3, 1> resultOrigin = (transformationMatrixX ) * vec->getOrigin();

                resultTip = (transformationMatrixY) * resultTip;
                resultOrigin = (transformationMatrixY ) * resultOrigin;

                LAVector3d* vectorToPrint = new LAVector3d(resultOrigin,resultTip, vec->getColor());
                printf("vec %i ---- origin: %f, %f; tip: %f, %f, color: %i, %i, %i\n", count, vec->getOrigin()(0), vec->getOrigin()(1), vec->getTip()(0), vec->getTip()(1), vec->getColor()(0), vec->getColor()(1), vec->getColor()(2));
                vectorsToPrint.insert(vectorsToPrint.end(),vectorToPrint);
            }
            int count = 1;
            for (const auto& vec : vectorsToPrint){
                //printf("vec %i ---- origin: %f, %f; tip: %f, %f, color: %i, %i, %i\n", count, vec->getOrigin()(0), vec->getOrigin()(1), vec->getTip()(0), vec->getTip()(1), vec->getColor()(0), vec->getColor()(1), vec->getColor()(2));
                vec->RenderDrawLine(this->getRenderer(), vec, vec->getColor() );
                count++;
            }
            vectorsToPrint.clear();
        }

        SDL_RenderPresent(this->getRenderer());

        end = SDL_GetPerformanceCounter();
        elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency();
        SDL_Delay(floor(8.666f - elapsedMS));
    }
    SDL_DestroyRenderer(this->getRenderer());
    SDL_DestroyWindow(this->getWindow());

    SDL_Quit();

    return 0;
}

const list<LAVector3d *> &Application::getVectorList() const {
    return vectorList;
}

void Application::setVectorList(const list<LAVector3d *> &vectorList) {
    Application::vectorList = vectorList;
}

const list<LAVector3d *> &Application::getVectorsToPrint() const {
    return vectorsToPrint;
}

void Application::setVectorsToPrint(const list<LAVector3d *> &vectorsToPrint) {
    Application::vectorsToPrint = vectorsToPrint;
}

void Application::clearVectorsToPrint() {
    vectorsToPrint.clear();
}
