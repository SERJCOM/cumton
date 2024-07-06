cmake_minimum_required(VERSION 3.25)
project(crypto)

find_package(OpenSSL REQUIRED)

set(UTILITIES_FILES 
${CMAKE_SOURCE_DIR}/Utilities/CryptoUtilities.cpp
${CMAKE_SOURCE_DIR}/Utilities/CodeGeneration/fbe_models.cpp
${CMAKE_SOURCE_DIR}/Utilities/CodeGeneration/fbe.cpp
${CMAKE_SOURCE_DIR}/Utilities/CodeGeneration/proto_models.cpp
${CMAKE_SOURCE_DIR}/Utilities/CodeGeneration/proto.cpp
)

set(BLOCKCHAIN_FILES 
${CMAKE_SOURCE_DIR}/Blockchain/Block.cpp
${CMAKE_SOURCE_DIR}/Blockchain/Blockchain.cpp
${CMAKE_SOURCE_DIR}/Blockchain/Transaction.cpp
)

add_executable(test CumTon/test.cpp ${BLOCKCHAIN_FILES} ${UTILITIES_FILES})

target_link_libraries(test PUBLIC OpenSSL::SSL uuid )

target_include_directories(test PRIVATE 
${CMAKE_SOURCE_DIR}
${CMAKE_CURRENT_BINARY_DIR}
)