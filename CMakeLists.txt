cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)
set(NAME TestSanitizer)
project(${NAME} VERSION 0.1.0 LANGUAGES CXX)

include(${CMAKE_CURRENT_BINARY_DIR}/conan_paths.cmake)
include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup(TARGETS NO_OUTPUT_DIRS)
set(CXX /usr/bin/clang++)

set(CMAKE_CXX_STANDARD 14 CACHE STRING "")

add_executable(${NAME} main.cpp)

target_include_directories(${NAME} PUBLIC )

#target_compile_options(${NAME} PUBLIC -fsanitize=thread -stdlib=libstdc++)

set(CMAKE_CXX_FLAG "${CMAKE_CXX_FLAGS} -fsanitize=thread")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=thread")

target_link_libraries(${NAME} CONAN_PKG::libcurl)
