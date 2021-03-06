cmake_minimum_required(VERSION 3.10)
#set cmake directory
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
string(ASCII 27 Esc)
set(ColourReset "${Esc}[m")
set(ColourBold  "${Esc}[1m")
set(Red         "${Esc}[31m")
set(Green       "${Esc}[32m")
set(Yellow      "${Esc}[33m")
set(Blue        "${Esc}[34m")
set(Magenta     "${Esc}[35m")
set(Cyan        "${Esc}[36m")
set(White       "${Esc}[37m")
set(BoldRed     "${Esc}[1;31m")
set(BoldGreen   "${Esc}[1;32m")
set(BoldYellow  "${Esc}[1;33m")
set(BoldBlue    "${Esc}[1;34m")
set(BoldMagenta "${Esc}[1;35m")
set(BoldCyan    "${Esc}[1;36m")
set(BoldWhite   "${Esc}[1;37m")
#determine build type Debug by default
if(NOT CMAKE_BUILD_TYPE)
    # Set default build type to Release
    set(CMAKE_BUILD_TYPE Debug CACHE STRING
            "Type of build (None Debug Release RelWithDebInfo MinSizeRel)" FORCE)
    if(NOT CMAKE_CONFIGURATION_TYPES)
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
                "RelWithDebInfo" "MinSizeRel")
    endif()
endif()


# set project name zsim library
set(zsim_VERSION_MAJOR "1")
set(zsim_VERSION_MINOR "0")
set(zsim_VERSION_PATCH "0")
set(zsim_VERSION
        "${zsim_VERSION_MAJOR}.${zsim_VERSION_MINOR}.${zsim_VERSION_PATCH}" CACHE INTERNAL "zsim version number")
if(POLICY CMP0048)# CMake 3.0
    project(zsim LANGUAGES C CXX  VERSION ${zsim_VERSION})
else()
    project(zsim C CXX)
endif()

