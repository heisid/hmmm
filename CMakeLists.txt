cmake_minimum_required(VERSION 3.16)

project(hmmm C)

set(CMAKE_C_COMPILER gcc)
set(SOURCE_FILES src/main.c)
if (UNIX AND NOT APPLE)
    set(PLATFORM_DIR linux)
elseif (WIN32)
    set(PLATFORM_DIR windows)
endif ()

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/${PLATFORM_DIR}/include)
set(RAYLIB_LIB_DIR ${CMAKE_SOURCE_DIR}/${PLATFORM_DIR}/lib)

add_executable(hmmm ${SOURCE_FILES})

target_include_directories(hmmm PRIVATE ${INCLUDE_DIR})
if (UNIX AND NOT APPLE)
    target_link_libraries(hmmm PUBLIC -lm)
endif ()

target_link_libraries(hmmm PRIVATE ${RAYLIB_LIB_DIR}/libraylib.a)

if (WIN32)
    target_link_libraries(hmmm PUBLIC -lwinmm)
endif()