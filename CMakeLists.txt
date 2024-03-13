cmake_minimum_required(VERSION 3.10)

project(LiberoServer VERSION 1.0 DESCRIPTION "libero: C++ http server framework")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/libero)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.cpp")
file(GLOB LIBERO_SOURCES "${PROJECT_SOURCE_DIR}/libero/*.cpp")

add_library(libero STATIC ${SOURCES} ${LIBERO_SOURCES})

set_target_properties(libero PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

install(TARGETS libero
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/libero/
        DESTINATION include/libero
        FILES_MATCHING PATTERN "*.h")