if(NOT ZSIM_INSOURCE_BUILD AND "${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR "In-source zsim builds are not permitted. \n How to fix this:\n 1. Type \nmake cleancmake\nto remove garbage CMake files. \n\n 2. Please make a separate folder for building, otherwise typing \nmake\nthat will create a ./build folder and will compile in that folder. ")
endif()
## #################################################################
## Cmake Inclusions and configuration options
## #################################################################

set(CMAKE_INSTALL_MESSAGE NEVER)

#Use solution folders for Visual Studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# Remove NDEBUG flag from RelWithDebInfo builds
if(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    string(REPLACE "-DNDEBUG" "" CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
endif()

include( zsimUse )
include( zsConfig )
message("")
message("${BoldBlue} _____ ${ColourReset}  ${BoldMagenta} _ ${ColourReset}            |${BoldBlue}Zewailcity${ColourReset} ${BoldMagenta}Simulation.${ColourReset}           ")
message("${BoldBlue}|__  /${ColourReset}___${BoldMagenta}(_)${ColourReset}_ __ ___    |proprietary simulation tool for        ")
message("${BoldBlue}  / /${ColourReset}/ __| | '_ ` _ \\   |academic and industrial purposes.        ")
message("${BoldBlue} / /_${ColourReset}\\__ \\ | | | | | |  |       ")
message("${BoldBlue}/____|${ColourReset}___/_|_| |_| |_|  |Version ${${PROJECT_NAME}_VERSION} (01/08/2020).")
message("")


## #################################################################
## Project options
## #################################################################

include( zsOptions )
include(CTest)
# Note: clean cache to reset to OFF
set(BUILD_TESTING "Enable testing" ${ZSIM_BUILD_UNITTESTS})

## #################################################################
## Preprocessor definitions
## #################################################################

# Data directory
include ( zsDataDir )

# Configure
configure_file ("${PROJECT_SOURCE_DIR}/src/zsCore/zsConfig.h.in"
        "${PROJECT_BINARY_DIR}/zsCore/zsConfig.h" )
configure_file ("${PROJECT_SOURCE_DIR}/src/zsCore/zsExport.h.in"
        "${PROJECT_BINARY_DIR}/zsCore/zsExport.h" )
## #################################################################
## Collect headers and sources
## #################################################################

# Clean previously set variables in the cache
unset(${PROJECT_NAME}_HEADERS    CACHE)
unset(${PROJECT_NAME}_SOURCES    CACHE)
unset(${PROJECT_NAME}_EXTENSIONS CACHE)
unset(${PROJECT_NAME}_MODULES    CACHE)
unset(${PROJECT_NAME}_optionals  CACHE)
unset(${PROJECT_NAME}_LINKER     CACHE)
unset(zsim_TMPL_HEADERS         CACHE)
set(${PROJECT_NAME}_optionals ""
        CACHE INTERNAL "${PROJECT_NAME} list of optionals")

set (ZSIM_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/external"
        "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/extensions"
        CACHE INTERNAL "${PROJECT_NAME} include directories" )

# Offer the user the choice of overriding the installation directories
set(LIB_INSTALL_DIR     lib     CACHE STRING "Installation directory for libraries")
set(BIN_INSTALL_DIR     bin     CACHE STRING "Installation directory for executables")
set(INCLUDE_INSTALL_DIR include CACHE STRING "Installation directory for header files")

## #################################################################
## Extensions
## #################################################################

if (EIGEN_USE_MKL_ALL)
    # See http://eigen.tuxfamily.org/dox/TopicUsingIntelMKL.html
    find_package(MKL REQUIRED)
    set (ZSIM_INCLUDE_DIRS ${ZSIM_INCLUDE_DIRS} ${MKL_INCLUDE_DIR}
            CACHE INTERNAL "${PROJECT_NAME} include directories")
endif()

#first time
include_directories(${ZSIM_INCLUDE_DIRS})

include(zsFetch)

# Add externals directory
add_subdirectory(external)

if(ZSIM_BUILD_UNITTESTS) # Unittests
    add_subdirectory(unittests)
else()
    add_custom_target(unittests COMMAND "" COMMENT "Set CMake argument ZSIM_BUILD_UNITTESTS=ON to enable unittests")
endif(ZSIM_BUILD_UNITTESTS)

#[[if(ZSIM_WITH_CODIPACK)
    add_subdirectory(extensions/zsCoDiPack)
    set (ZSIM_INCLUDE_DIRS ${ZSIM_INCLUDE_DIRS} ${CODIPACK_INCLUDE_DIR}
            CACHE INTERNAL "${PROJECT_NAME} include directories")
    #include_directories(${CODIPACK_INCLUDE_DIR})
endif(ZSIM_WITH_CODIPACK)]]

#[[if(ZSIM_WITH_IPOPT)
    add_subdirectory(extensions/zsIpopt)
    #set (ZSIM_INCLUDE_DIRS ${ZSIM_INCLUDE_DIRS} ${IPOPT_INCLUDE_DIR}
    #CACHE INTERNAL "${PROJECT_NAME} include directories")
    #include_directories(${IPOPT_INCLUDE_DIR})
endif(ZSIM_WITH_IPOPT)]]

#if(ZSIM_WITH_METIS)
#include_directories(${METIS_INCLUDE_DIR})
#set(zsim_LINKER ${zsim_LINKER} ${METIS_LIBRARIES}
#    CACHE INTERNAL "${PROJECT_NAME} extra linker objects")
#endif(ZSIM_WITH_METIS)

if(ZSIM_WITH_MPI)
    find_package(MPI REQUIRED)
    set (ZSIM_INCLUDE_DIRS ${ZSIM_INCLUDE_DIRS} ${MPI_INCLUDE_PATH}
            CACHE INTERNAL "${PROJECT_NAME} include directories")
    set(zsim_LINKER ${zsim_LINKER} ${MPI_CXX_LIBRARIES}
            CACHE INTERNAL "${PROJECT_NAME} extra linker objects")
    #include_directories(SYSTEM ${MPI_INCLUDE_PATH})
endif(ZSIM_WITH_MPI)

#[[if(ZSIM_WITH_MPFR OR ZSIM_WITH_MPQ)
    find_package(GMP QUIET)
    find_package(MPFR QUIET)

    if (NOT GMP_FOUND OR NOT MPFR_FOUND)
        add_subdirectory(extensions/zsMultiPrecision)
    endif()

    set (ZSIM_INCLUDE_DIRS ${ZSIM_INCLUDE_DIRS} ${GMP_INCLUDE_DIR}
            CACHE INTERNAL "${PROJECT_NAME} include directories")
    set(zsim_LINKER ${zsim_LINKER} ${GMP_LIBRARY} ${GMPXX_LIBRARY}
            CACHE INTERNAL "${PROJECT_NAME} extra linker objects")
    #include_directories(SYSTEM ${GMP_INCLUDE_DIR})

    set (ZSIM_INCLUDE_DIRS ${ZSIM_INCLUDE_DIRS} ${MPFR_INCLUDE_DIR}
            CACHE INTERNAL "${PROJECT_NAME} include directories")
    set(zsim_LINKER ${zsim_LINKER} ${MPFR_LIBRARY}
            CACHE INTERNAL "${PROJECT_NAME} extra linker objects")
    #include_directories(SYSTEM ${MPFR_INCLUDE_DIR})
