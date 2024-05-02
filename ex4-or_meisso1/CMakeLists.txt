cmake_minimum_required(VERSION 3.22)
project(ex4_or_meisso1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex4_or_meisso1
        Activation.cpp
        Activation.h
        Dense.cpp
        Dense.h
        main.cpp
        Matrix.cpp
        Matrix.h
        MlpNetwork.cpp
        MlpNetwork.h)
