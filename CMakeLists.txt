cmake_minimum_required(VERSION 2.6)

project(caskdb)

include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/test")
add_subdirectory(src)

# build the main barevm executable
add_executable(caskdb src/main.cpp)
target_link_libraries(caskdb libcaskdb)

# build the unit tests
#add_definitions("-DGTEST_HAS_PTHREAD=0")
# add_executable(caskdb_test)
  
target_link_libraries(libcaskdb ${extra_libs})
