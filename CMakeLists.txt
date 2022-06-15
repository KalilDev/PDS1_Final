cmake_minimum_required (VERSION 3.18)
project (pds1final)

add_library(libpinball src/sprites.c)
target_include_directories(libpinball PRIVATE include/bits)

add_executable(pds1final src/main.c)
target_include_directories(pds1final PRIVATE include)

target_link_libraries(pds1final PRIVATE libpinball)