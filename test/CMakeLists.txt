project(Project-tests)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_FLAGS "-Wall -Werror -Wpedantic")
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wpedantic")
set(CMAKE_CXX_STANDARD 14)

add_link_options(-lsfml-graphics -lsfml-window -lsfml-system)

add_subdirectory("../Game" "./gamelib")
add_subdirectory("../Level" "./levellib")

find_package(GTest REQUIRED)

add_executable(test test.cpp)

target_link_directories(test PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/../Game")

target_include_directories(test PUBLIC
                                "${PROJECT_BINARY_DIR}"
                                "${PROJECT_SOURCE_DIR}/../Game/include")
target_link_libraries(test sfml-graphics sfml-window sfml-system ${GTEST_LIBRARIES} pthread Game)