endif()]]

#[[if(ZSIM_WITH_ONURBS)
    add_subdirectory(extensions/zsOpennurbs)
endif(ZSIM_WITH_ONURBS)]]

#if(ZSIM_WITH_PARDISO)
#endif(ZSIM_WITH_PARDISO)

#if(ZSIM_WITH_PASTIX)
#endif(ZSIM_WITH_PASTIX)

#[[if(ZSIM_WITH_PSOLID)
    add_subdirectory(extensions/zsParasolid)
endif(ZSIM_WITH_PSOLID)]]

#[[if(ZSIM_WITH_SPECTRA)
    add_subdirectory(extensions/zsSpectra)
    set (ZSIM_INCLUDE_DIRS ${ZSIM_INCLUDE_DIRS} ${SPECTRA_INCLUDE_DIR}
            CACHE INTERNAL "${PROJECT_NAME} include directories")
    #include_directories(${SPECTRA_INCLUDE_DIR})
endif(ZSIM_WITH_SPECTRA)]]

#[[if(ZSIM_WITH_SUPERLU)
    find_package(SuperLU REQUIRED)
    set (ZSIM_INCLUDE_DIRS ${ZSIM_INCLUDE_DIRS} ${SUPERLU_INCLUDES}
            CACHE INTERNAL "${PROJECT_NAME} include directories")
    set(zsim_LINKER ${zsim_LINKER} ${SUPERLU_LIBRARIES}
            CACHE INTERNAL "${PROJECT_NAME} extra linker objects")
    #include_directories(SYSTEM ${SUPERLU_INCLUDES})
endif(ZSIM_WITH_SUPERLU)]]

#[[if(ZSIM_WITH_TAUCS)
    find_package(Taucs REQUIRED)
    set (ZSIM_INCLUDE_DIRS ${ZSIM_INCLUDE_DIRS} ${TAUCS_INCLUDES}
            CACHE INTERNAL "${PROJECT_NAME} include directories")
    set(zsim_LINKER ${zsim_LINKER} ${TAUCS_LIBRARIES}
            CACHE INTERNAL "${PROJECT_NAME} extra linker objects")
    #include_directories(SYSTEM ${SUPERLU_INCLUDES})
endif(ZSIM_WITH_TAUCS)]]

#[[if(ZSIM_WITH_UMFPACK)
    find_package(Umfpack REQUIRED)
    set (ZSIM_INCLUDE_DIRS ${ZSIM_INCLUDE_DIRS} ${UMFPACK_INCLUDES}
            CACHE INTERNAL "${PROJECT_NAME} include directories")
    set(zsim_LINKER ${zsim_LINKER} ${UMFPACK_LIBRARIES}
            CACHE INTERNAL "${PROJECT_NAME} extra linker objects")
    #include_directories(SYSTEM ${UMFPACK_INCLUDES})
endif(ZSIM_WITH_UMFPACK)]]

#[[if(ZSIM_WITH_UNUM)
    add_subdirectory(extensions/zsUnum)
    set (ZSIM_INCLUDE_DIRS ${ZSIM_INCLUDE_DIRS} ${UNUM_INCLUDE_DIR}
            CACHE INTERNAL "${PROJECT_NAME} include directories")
    #include_directories(${UNUM_INCLUDE_DIR})
endif(ZSIM_WITH_UNUM)]]

#[[if(ZSIM_WITH_OCC)
    add_subdirectory(extensions/zsOpenCascade)
    set (ZSIM_INCLUDE_DIRS ${ZSIM_INCLUDE_DIRS} ${OCC_INCLUDE_DIR}
            CACHE INTERNAL "${PROJECT_NAME} include directories")
    #include_directories(${OCC_INCLUDE_DIR})
endif(ZSIM_WITH_OCC)]]

#[[if(ZSIM_WITH_SMESH)
    include(external/surface_mesh.cmake)
    set (ZSIM_INCLUDE_DIRS ${ZSIM_INCLUDE_DIRS} ${SMESH_INCLUDE_DIRS}
            CACHE INTERNAL "${PROJECT_NAME} include directories")
    #include_directories(${SMESH_INCLUDE_DIR})
