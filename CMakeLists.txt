cmake_minimum_required(VERSION 3.15)
project(2)

set(CMAKE_CXX_STANDARD 14)

SET(MYCOMPILE_FLAGS "-lsfml-graphics -lsfml-window -lsfml-system")


set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.4 COMPONENTS graphics audio REQUIRED)


add_executable(2 main.cpp Animation.cpp Entity.cpp Player.cpp Asteroid.cpp Game.cpp Bullet.cpp)


add_definitions(${MYCOMPILE_FLAGS} "-lsfml-graphics -lsfml-window -lsfml-system")
target_link_libraries(2 sfml-graphics sfml-audio)