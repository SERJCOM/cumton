cmake_minimum_required(VERSION 3.25)

find_package(OpenSSL REQUIRED)

set(SOURCE_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/CryptoUtilities.cpp
)

message(${SOURCE_FILES})

add_library(utilities ${SOURCE_FILES})

target_link_libraries(utilities OpenSSL::SSL)

