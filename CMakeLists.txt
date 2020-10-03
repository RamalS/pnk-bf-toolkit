cmake_minimum_required(VERSION 3.5)
project(pnk-bf-toolkit VERSION 1.2)

set(library-src
	inc/pnk/bf_toolkit.h
	src/bf_toolkit.c
)

add_executable(test tests/test.c ${library-src})
target_include_directories(test PRIVATE inc)
target_compile_features   (test PRIVATE c_std_11)
