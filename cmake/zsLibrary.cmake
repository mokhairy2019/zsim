######################################################################
## CMakeLists.txt ---
## This file is part of the G+Smo library.
##
## Author: Mohamed Mahmoud
######################################################################

#include (GenerateExportHeader)

## #################################################################
## Add library targets
## #################################################################

#message("Using ${${PROJECT_NAME}_EXTENSIONS}")
#message("Using ${${PROJECT_NAME}_MODULES}")
#message("Using ${${PROJECT_NAME}_SOURCES}")

if(ZSIM_BUILD_LIB)

    #if ("x${CMAKE_CXX_COMPILER_ID}" STREQUAL "xGNU")
    #  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-implicit-templates")
    #endif()

    if("x${CMAKE_CXX_COMPILER_ID}" STREQUAL "xMSVC" OR
            "x${CMAKE_GENERATOR}" STREQUAL "xXcode")
        set(${PROJECT_NAME}_SOURCES)
    endif()

    add_library(${PROJECT_NAME} SHARED
            ${${PROJECT_NAME}_MODULES}
            ${${PROJECT_NAME}_SOURCES}
            ${${PROJECT_NAME}_EXTENSIONS}
            )

    #generate_export_header(${PROJECT_NAME})

    set_target_properties(${PROJECT_NAME} PROPERTIES
            #https://community.kde.org/Policies/Binary_Compatibility_Issues_With_C%2B%2B
            VERSION ${${PROJECT_NAME}_VERSION}
            SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR}
            PUBLIC_HEADER "${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME}.h"
            POSITION_INDEPENDENT_CODE ON
            LINKER_LANGUAGE CXX
            #COMPILE_DEFINITIONS ${PROJECT_NAME}_EXPORTS # Used for DLL exporting (defined by default by CMake)
            FOLDER "zsim libraries"
            )

    if(ZSIM_WITH_MPFR OR ZSIM_WITH_MPQ)
        find_package(GMP)
        find_package(MPFR)

        if (GMP_FOUND AND MPFR_FOUND)
            target_link_libraries(${PROJECT_NAME} ${MPFR_LIBRARY};${GMP_LIBRARY};${GMPXX_LIBRARY})
        endif()
    endif()

    if (ZSIM_WITH_SUPERLU)
        target_link_libraries(${PROJECT_NAME} ${SUPERLU_LIBRARIES})
    endif()

    if (ZSIM_WITH_TAUCS)
        target_link_libraries(${PROJECT_NAME} ${TAUCS_LIBRARIES})
    endif()

    if (ZSIM_WITH_UMFPACK)
        target_link_libraries(${PROJECT_NAME} ${UMFPACK_LIBRARIES})
    endif()

    if (ZSIM_WITH_PARDISO)
        if (PARDISO_USE_MKL)
            find_package(MKL REQUIRED)
            target_link_libraries(${PROJECT_NAME} ${MKL_LIBRARIES})
        else()
            find_package(Pardiso REQUIRED)
            target_link_libraries(${PROJECT_NAME} Pardiso)
        endif()
    endif()

    if(${PROJECT_NAME}_LINKER)
        target_link_libraries(${PROJECT_NAME} "${${PROJECT_NAME}_LINKER}")
    endif()

    if (ZSIM_GCC_STATIC_LINKAGE)
        target_link_libraries(${PROJECT_NAME} -static-libgcc -static-libstdc++)
    endif()

    #  if (ZSIM_WITH_OPENMP)
    #    find_package(OpenMP REQUIRED)
    #  endif()

    if (ZSIM_EXTRA_DEBUG AND DBGHELP_FOUND)
        target_link_libraries(${PROJECT_NAME} ${DBGHELP_LIBRARY})
    endif()

    if( WIN32 ) # Copy the dll to the bin folder to allow executables to find it
        if(CMAKE_CONFIGURATION_TYPES)
            add_custom_command(
                    TARGET ${PROJECT_NAME}
                    POST_BUILD
                    #COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin
                    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/$<CONFIGURATION>
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/bin/$<CONFIGURATION>
                    COMMAND ${CMAKE_COMMAND} -E echo 'The file $<TARGET_FILE:${PROJECT_NAME}> is copied to the bin folder for convenience.' )
        else()
            add_custom_command(
                    TARGET ${PROJECT_NAME}
                    POST_BUILD
                    #COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin
                    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/bin
                    COMMAND ${CMAKE_COMMAND} -E echo 'The file $<TARGET_FILE:${PROJECT_NAME}> is copied to the bin folder for convenience.' )
        endif()
    endif( WIN32 )

endif(ZSIM_BUILD_LIB)

add_library(${PROJECT_NAME}_static STATIC
        ${${PROJECT_NAME}_MODULES}
        ${${PROJECT_NAME}_SOURCES}
        ${${PROJECT_NAME}_EXTENSIONS}
        )

#generate_export_header(${PROJECT_NAME}_static)

if(${PROJECT_NAME}_LINKER)
    target_link_libraries(${PROJECT_NAME}_static "${${PROJECT_NAME}_LINKER}")
endif()

if (EIGEN_USE_MKL_ALL)
    target_link_libraries(${PROJECT_NAME} ${MKL_LIBRARIES})
endif()

if (ZSIM_EXTRA_DEBUG AND DBGHELP_FOUND)
    target_link_libraries(${PROJECT_NAME}_static ${DBGHELP_LIBRARY})
ENDIF()

if (ZSIM_GCC_STATIC_LINKAGE)
    target_link_libraries(${PROJECT_NAME}_static -static-libgcc -static-libstdc++)
endif()

# Avoid naming conflic on MSVC
if("x${CMAKE_CXX_COMPILER_ID}" STREQUAL "xMSVC")
    set(zs_static_lib_suffix _static)
endif()

set_target_properties(${PROJECT_NAME}_static PROPERTIES
        COMPILE_DEFINITIONS ${PROJECT_NAME}_STATIC
        POSITION_INDEPENDENT_CODE ON
        LINKER_LANGUAGE CXX
        FOLDER "zsim libraries"
        OUTPUT_NAME ${PROJECT_NAME}${zs_static_lib_suffix} )

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib/)

## #################################################################
## Installation
## #################################################################

install(TARGETS ${PROJECT_NAME}_static OPTIONAL
        EXPORT zsimTargets
        LIBRARY DESTINATION "${LIB_INSTALL_DIR}" COMPONENT shared
        ARCHIVE DESTINATION "${LIB_INSTALL_DIR}" COMPONENT static
        RUNTIME DESTINATION "${BIN_INSTALL_DIR}" COMPONENT exe
        PUBLIC_HEADER DESTINATION "${INCLUDE_INSTALL_DIR}/${PROJECT_NAME}")

if(ZSIM_BUILD_LIB)

    install(TARGETS ${PROJECT_NAME}
            # IMPORTANT: Add the ${PROJECT_NAME} library to the "export-set"
            EXPORT zsimTargets
            LIBRARY DESTINATION "${LIB_INSTALL_DIR}" COMPONENT shared
            ARCHIVE DESTINATION "${LIB_INSTALL_DIR}" COMPONENT static
            RUNTIME DESTINATION "${BIN_INSTALL_DIR}" COMPONENT exe
            PUBLIC_HEADER DESTINATION "${INCLUDE_INSTALL_DIR}/${PROJECT_NAME}")

endif(ZSIM_BUILD_LIB)
