cmake_minimum_required(VERSION 3.26.3)

set(CMAKE_TOOLCHAIN_FILE "D:/Programs/VisualStudio/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set(CMAKE_PREFIX_PATH "D:/Programs/VisualStudio/vcpkg/installed/x64-mingw-static/share")
set(VCPKG_TARGET_TRIPLET "x64-mingw-static" CACHE STRING "Vcpkg triplet")
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(kaban)

add_executable(${PROJECT_NAME} src/board.cpp src/error_bus.cpp src/game.cpp src/glfw_wrapper.cpp src/imgui_wrapper.cpp src/input_bus.cpp src/main.cpp src/message_bus.cpp src/renderer.cpp) 

target_include_directories(kaban PRIVATE include)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL glfw imgui::imgui GTest::gtest)