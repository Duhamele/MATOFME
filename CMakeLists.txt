cmake_minimum_required(VERSION 3.28)
project(MATOFME)

set(CMAKE_CXX_STANDARD 17)
set(FICHIER_SOURCE  Matrix.cpp )
add_library(MOPRIN_Base STATIC ${FICHIER_SOURCE})
#Test
add_executable(TestMatrix Test/TestMatrix.cpp)
target_link_libraries(TestMatrix MOPRIN_Base)
enable_testing()
