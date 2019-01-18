cmake_minimum_required(VERSION 2.8)

project(zalc)
set(PACKAGE_VERSION "1.2.4")

if(MSVC)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
endif()

add_definitions(-DPACKAGE_VERSION="${PACKAGE_VERSION}")

find_package(FLTK REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${FLTK_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${FLTK_LIBRARIES})