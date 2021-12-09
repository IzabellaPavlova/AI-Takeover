project(tests)
cmake_minimum_required(VERSION 3.16)

add_link_options(-lsfml-graphics -lsfml-window -lsfml-system)

find_package(GTest REQUIRED)
include_directories("../include/")

set(SOURCE ../src/ChooseLevelMenuScene.cpp ../src/Game.cpp ../src/GameplayScene.cpp ../src/Level ../src/MainMenuScene.cpp ../src/PauseScene.cpp ../src/SceneManager.cpp)

add_executable(test test.cpp ${SOURCE} ${HEADERS})
target_link_libraries(test ${GTEST_LIBRARIES} pthread)
target_link_libraries(test sfml-graphics sfml-window sfml-system)