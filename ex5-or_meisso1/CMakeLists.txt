cmake_minimum_required(VERSION 3.22)
project(ex5_or_meisso1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex5_or_meisso1
        Movie.cpp
        Movie.h
        print_main.cpp
        RecommendationSystem.h
        RecommendationSystem.cpp
        RecommendationSystemLoader.cpp
        RecommendationSystemLoader.h
        User.cpp
        User.h
        UsersLoader.cpp
        UsersLoader.h RecommendationSystem.cpp RecommendationSystem.cpp presubmit.cpp)
