### zsDataDir.cmake ---
## 
## set ZSIM_DATA_DIR based on compiler-toolchain
## 
## Author: Mohamed Mahmoud
######################################################################

# Data directory
if (DEFINED EMSCRIPTEN)
    set(ZSIM_DATA_DIR "filedata/" )
    message("ZSIM_DATA_DIR set to relative path '${ZSIM_DATA_DIR}'")
    set(ZSIM_ORIG_DATA_DIR "${PROJECT_SOURCE_DIR}/filedata/")
else()
    set (ZSIM_DATA_DIR   "${PROJECT_SOURCE_DIR}/filedata/")
endif()

# Config-files directory
set(ZSIM_CONFIG_DIR "${CMAKE_BINARY_DIR}/config/")

# Set default search paths
if (NOT DEFINED ZSIM_SEARCH_PATHS)
    set(ZSIM_SEARCH_PATHS "${ZSIM_DATA_DIR}" CACHE STRING
            "Define paths where files should be searched; seperated by semicolon.")
endif()
