cmake_minimum_required(VERSION 3.9)
project(2ndtest_mastersscholarshipinrobotics_sokolovmaxim)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(2ndtest_mastersscholarshipinrobotics_sokolovmaxim
        "Connection.h"
        "EN_TestTaskControl _.docx"
        "input.in"
        Connection.cpp
        main.cpp
        Joint.cpp)
