cmake_minimum_required(VERSION 3.26)

set(PROJECT_NAME "kaban")
set(APP_LIB_NAME "kaban_lib")

set(CMAKE_TOOLCHAIN_FILE "C:/Tools/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_TARGET_TRIPLET "x64-mingw-static")
set(CMAKE_PREFIX_PATH "C:/Tools/vcpkg/installed/x64-mingw-static/share")

project(${PROJECT_NAME})

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
)
set(gtest_force_shared_crt ON CACHE STRING "" FORCE)
FetchContent_MakeAvailable(googletest)
option(BUILD_TESTS "Build tests" OFF)
enable_testing()


file(GLOB_RECURSE APP_MAIN "src/main.cpp")
file(GLOB_RECURSE APP_SOURCES "src/*.cpp")
list(REMOVE_ITEM APP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
file(GLOB_RECURSE TESTS_SOURCES "tests/*.cpp")

set(NECESSARY_LIBS OpenGL::GL glfw imgui::imgui)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(Stb REQUIRED)


include_directories(include)
include_directories("C:/Tools/vcpkg/installed/x64-mingw-static/include")


add_library(${APP_LIB_NAME} STATIC ${APP_SOURCES})
target_link_libraries(${APP_LIB_NAME} PRIVATE ${NECESSARY_LIBS})


add_executable(${PROJECT_NAME} ${APP_MAIN})
target_link_libraries(${PROJECT_NAME} PRIVATE ${APP_LIB_NAME} ${NECESSARY_LIBS})


add_executable(tests ${TESTS_SOURCES})
target_link_libraries(tests PRIVATE ${APP_LIB_NAME} ${NECESSARY_LIBS} GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)