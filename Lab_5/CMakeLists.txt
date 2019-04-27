cmake_minimum_required(VERSION 3.8)

project(Lab5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -g") # DEBUG KEY

include_directories(/C:/fltk-1.3.5rc2)
link_directories(/C:/fltk-1.3.5rc2/lib)

file(GLOB Lab5_SRC
	./Source/*.cpp
)

find_package(OpenGL 3.3 REQUIRED)
	include_directories(${OPENGL_INCLUDE_DIRS})
	link_libraries(${OPENGL_LIBRARIES})
find_package(GLEW REQUIRED)
	include_directories(${GLEW_INCLUDE_DIRS})
	link_libraries(${GLEW_LIBRARIES})
find_package(FLTK REQUIRED)
	include_directories(${FLTK_INCLUDE_DIRS})
	link_libraries(${FLTK_LIBRARIES})
 
add_executable(Lab5 ${Lab5_SRC} )
#target_link_libraries(Lab5 fltk fltk_gl fltk_forms opengl32 gdi32 ole32 uuid comctl32)
target_link_libraries(Lab5)