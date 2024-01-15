cmake_minimum_required(VERSION 3.0.2)

project(IKFast)

add_compile_options(-O3 -Wall -shared -fPIC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
# add_compile_options(-O2 -Wall -Wextra -Wpedantic -fPIC)

## Settings
set(IKFAST_NAMESPACE ikfast_ex) # Change this to the name of your python module
set(SOURCES
    ikfast_gen.cpp
)

include_directories(
    ${PROJECT_SOURCE_DIR}
)

# IKFast Library
add_library(${IKFAST_NAMESPACE} ${SOURCES})
set_target_properties(${IKFAST_NAMESPACE} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
configure_file(config.h.in ${CMAKE_SOURCE_DIR}/config.h @ONLY)

# Test
add_executable(test_ik test_ik.cpp)
target_link_libraries(test_ik PRIVATE ${IKFAST_NAMESPACE})
