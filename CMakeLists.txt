project(AI-Takeover)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_FLAGS "-Wall -Werror -Wpedantic")
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wpedantic")
set(CMAKE_CXX_STANDARD 14)

ADD_SUBDIRECTORY( Level )
ADD_SUBDIRECTORY( Game )

add_executable(main Main.cpp ${SOURCE} ${HEADERS})

target_link_libraries(main sfml-graphics sfml-window sfml-system Level Game)
target_include_directories(main PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/Game/include")