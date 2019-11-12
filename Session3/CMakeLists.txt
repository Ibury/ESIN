

# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 3.0)
project (Session3)

set(EXECUTABLE_OUTPUT_PATH "build")
add_executable (mcj_enters.e mcj_enters.cpp)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -c")

add_compile_options(
  "-Wall" "-ansi" "-g" "-c"
)


