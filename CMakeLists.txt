cmake_minimum_required(VERSION 3.9)
project(Exercice_IO_2_1)

include_directories(include/)

file(GLOB_RECURSE Exercice_IO_2_1_SRC src/*.cpp include/*.h)

add_executable(Exercice_IO_2_1 ${Exercice_IO_2_1_SRC})
set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/externals)

#SFML
set(SFML_DIR ${EXTERNAL_DIR}/SFML)
set(SFML_BUILD_EXAMPLES FALSE)
add_subdirectory(${SFML_DIR})
include_directories(${SFML_DIR}/include)

LIST(APPEND Exercice_IO_2_1_LIBRARIES
	sfml-system
	sfml-window
	sfml-graphics
	sfml-audio
	sfml-network)
	
target_link_libraries(Exercice_IO_2_1 ${Exercice_IO_2_1_LIBRARIES})