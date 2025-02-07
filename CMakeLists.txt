cmake_minimum_required(VERSION 3.26.3)

set(CMAKE_TOOLCHAIN_FILE "D:/Programs/VisualStudio/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set(CMAKE_PREFIX_PATH "D:/Programs/VisualStudio/vcpkg/installed/x64-mingw-static/share")
set(VCPKG_TARGET_TRIPLET "x64-mingw-static" CACHE STRING "Vcpkg triplet")
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")

project(kaban)

add_executable(${PROJECT_NAME} src/main.cpp src/input_handler.cpp src/renderer.cpp src/game.cpp src/board.cpp) 

target_include_directories(kaban PRIVATE include)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL glfw imgui::imgui GTest::gtest)