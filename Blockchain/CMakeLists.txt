cmake_minimum_required(VERSION 3.25)

set(SRC_FILES
${CMAKE_CURRENT_SOURCE_DIR}/Block.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Transaction.cpp
)

add_library(blockchain ${SRC_FILES})

target_link_libraries(blockchain PUBLIC utilities)

target_include_directories(blockchain PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}/..
)