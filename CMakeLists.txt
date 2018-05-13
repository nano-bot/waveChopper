cmake_minimum_required(VERSION 3.10)
project(waveChopper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wredundant-decls -Wcast-align -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Wextra -Wall -Winvalid-pch -Wredundant-decls -Wmissing-prototypes -Wformat=2 -Wmissing-format-attribute -Wodr -Wformat-nonliteral -std=c++17")

ADD_LIBRARY( lodePNG STATIC "lodePNG/lodepng.cpp" )
target_include_directories(lodePNG PUBLIC ${PROJECT_SOURCE_DIR}/lodePNG)

include_directories("waveChopper/include")

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SOURCE_DIR}/waveChopper/*.cpp ${PROJECT_SOURCE_DIR}/waveChopper/*.h)

add_executable(waveChopper ${SRC_FILES})
TARGET_LINK_LIBRARIES(waveChopper lodePNG "-lstdc++fs")