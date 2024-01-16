cmake_minimum_required(VERSION 3.0.2)

project(IKFast_warpper)

include(cmake/addIKFast.cmake)

add_compile_options(-O3 -Wall -shared -fPIC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
# add_compile_options(-O2 -Wall -Wextra -Wpedantic -fPIC)

## Settings
set(LIB_NAME ikfast_example_lib)


set(BUILD_DIR ${CMAKE_BINARY_DIR}/temp)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

file(GLOB IKFAST_SRC_LIST ${SRC_DIR}/*.cpp)

foreach(IKFAST_SRC ${IKFAST_SRC_LIST})
    get_filename_component(IKFAST_NS ${IKFAST_SRC} NAME_WE)
    add_IKFast(${LIB_NAME} ${IKFAST_NS} ${IKFAST_SRC})
    add_subdirectory(${BUILD_DIR}/${IKFAST_NS})
endforeach()



# set(IKFAST_NAMESPACE ikfast_ex) # Change this to the name of your python module

# set(TEMPLATE_DIR ${CMAKE_SOURCE_DIR}/template)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${LIB_NAME})

# set(SOURCES
#     ikfast_gen.cpp
#     ikfast_interface.cpp
# )


# include_directories(
#     ${PROJECT_SOURCE_DIR}
# )

# # IKFast Library
# add_library(${IKFAST_NAMESPACE} ${SOURCES})
# configure_file(${TEMPLATE_DIR}/config.h.in ${CMAKE_SOURCE_DIR}/config.h @ONLY)
# configure_file(${TEMPLATE_DIR}/ikfast_interface_gen.h.in ${CMAKE_SOURCE_DIR}/lib/${LIB_NAME}/${IKFAST_NAMESPACE}.h @ONLY)

# # Test
# # add_executable(test_ik test_ik.cpp)
# # target_link_libraries(test_ik PRIVATE ${IKFAST_NAMESPACE})
