cmake_minimum_required(VERSION 3.15)

project(SpaceInvaders VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib CONFIG REQUIRED)
include_directories(include)

file(GLOB SOURCES "src/*.cpp" "src/manager/*.cpp" "src/sprite/*.cpp" "src/ui/*.cpp" "src/utils/*.cpp")
add_executable(game ${SOURCES})

target_link_libraries(game PRIVATE raylib)
