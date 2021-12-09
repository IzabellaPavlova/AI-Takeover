project(Game)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_FLAGS "-Wall -Werror -Wpedantic")
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wpedantic")
set(CMAKE_CXX_STANDARD 14)

add_link_options(-lsfml-graphics -lsfml-window -lsfml-system)

include_directories("include/")
set(SOURCE src/Gui.cpp src/Button.cpp src/Constants.cpp src/Background.cpp src/ChooseLevelMenuScene.cpp src/Game.cpp src/GameplayScene.cpp src/MainMenuScene.cpp src/PauseScene.cpp src/SceneManager.cpp)

add_library(Game STATIC ${SOURCE} ${HEADERS})


target_include_directories(Game PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/../Level/include")
target_link_libraries(Game sfml-graphics sfml-window sfml-system Level)