cmake_minimum_required(VERSION 3.2)

project(caskdb)

set(CMAKE_CXX_STANDARD 17)
# compiler go brr
add_compile_options(-O3 -fPIC)
# lots of warnings and errors.
add_compile_options(-Wall -Wextra -pedantic -Werror)

include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/test")
add_subdirectory(src)

# build the test executable
add_executable(caskdb_test test/main.cpp)
target_include_directories(caskdb_test PUBLIC "${PROJECT_SOURCE_DIR}/include")

# build the main caskdb executable
add_executable(caskdb src/main.cpp)
target_include_directories(caskdb PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(caskdb libcaskdb)

# build the unit tests
#add_definitions("-DGTEST_HAS_PTHREAD=0")
# add_executable(caskdb_test)
  
target_link_libraries(libcaskdb ${extra_libs})
