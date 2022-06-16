cmake_minimum_required (VERSION 3.18)
project (pds1final)

include(FetchContent)

add_library(pinball SHARED
    src/aabb.c
    src/glue.c
    src/sprites.c
    src/loop.c
    src/resource.c
    src/sprite.c
)

target_include_directories(pinball PRIVATE include/bits)

set(CMAKE_INSTALL_PREFIX "./out")

FetchContent_Declare(allegro5 URL https://github.com/liballeg/allegro5/releases/download/5.2.8.0/allegro-5.2.8.0.tar.gz)
FetchContent_MakeAvailable(allegro5)

get_target_property(allegro_SOURCE_DIR allegro SOURCE_DIR)
get_target_property(allegro_BINARY_DIR allegro BINARY_DIR)
include_directories(
    include
    ${allegro_SOURCE_DIR}/include
    ${allegro_BINARY_DIR}/include
    ${allegro_SOURCE_DIR}/addons/image
    ${allegro_SOURCE_DIR}/addons/font
    )
    
if(WANT_MONOLITH)
    target_link_libraries(pinball
        allegro_monolith
    )
else(WANT_MONOLITH)
    target_link_libraries(pinball
        allegro
        allegro_image
        allegro_font
    )
endif(WANT_MONOLITH)

if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(pinball PRIVATE ALLEGRO_STATICLINK)
endif(NOT BUILD_SHARED_LIBS)


add_executable(pds1final src/main.c)
target_include_directories(pds1final PRIVATE include)

target_link_libraries(pds1final PRIVATE pinball)