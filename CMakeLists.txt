cmake_minimum_required(VERSION 3.25)
project(crypto)

find_package(OpenSSL REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(Catch2 3 REQUIRED)
find_package(Threads REQUIRED)
find_package(leveldb REQUIRED)

set(UTILITIES_FILES 

${CMAKE_SOURCE_DIR}/Utilities/CodeGeneration/fbe_models.cpp
${CMAKE_SOURCE_DIR}/Utilities/CodeGeneration/fbe.cpp
${CMAKE_SOURCE_DIR}/Utilities/CodeGeneration/proto_models.cpp
${CMAKE_SOURCE_DIR}/Utilities/CodeGeneration/proto.cpp
)

set(BLOCKCHAIN_FILES 
${CMAKE_SOURCE_DIR}/Blockchain/Block.cpp
${CMAKE_SOURCE_DIR}/Blockchain/Blockchain.cpp
${CMAKE_SOURCE_DIR}/Blockchain/BlockchainDB.cpp
${CMAKE_SOURCE_DIR}/Blockchain/Transaction.cpp
)

set(CRYPTO_FILES 
${CMAKE_SOURCE_DIR}/Crypto/Hash.cpp
${CMAKE_SOURCE_DIR}/Crypto/CryptoUtilities.cpp
)

set(CMAKE_CXX_CPPCHECK "cppcheck")

add_library(cumton ${BLOCKCHAIN_FILES} ${UTILITIES_FILES} ${CRYPTO_FILES})

target_link_libraries(cumton PUBLIC OpenSSL::SSL uuid yaml-cpp::yaml-cpp Threads::Threads leveldb::leveldb)

target_include_directories(cumton PRIVATE 
${CMAKE_SOURCE_DIR}
${CMAKE_CURRENT_BINARY_DIR}
)


add_executable(cumtonmain CumTon/test.cpp )

target_link_libraries(cumtonmain PUBLIC OpenSSL::SSL uuid yaml-cpp::yaml-cpp cumton
Threads::Threads leveldb::leveldb
)

target_include_directories(cumtonmain PRIVATE 
${CMAKE_SOURCE_DIR}
${CMAKE_CURRENT_BINARY_DIR}
)



add_executable(tests tests/test1.cpp)

target_link_libraries(tests PRIVATE OpenSSL::SSL uuid Catch2::Catch2WithMain cumton)

target_include_directories(tests PRIVATE 
${CMAKE_SOURCE_DIR}
)

# add_custom_target(check ALL COMMAND tests)