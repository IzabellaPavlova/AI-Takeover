project(Level)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_FLAGS "-Wall -Werror -Wpedantic")
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wpedantic")
set(CMAKE_CXX_STANDARD 14)

add_link_options(-lsfml-graphics -lsfml-window -lsfml-system)

set(SOURCE src/Level src/Finish.cpp src/Map.cpp src/Hero.cpp)
include_directories("include/")

add_library(Level STATIC ${SOURCE} ${HEADERS})

target_include_directories(Level PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Level sfml-graphics sfml-window sfml-system)