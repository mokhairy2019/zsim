######################################################################
## zsimConfig.cmake --- zsim CMake Configuration file
## This file is part of the G+Smo library.
##
## Author: Mohamed Mahmoud
######################################################################
set(ZSIM_VERSION        "1.0.0")

set(ZSIM_INCLUDE_DIRS "/usr/local/include/zsim")
set(ZSIM_LIBRARY_DIR  "/usr/local/lib")
set(ZSIM_LIBRARIES    zsim)
set(ZSIM_MODULE_PATH  "lib")
set(ZSIM_USE_FILE     "lib/zsimUse.cmake")
set(ZSIM_BUILD_TYPE   "Debug")

if(NOT ZSIM_IS_CONFIGURED_MESSAGE)
    message(STATUS "G+Smo is configured at ${ZSIM_LIBRARY_DIR}")
    set(ZSIM_IS_CONFIGURED_MESSAGE 1 CACHE INTERNAL "Display once G+Smo library path")
endif()

if(NOT CMAKE_BUILD_TYPE)
    # Set automatically the build type
    set(CMAKE_BUILD_TYPE ${ZSIM_BUILD_TYPE} CACHE STRING
            "Type of build (set to comply with G+Smo library)" FORCE)
elseif(NOT "x${CMAKE_BUILD_TYPE}" STREQUAL "x${ZSIM_BUILD_TYPE}")
    message(WARNING "G+Smo is configured in ${ZSIM_BUILD_TYPE} mode which does not coincide with this project! Conflicts may occur. Re-run CMake with CMAKE_BUILD_TYPE=${ZSIM_BUILD_TYPE} to fix this, or update zsim_DIR.")
endif()

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ZSIM_MODULE_PATH})
