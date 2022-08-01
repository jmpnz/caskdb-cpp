cmake_minimum_required(VERSION 3.2)

project(caskdb LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
# compiler options
add_compile_options(-g -fPIC)
# lots of warnings and errors.
add_compile_options(-Wall -Wextra -pedantic -Werror)

include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/test")
add_subdirectory(src)

# build the test executable
find_package(doctest REQUIRED)

# Make test executable
add_executable(test test/main.cpp src/file_manager.cpp) 
target_compile_features(test PRIVATE cxx_std_17)
target_link_libraries(test PRIVATE doctest::doctest)# build the main caskdb executable

# build the binary
add_executable(caskdb src/main.cpp)
target_include_directories(caskdb PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(caskdb libcaskdb)

target_link_libraries(libcaskdb ${extra_libs})

# setup clang-tidy
# clang-tidy
if (NOT DEFINED CLANG_TIDY_BIN)
    # attempt to find the binary if user did not specify
    find_program(CLANG_TIDY_BIN
            NAMES clang-tidy clang-tidy-12)
endif()
if ("${CLANG_TIDY_BIN}" STREQUAL "CLANG_TIDY_BIN-NOTFOUND")
    message(WARNING "casdkdb/main couldn't find clang-tidy.")
else()
    # Output compile_commands.json
    set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
    message(STATUS "caskdb/main found clang-tidy at ${CLANG_TIDY_BIN}")
endif()