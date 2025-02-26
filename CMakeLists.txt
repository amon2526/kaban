cmake_minimum_required(VERSION 3.26.3)

set(CMAKE_TOOLCHAIN_FILE "D:/Programs/VisualStudio/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set(VCPKG_TARGET_TRIPLET "x64-mingw-static" CACHE STRING "Vcpkg triplet")
set(CMAKE_PREFIX_PATH "D:/Programs/VisualStudio/vcpkg/installed/x64-mingw-static/share")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(kaban)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB_RECURSE APP_SOURCES "src/*.cpp")
file(GLOB_RECURSE TESTS_SOURCES "tests/*.cpp")
file(GLOB_RECURSE APP_SOURCES_WITHOUT_MAIN "src/*.cpp")
message(${TESTS_SOURCES})
list(REMOVE_ITEM APP_SOURCES_WITHOUT_MAIN "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(Stb REQUIRED)

add_executable(${PROJECT_NAME} ${APP_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE "D:/Programs/VisualStudio/vcpkg/installed/x64-mingw-static/include")
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL glfw imgui::imgui GTest::gtest GTest::gtest_main)


add_library(kaban_lib STATIC ${APP_SOURCES_WITHOUT_MAIN})
target_include_directories(kaban_lib PRIVATE include)
target_include_directories(kaban_lib PRIVATE "D:/Programs/VisualStudio/vcpkg/installed/x64-mingw-static/include")
target_link_libraries(kaban_lib PRIVATE OpenGL::GL glfw imgui::imgui)


add_executable(tests ${TESTS_SOURCES})
target_include_directories(tests PRIVATE include)
target_include_directories(tests PRIVATE "D:/Programs/VisualStudio/vcpkg/installed/x64-mingw-static/include")
target_link_libraries(tests PRIVATE kaban_lib OpenGL::GL glfw imgui::imgui GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
