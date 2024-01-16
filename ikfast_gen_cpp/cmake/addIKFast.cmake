
function(add_IKFast libname namespace srcfile)
    if(NOT WIN32)
        string(ASCII 27 Esc)
        set(ColourReset "${Esc}[m")
        set(ColourBold  "${Esc}[1m")
        set(Red         "${Esc}[31m")
        set(Green       "${Esc}[32m")
    endif()
    set(TEMPLATE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/template)
    set(BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/temp/${namespace})
    set(OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/${libname})
    set(IKFAST_NAMESPACE ${namespace})
    # Configure files
    # ikfast src
    configure_file(${srcfile} ${BUILD_DIR}/ikfast_gen.cpp @ONLY)
    # template include & src
    configure_file(${TEMPLATE_DIR}/config.h.in ${BUILD_DIR}/config.h @ONLY)
    configure_file(${TEMPLATE_DIR}/ikfast.h ${BUILD_DIR}/ikfast.h @ONLY)
    configure_file(${TEMPLATE_DIR}/ikfast_interface.h ${BUILD_DIR}/ikfast_interface.h @ONLY)
    configure_file(${TEMPLATE_DIR}/ikfast_interface.cpp ${BUILD_DIR}/ikfast_interface.cpp @ONLY)
    configure_file(${TEMPLATE_DIR}/test_ik.cpp ${BUILD_DIR}/test_ik.cpp @ONLY)
    # Cmake
    configure_file(${TEMPLATE_DIR}/CMakeLists.txt.in ${BUILD_DIR}/CMakeLists.txt @ONLY)
    # generated interface
    configure_file(${TEMPLATE_DIR}/ikfast_interface_gen.h.in ${OUTPUT_DIR}/${IKFAST_NAMESPACE}.h @ONLY)

endfunction(add_IKFast namespace)
