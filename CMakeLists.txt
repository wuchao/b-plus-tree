cmake_minimum_required(VERSION 3.14)
project(b_plus_tree C)

set(CMAKE_C_STANDARD 99)

add_executable(b_plus_tree src/main.c src/BPlusTree.c h/BPlusTree.h)