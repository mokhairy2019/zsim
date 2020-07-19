######################################################################
## CMakeLists.txt ---
## This file is part of the zsim library.
##
## Author: Mohamed Mahmoud
######################################################################

######################################################################
# Macros for adding executables linked to zsim
######################################################################

# add an executable
macro(add_zsim_executable FILE)
    set(ExtraMacroArgs ${ARGN})
    if( ZSIM_BUILD_LIB )
        add_zsim_shared_executable(${FILE} ${ExtraMacroArgs})
    else ( ZSIM_BUILD_LIB )
        add_zsim_pure_executable(${FILE} ${ExtraMacroArgs})
    endif( ZSIM_BUILD_LIB )
endmacro(add_zsim_executable)

# add an executable compiled with pure template headers
macro(add_zsim_pure_executable FILE)
    set(ExtraMacroArgs ${ARGN})
    list(LENGTH ExtraMacroArgs NumExtraMacroArgs)
    if(NumExtraMacroArgs GREATER 0)
        set(FNAME ${ARGV1})
    else()
        get_filename_component(FNAME ${FILE} NAME_WE) # name without extension
    endif()
    add_test(${FNAME} ${CMAKE_BINARY_DIR}/bin/${FNAME})
    add_executable(${FNAME} ${FILE} ${zsim_SOURCES} ${zsim_EXTENSIONS} ${zsim_dev_EXTENSIONS})
    target_link_libraries(${FNAME} zsim_static)
    if(UNIX AND NOT APPLE)
        target_link_libraries(${FNAME} dl)
    endif(UNIX AND NOT APPLE)
    # Allow CMake to follow dependencies on hpp files
    set_property(TARGET ${FNAME} PROPERTY
            IMPLICIT_DEPENDS_INCLUDE_TRANSFORM "zsim_HPP_HEADER(%)=\"%\"")
    SET_TARGET_PROPERTIES(${FNAME} PROPERTIES COMPILE_FLAGS -Uzsim_BUILD_LIB)
endmacro(add_zsim_pure_executable)

# add an executable compiled with the shared library
macro(add_zsim_shared_executable FILE)
    set(ExtraMacroArgs ${ARGN})
    list(LENGTH ExtraMacroArgs NumExtraMacroArgs)
    if(NumExtraMacroArgs GREATER 0)
        set(FNAME "${ARGV1}")
    else()
        get_filename_component(FNAME ${FILE} NAME_WE) # name without extension
    endif()
    add_test(${FNAME} ${CMAKE_BINARY_DIR}/bin/${FNAME})
    #message(STATUS "exec (dynamically linked): ${FNAME}")
    add_executable(${FNAME} ${FILE})
    target_link_libraries(${FNAME} zsim)
    if (zsim_BUILD_COVERAGE)
        target_link_libraries(${FNAME} gcov)
    endif(zsim_BUILD_COVERAGE)
    if(UNIX AND NOT APPLE)
        target_link_libraries(${FNAME} dl)
    endif(UNIX AND NOT APPLE)
    #set_property(TARGET ${FNAME} PROPERTY FOLDER "examples-zsim")
endmacro(add_zsim_shared_executable)

# add an executable compiled statically with the library
macro(add_zsim_static_executable FILE)
    set(ExtraMacroArgs ${ARGN})
    list(LENGTH ExtraMacroArgs NumExtraMacroArgs)
    if(NumExtraMacroArgs GREATER 0)
        set(FNAME ${ARGV1})
    else()
        get_filename_component(FNAME ${FILE} NAME_WE) # name without extension
    endif()
    add_test(${FNAME} ${CMAKE_BINARY_DIR}/bin/${FNAME})
    #message(STATUS "exec (statically linked): ${FNAME}")
    add_executable(${FNAME} ${FILE})
    target_link_libraries(${FNAME} zsim_static)
    if(UNIX AND NOT APPLE)
        target_link_libraries(${FNAME} dl)
    endif(UNIX AND NOT APPLE)
endmacro(add_zsim_static_executable)

macro(mark_zsim_optional FILE)
    get_filename_component(FNAME ${FILE} NAME_WE) # name without extension
    set(zsim_optionals ${zsim_optionals} ${FNAME}
            CACHE INTERNAL "${PROJECT_NAME} list of optionals")
