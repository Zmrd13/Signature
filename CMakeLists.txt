cmake_minimum_required(VERSION 3.23)
project(Submit)

set(CMAKE_CXX_STANDARD 14)

add_executable(Submit main.cpp FileToVecClass.h cryptEssential.h cmake-build-debug/Signature.h src/md5.cpp src/md5.h)
