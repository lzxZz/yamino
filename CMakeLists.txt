cmake_minimum_required(VERSION 3.0)

project(yamino CXX)

include_directories(
    yamino
)

aux_source_directory(yamino SRCS)

add_executable(yamino ${SRCS})