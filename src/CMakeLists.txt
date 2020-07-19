######################################################################
## CMakeLists.txt ---
## This file is part of the zsim library.
##
## Author: Mohamed Mahmoud
######################################################################

include_directories(${ZSIM_INCLUDE_DIRS})

if(ZSIM_WITH_CODIPACK)
    include_directories(${CODIPACK_INCLUDE_DIR})
endif()

if(ZSIM_WITH_UNUM)
    include_directories(${UNUM_INCLUDE_DIR})
endif()

SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})
#LIST( REMOVE_ITEM SUBDIRS misc)
#[[LIST( APPEND SUBDIRS gsUtils/gsMesh)]]

if (ZSIM_BUILD_PCH)
    add_precompiled_header(gsPrecompiledHeader misc/gsPrecompiledHeader.h)
endif()

FOREACH(subdir ${SUBDIRS})

    get_filename_component(GM_NAME ${subdir} NAME)
    #message("module: ${GM_NAME}")

    ## Collect files
    aux_header_directory     (${CMAKE_CURRENT_SOURCE_DIR}/${subdir} ${subdir}_H  )
    aux_cpp_directory        (${CMAKE_CURRENT_SOURCE_DIR}/${subdir} ${subdir}_CPP)
    aux_tmpl_header_directory(${CMAKE_CURRENT_SOURCE_DIR}/${subdir} ${subdir}_HPP)

    if( (NOT ZSIM_BUILD_LIB) )
        aux_instance_directory (${CMAKE_CURRENT_SOURCE_DIR}/${subdir} ${subdir}_INS)
        if(${subdir}_INS)
            LIST( REMOVE_ITEM ${subdir}_CPP ${${subdir}_INS})
        endif()
    endif()

    ## Add module
    add_library(${GM_NAME} OBJECT
            ${${subdir}_H}
            ${${subdir}_HPP}
            ${${subdir}_CPP}
            )

    set_target_properties(${GM_NAME} PROPERTIES
            COMPILE_DEFINITIONS zsim_EXPORTS
            POSITION_INDEPENDENT_CODE ON
            LINKER_LANGUAGE CXX
            FOLDER "G+Smo modules"
            #EXCLUDE_FROM_ALL 1
            #EXCLUDE_FROM_DEFAULT_BUILD 1
            )

    if(ZSIM_BUILD_MULTIPRECISION)
        add_dependencies(${GM_NAME} gsMultiPrecisionExtension)
    endif()

    if (ZSIM_BUILD_PCH)
        target_precompiled_header(${GM_NAME} gsPrecompiledHeader)
    endif()

    set(zsim_MODULES ${zsim_MODULES} $<TARGET_OBJECTS:${GM_NAME}>
            CACHE INTERNAL "G+Smo modules" )

    ## install module
    if (NOT ${GM_NAME} MATCHES gsMesh) # avoid installing twice gsMesh
        install(DIRECTORY   "${CMAKE_CURRENT_SOURCE_DIR}/${subdir}"
                DESTINATION include/${PROJECT_NAME}
                FILES_MATCHING PATTERN "*.h" )
    endif()

ENDFOREACH()
