cmake_minimum_required(VERSION 3.16)

project(hmmm C)

set(SOURCE_FILES src/main.c
        src/config.h
        src/utilities.h
        src/utilities.c
        src/config.c)
set(INCLUDE_DIR include)
set(RAYLIB_DIR ${CMAKE_SOURCE_DIR}/lib)

add_executable(hmmm ${SOURCE_FILES})

target_include_directories(hmmm PRIVATE ${INCLUDE_DIR})
target_link_libraries(hmmm PUBLIC -lm)
target_link_libraries(hmmm PRIVATE ${RAYLIB_DIR}/libraylib.a)
