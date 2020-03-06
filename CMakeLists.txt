cmake_minimum_required(VERSION 3.15)
project(HeartTrace)

set(CMAKE_CXX_STANDARD 20)

add_executable(HeartTrace main.cpp Image.h matrix/Matrix.h matrix/Vec.h util/Json.h util/File.h)