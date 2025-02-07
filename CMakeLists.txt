cmake_minimum_required(VERSION 3.26.3)

set(CMAKE_TOOLCHAIN_FILE "D:/Programs/VisualStudio/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set(CMAKE_PREFIX_PATH "D:/Programs/VisualStudio/vcpkg/installed/x64-mingw-static/share")

project(kaban)

add_executable(${PROJECT_NAME} src/main.cpp) 

#set(CMAKE_TOOLCHAIN_FILE "D:/Programs/VisualStudio/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
#set(CMAKE_PREFIX_PATH "D:/Programs/VisualStudio/vcpkg/installed/x64-windows/share")
#add_subdirectory(D:/Programs/VisualStudio/vcpkg/installed/x64-windows/share/glfw3)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL glfw imgui::imgui GTest::gtest )