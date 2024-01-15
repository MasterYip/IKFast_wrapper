cmake_minimum_required(VERSION 3.0.2)

project(IKFast)

add_compile_options(-O3 -Wall -shared -fPIC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
# add_compile_options(-O2 -Wall -Wextra -Wpedantic -fPIC)

## Settings
set(LIB_NAME ikfast_example_lib)
set(IKFAST_NAMESPACE ikfast_ex) # Change this to the name of your python module

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${LIB_NAME})

set(SOURCES
    ikfast_gen.cpp
    ikfast_interface.cpp
)


include_directories(
    ${PROJECT_SOURCE_DIR}
)

# IKFast Library
add_library(${IKFAST_NAMESPACE} ${SOURCES})
# set_target_properties(${IKFAST_NAMESPACE} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
configure_file(config.h.in ${CMAKE_SOURCE_DIR}/config.h @ONLY)

configure_file(ikfast_interface_gen.h.in ${CMAKE_SOURCE_DIR}/${LIB_NAME}/${IKFAST_NAMESPACE}_interface.h @ONLY)

# Test
add_executable(test_ik test_ik.cpp)
target_link_libraries(test_ik PRIVATE ${IKFAST_NAMESPACE})
