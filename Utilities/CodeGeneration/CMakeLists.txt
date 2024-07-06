project(fbe)

add_executable(fbe test.cpp fbe_models.cpp fbe.cpp proto_models.cpp proto.cpp )

target_link_libraries(fbe uuid)