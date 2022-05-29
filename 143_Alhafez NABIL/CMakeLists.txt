cmake_minimum_required(VERSION 3.21)
project(colocviu)

set(CMAKE_CXX_STANDARD 14)

add_executable(colocviu main.cpp collections/enumerable.h collections/IoBase.h collections/functions.cpp collections/functions.h collections/biletele.h collections/date.h collections/cardurile.h)
