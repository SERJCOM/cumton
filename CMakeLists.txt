cmake_minimum_required(VERSION 3.25)
project(crypto)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Utilities)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Blockchain)

add_executable(test CumTon/test.cpp)

target_link_libraries(test PUBLIC utilities)

target_include_directories(test PRIVATE 
${CMAKE_CURRENT_SOURCE_DIR}
)