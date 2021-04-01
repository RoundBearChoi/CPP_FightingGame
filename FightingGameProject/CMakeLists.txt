cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

project(CPPFightingGame)

add_executable(CPPFightingGame
AnimationController.cpp
Background.cpp
Camera.cpp
DecalLineRenderer.cpp
DevSettings.cpp
Fighters.cpp
FightScene.cpp
GameObj.cpp
InputQueue.cpp
main.cpp
Scene.cpp
SceneController.cpp
SpriteLoader.cpp
StateController.cpp
)

target_link_libraries(CPPFightingGame -lX11 -lGL -lpthread -lpng -lstdc++fs)
