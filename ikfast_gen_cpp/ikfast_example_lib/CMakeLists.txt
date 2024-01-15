cmake_minimum_required(VERSION 3.0.2)

project(IKFast_usage_cpp)

include_directories(
    ${PROJECT_SOURCE_DIR}
)

# test example
add_executable(test_ik1 test_ik.cpp)
target_link_libraries(test_ik1 ${PROJECT_SOURCE_DIR}/libikfast_ex.a)

# add_executable(test_ik2 test_ik.cpp)
# target_link_libraries(test_ik2 ${PROJECT_SOURCE_DIR}/libIKFast2.a)

# add_executable(test_ik3 test_ik.cpp)
# target_link_libraries(test_ik3 ${PROJECT_SOURCE_DIR}/libikfast_ex.a)