endmacro(mark_zsim_optional)

######################################################################
# File collection utilities
######################################################################

# list all subdirectories of the current directory
MACRO(SUBDIRLIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/zs*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO(SUBDIRLIST)

# collect .cpp files
macro(aux_cpp_directory DIR VAR)
    FILE(GLOB ${ARGV1} ${DIR}/[^.]*.cpp)
endmacro(aux_cpp_directory)

# collect zs*.cpp files
macro(aux_zs_cpp_directory DIR VAR)
    FILE(GLOB ${ARGV1} ${DIR}/zs*.cpp)
endmacro(aux_zs_cpp_directory)

# collect .h files
macro(aux_header_directory DIR VAR)
    FILE(GLOB ${ARGV1} ${DIR}/[^.]*.h)
endmacro(aux_header_directory)

# collect .hpp files
macro(aux_tmpl_header_directory DIR VAR)
    FILE(GLOB ${ARGV1} ${DIR}/[^.]*.hpp)
endmacro(aux_tmpl_header_directory)

# collect .cxx files
macro(aux_cxx_source_directory DIR VAR)
    FILE(GLOB ${ARGV1} ${DIR}/[^.]*.cxx)
endmacro(aux_cxx_source_directory)

# collect _.cpp (instance) files
macro(aux_instance_directory DIR VAR)
    FILE(GLOB ${ARGV1} ${DIR}/[^.]*_.cpp)
endmacro(aux_instance_directory)

function(get_repo_info repository revision) #REPO_REVISION
    if (NOT DEFINED ${repository})
        if (EXISTS "${zsim_SOURCE_DIR}/.svn")
            set(${repository} "svn" PARENT_SCOPE)
            #find_program(Subversion_SVN_EXECUTABLE NAMES svn svn.bat)
            find_package(Subversion)
            set(${revision} ${Project_WC_REVISION} PARENT_SCOPE)
            #elseif (EXISTS "${zsim_SOURCE_DIR}/.git/svn/refs")
        elseif (EXISTS "${zsim_SOURCE_DIR}/.git")
            set(${repository} "git" PARENT_SCOPE)
            find_program(git_executable NAMES git git.exe git.cmd)
            execute_process(COMMAND ${git_executable} log -1 --pretty=format:%H
                    WORKING_DIRECTORY ${zsim_SOURCE_DIR} TIMEOUT 5
                    RESULT_VARIABLE git_res OUTPUT_VARIABLE git_rev)
            set(${revision} ${git_rev} PARENT_SCOPE)
            #else()
            #  message("zsim_REPO undefined.")
        endif()
    endif()
    #set( ${repo_exe}
endfunction()

macro(add_zsim_module _DIR _NAME)

    message(STATUS "Module ${_NAME}")
    aux_header_directory     (${_DIR} ${_NAME}_H  )
    aux_cpp_directory        (${_DIR} ${_NAME}_CPP)
    aux_tmpl_header_directory(${_DIR} ${_NAME}_HPP)

    if( (NOT zsim_BUILD_LIB) )
        aux_instance_directory (${_DIR} ${_NAME}_INS)
        if(${_NAME}_INS)
            LIST( REMOVE_ITEM ${_NAME}_CPP ${${_NAME}_INS})
        endif()
    endif()

    add_library(${_NAME} OBJECT
            ${${_NAME}_H}
            ${${_NAME}_HPP}
            ${${_NAME}_CPP} )

    set_target_properties(${_NAME} PROPERTIES
            COMPILE_DEFINITIONS zsim_EXPORTS
            POSITION_INDEPENDENT_CODE ON
            LINKER_LANGUAGE CXX
            FOLDER "zsim modules" )

    set(zsim_MODULES ${zsim_MODULES} $<TARGET_OBJECTS:${_NAME}>
            CACHE INTERNAL "zsim modules" )

    install(DIRECTORY "${_DIR}/${_NAME}"
            DESTINATION include/zsim
            FILES_MATCHING PATTERN "*.h")

endmacro(add_zsim_module)
