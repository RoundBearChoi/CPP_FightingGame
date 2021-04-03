cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

project(CPPFightingGame)

add_executable(CPPFightingGame
AnimationController.cpp
BackgroundGroup.cpp
Camera.cpp
DevSettings.cpp
FightersGroup.cpp
FightScene.cpp
GameObj.cpp
InputBuffer.cpp
main.cpp
Scene.cpp
SceneController.cpp
SpriteLoader.cpp
State.cpp
StateController.cpp
)

target_link_libraries(CPPFightingGame -lX11 -lGL -lpthread -lpng -lstdc++fs)
