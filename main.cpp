#include <stdio.h>
#include <iostream>
#include <iterator>
#include <list>
#include <SDL.h>
#include <windows.h>
#include <Eigen/Dense>
#include <unordered_map>
#include <cmath>
#include "src/Include/Application.h"
#include "src/Include/Constants.h"
#include "src/Include/LAVector3d.h"
#include <list>

using namespace std;
using namespace Eigen;

int main(int argc, char *args[]) {
    Application application;
    application.setRunning(true);

    bool running = true;

    LAVector3d* vec1 = new LAVector3d({0, 200});
    LAVector3d* vec2 = new LAVector3d({200, 0});

    std::list<LAVector3d*> vectorList;
    std::list<LAVector3d*>::iterator it;

    it = vectorList.begin();
    vectorList.insert(it, vec1);
    vectorList.insert(it, vec2);

    application.setVectorList(vectorList);

    unordered_map<string, Matrix<float, 2, 1>> arrayOfVectors;

    application.Run();

    return 0;
}