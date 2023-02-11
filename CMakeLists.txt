cmake_minimum_required(VERSION 3.24)
project(interpreter)

set(CMAKE_CXX_STANDARD 17)
#include_directories(/opt/homebrew/Cellar/catch2/3.3.1/include)
#find_package(Catch2 3 REQUIRED)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

include_directories(/lib)


add_executable(lox_test tests/lox_main_test.cpp)
target_link_libraries(lox_test PRIVATE Catch2::Catch2WithMain)

add_executable(interpreter main.cpp lib/scanner.h lib/error/report.h)