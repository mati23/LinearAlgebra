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
Array<int, 3, 1> GREEN{{0, 255, 0}};
Array<int, 3, 1> BLUE{{0, 0, 255}};

unordered_map<string, Matrix<float, 2, 1>> RemoveResultVectors(unordered_map<string, Matrix<float, 2, 1>> arrayOfVectors) {
    unordered_map<string, Matrix<float, 2, 1>>::const_iterator got = arrayOfVectors.find("result");
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
    LAVector3d *vec1 = new LAVector3d({0, 200});
    LAVector3d *vec2 = new LAVector3d({200, 0});
    unordered_map<string, Matrix<float, 2, 1>> arrayOfVectors;

    if (this->getWindow() == NULL) {
        printf("Coundn't initialize window");
        return 1;
    }
    SDL_Event event;
    int count = 0;
    bool showTransformationMatrix = false;
    while (this->getRunning()) {
        RemoveResultVectors(arrayOfVectors);
        if (count < 360) {
            //printf("counter %i", count);
            count++;
        } else {
            count = 0;
        }

        float degree = (count * (M_PI / 180.0));

        Matrix<float, 2, 2> transformationMatrix
                {{(float) cos(degree), (float) -sin(degree)},
                 {(float) sin(degree), (float) cos(degree)}};

        SDL_Texture *texture = SDL_CreateTexture(this->getRenderer(), SDL_PIXELFORMAT_RGBA8888,
                                                 SDL_TEXTUREACCESS_TARGET, 50, 10);
        if (!arrayOfVectors.count("vec1")) {
            arrayOfVectors.insert(pair<string, Matrix<float, 2, 1>>{"vec1", vec1->getTip()});
            arrayOfVectors.insert(pair<string, Matrix<float, 2, 1>>{"vec2", vec2->getTip()});
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
                                pair<string, Matrix<float, 2, 1>>{"result", vec1->getTip() + vec2->getTip()});
                    }
                    break;

                case SDL_SCANCODE_R:
                    printf("Removing vectors");
                    RemoveResultVectors(arrayOfVectors);
                    break;

                case SDL_SCANCODE_T:
                    printf("Transforming vectors");
                    RemoveResultVectors(arrayOfVectors);
                    showTransformationMatrix = true;
                    break;

            }
        }
        SDL_SetRenderDrawColor(this->getRenderer(), 0, 255, 0, SDL_ALPHA_OPAQUE);
        this->PrintGrid(this->getRenderer());

        if (showTransformationMatrix) {
            Matrix<float, 2, 1> result = transformationMatrix * vec1->getTip();
            arrayOfVectors = RemoveResultVectors(arrayOfVectors);
            arrayOfVectors.insert(pair<string, Matrix<float, 2, 1>>{"result", result});
            printf("\n %f %f \n", result(0), result(1));
        }


        for (pair<string, Array<float, 2, 1>> vect: arrayOfVectors) {
            printf("%s \n ", vect.first.c_str());
            if (vect.first == "result") {
                printf("\n %f %f \n", vect.second(0), vect.second(1));
                vec1->RenderDrawLine(this->getRenderer(), vect.second, BLUE);
            } else {
                vec1->RenderDrawLine(this->getRenderer(), vect.second, RED);
            }

        }

        SDL_RenderPresent(this->getRenderer());
        SDL_Delay(100);
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
