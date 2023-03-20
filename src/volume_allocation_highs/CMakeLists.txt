cmake_minimum_required(VERSION 3.18)

project(va_highs LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    highs
    GIT_REPOSITORY "https://github.com/ERGO-Code/HiGHS.git"
    GIT_TAG        "bazel"
)
set(FAST_BUILD ON CACHE INTERNAL "Fast Build")

FetchContent_MakeAvailable(highs)

add_executable(${PROJECT_NAME} va_main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE /usr/local/include/highs)
find_package(ZLIB REQUIRED)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE highs::highs ZLIB::ZLIB Threads::Threads)
