cmake_minimum_required(VERSION 3.10)
project(protobuf_test)

aux_source_directory(src SOURCES)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    protobuf)