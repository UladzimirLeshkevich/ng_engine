cmake_minimum_required(VERSION 3.12)
project(engine LANGUAGES CXX C)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}../../../build)

add_library(${PROJECT_NAME} SHARED include/engine.hxx
                                   src/engine.cxx
                                   include/timer.hxx
                                   src/timer.cxx
                                   include/animation.hxx
                                   src/animation.cxx
                                   include/game_object.hxx
                                   src/game_object.cxx
                                   ../common/geometry.hxx
                                   ../common/geometry.cxx
                                   )

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_include_directories(${PROJECT_NAME} PUBLIC
                          ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_library(SDL2_LIB NAMES libSDL2)
find_library(SDL2_MIXER NAMES SDL2_mixer.dll)
find_library(SDL2_IMAGE NAMES SDL2_image.dll)

if(NOT SDL2_LIB)
    message(FATAL_ERROR "Error: find_library(...) did not find libSDL2")
endif()

if(NOT SDL2_MIXER)
    message(FATAL_ERROR "Error: find_library(...) did not find SDL2_mixer.dll")
endif()

if(NOT SDL2_IMAGE)
    message(FATAL_ERROR "Error: find_library(...) did not find SDL2_image.dll")
endif()
      
    target_link_libraries(${PROJECT_NAME}

               -lmingw32
               -lSDL2main
               -lSDL2          
               ${SDL2_LIB}
               ${SDL2_MIXER}
               ${SDL2_IMAGE}
               logger
               #-mwindows
               #-Wl,--no-undefined
               #-lm
               #-ldinput8
               #-ldxguid
               #-ldxerr8
               #-luser32
               #-lgdi32
               #-lwinmm
               #-limm32
               #-lole32
               #-loleaut32
               #-lshell32
               #-lversion
               #-luuid
               #-static-libgcc
               -lopengl32
               )

