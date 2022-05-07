cmake_minimum_required(VERSION 3.22)
project(linearalgebra)

set(CMAKE_CXX_STANDARD 14)
set(SDL2_INCLUDE_DIR C:/SDL2/include)
set(EIGEN_INCLUDE_DIR C:/eigen)
set(SDL2_LIB_DIR C:/SDL2/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(linearalgebra main.cpp src/Model/LAVector3d.cpp src/Include/LAVector3d.h src/Model/Application.cpp src/Include/Application.h src/Include/Constants.h)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)
include_directories(${EIGEN_INCLUDE_DIR})