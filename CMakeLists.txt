cmake_minimum_required(VERSION 3.12)
project(logged_engine LANGUAGES CXX C)

add_subdirectory(logger)
add_subdirectory(engine)
add_subdirectory(game)

file(GLOB resources "res/*")
#file(COPY ${resources} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../build/res)

file(COPY ${resources} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../build/res)