endif()]]

#second time
include_directories(${ZSIM_INCLUDE_DIRS})

if(ZSIM_WITH_TRILINOS)
    add_subdirectory(extensions/zsTrilinos)
    set (ZSIM_INCLUDE_DIRS ${ZSIM_INCLUDE_DIRS} ${TRILINOS_INCLUDE_DIR}
            CACHE INTERNAL "${PROJECT_NAME} include directories")
    #include_directories(${TRILINOS_INCLUDE_DIR})
endif(ZSIM_WITH_TRILINOS)

#third time
include_directories(${ZSIM_INCLUDE_DIRS})

# external inclusion paths
#get_property(EXTERNAL_INCLUDE_DIRS GLOBAL PROPERTY EXTERNAL_INCLUDE_DIRS)
#include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/external)

# Add main sources directory
add_subdirectory(src)

if(ZSIM_BUILD_LIB)
    if (ZSIM_EXTRA_DEBUG)
        set(zsim_SOURCES ${zsim_SOURCES} ${PROJECT_SOURCE_DIR}/src/misc/zsStackWalker.cpp)
    endif()
endif()

## #################################################################
## Submodules
## #################################################################

#[[option(ZSIM_COMPFLOW "Enable compflow module" OFF)
if(ZSIM_COMPFLOW)
    zsim_fetch_module(zsCompFlow)
endif()]]

#[[option(ZSIM_ELASTICITY "Enable elasticity module" OFF)
if(ZSIM_ELASTICITY)
    zsim_fetch_module(zsElasticity)
endif()]]

#[[option(ZSIM_EXASTENCILS "Enable exastenciles module" OFF)
if(ZSIM_EXASTENCILS)
    zsim_fetch_module(zsExaStencils)
endif()]]

#[[option(ZSIM_UNSUPPORTED "Enable unsupported module" OFF)
option(ZSIM_MOTOR "Enable motor module" OFF)
if(ZSIM_UNSUPPORTED OR ZSIM_MOTOR)
    zsim_fetch_module(unsupported)
    set (ZSIM_INCLUDE_DIRS ${ZSIM_INCLUDE_DIRS} ${ZSIM_DEV_INCLUDE_DIRS}
            CACHE INTERNAL "${PROJECT_NAME} include directories")
endif()

if(ZSIM_MOTOR)
    zsim_fetch_module(motor)
endif()]]

## #################################################################
## Shared and static library
## #################################################################

include(zsLibrary)

## #################################################################
## Documentation
## #################################################################

#[[add_subdirectory(doc/snippets EXCLUDE_FROM_ALL)]]
add_subdirectory(doc)

## #################################################################
## Plugins
## #################################################################

#[[add_custom_target(plugins)

if(ZSIM_BUILD_AXL)
    add_subdirectory(plugins/zsAxel)
endif(ZSIM_BUILD_AXL)

if(ZSIM_BUILD_MEX)
    add_subdirectory(plugins/zsMex)
endif(ZSIM_BUILD_MEX)]]

#if(ZSIM_BUILD_PVIEW)
#  add_subdirectory(plugins/zsParaview)
#endif(ZSIM_BUILD_PVIEW)

#[[if(ZSIM_BUILD_RHINOPLUGINS)
    add_subdirectory(plugins/RhinoTHBSplines)
endif(ZSIM_BUILD_RHINOPLUGINS)]]

## #################################################################
## Install
## #################################################################

include(zsInstall)

## #################################################################
## Executables
## #################################################################

# Note: if the shared libs are created, examples are linked against the
#  shared lib, otherwise targets are not linked against anything, only
#  templated code is used.
if(ZSIM_BUILD_EXAMPLES)
    add_subdirectory(examples)
else()
    add_subdirectory(examples EXCLUDE_FROM_ALL)
endif(ZSIM_BUILD_EXAMPLES)

## #################################################################
## Misc
## #################################################################

add_subdirectory(optional)

if (NOT zsim_optionals STREQUAL "")
    string (REPLACE ";" ", " zsim_optionals "${zsim_optionals}")
    message(STATUS "Optional compile list: ${zsim_optionals}")
endif()

unset(ZSIM_UNAME CACHE)
unset(ZSIM_PASS CACHE)


#message("ZSIM_INCLUDE_DIRS ${ZSIM_INCLUDE_DIRS}")






