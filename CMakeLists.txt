project(AI-Takeover-game)

cmake_minimum_required(VERSION 3.16)

add_link_options(-lsfml-graphics -lsfml-window -lsfml-system)

set(HEADER_FILES Tail/Tail.hpp Map/map.hpp Button/Button.hpp)
set(SOURCE Tail/Tail.cpp Map/Map.cpp Button/Button.cpp main.cpp)

add_executable(main ${SOURCE} ${HEADERS})

target_link_libraries(main sfml-graphics sfml-window sfml-system)