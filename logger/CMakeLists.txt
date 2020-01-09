cmake_minimum_required(VERSION 3.12)
project(logger LANGUAGES CXX C)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}../../../build)

add_library(${PROJECT_NAME} SHARED include/log.h 
                                   include/decorator.h
                                   include/my_log.h
                                   include/log_manager.h
                                   src/log.cpp
                                   src/decorator.cpp
                                   src/my_log.cpp
                                   src/log_manager.cpp
                                   )

target_include_directories(${PROJECT_NAME} PUBLIC 
                          ${CMAKE_CURRENT_SOURCE_DIR}/include)


