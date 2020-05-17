cmake_minimum_required(VERSION 3.12)
project(game LANGUAGES CXX C)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}../../../build)

add_executable(game src/game.cxx
                    include/game.hxx
              )

target_compile_features(game PUBLIC cxx_std_17)

target_include_directories(${PROJECT_NAME} PUBLIC 
                          ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(game engine)

