cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

# change name of project here
project(app LANGUAGES CXX)

Option(BUILD_TEST "Build unittest" OFF)


add_library(${PROJECT_NAME}_header INTERFACE)
target_include_directories(${PROJECT_NAME}_header INTERFACE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/third-party
)

add_library(volume_allocation STATIC
  src/volume_allocation/VolumeAllocation.cpp
)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    src/main.cpp
)

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE
  ${CMAKE_THREAD_LIBS_INIT}
)

# unittests
if (BUILD_TEST)
    add_subdirectory("test")
endif()
