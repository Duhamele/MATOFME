cmake_minimum_required(VERSION 3.28)
project(MOPRIN_Base)

set(CMAKE_CXX_STANDARD 17)
set(FICHIER_SOURCE  Matrix.cpp )
add_library(MOPRIN_Base STATIC ${FICHIER_SOURCE})
