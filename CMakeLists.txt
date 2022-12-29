cmake_minimum_required(VERSION 3.15)
project(LinkControl)

set(CMAKE_CXX_STANDARD 14)

add_executable(LinkControl main.cpp MM2S_1ST_WORD.cpp MM2S_1ST_WORD.h DATA_WORD.cpp DATA_WORD.h S2MM_1ST_WORD.cpp S2MM_1ST_WORD.h)