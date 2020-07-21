######################################################################
## zsIntall.cmake ---
## This file is part of the zsim library.
##
## Author: Mohamed Mahmoud
######################################################################
## Installation
######################################################################

message ("  CMAKE_INSTALL_PREFIX    ${CMAKE_INSTALL_PREFIX}")

set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)
set(CMAKE_INSTALL_MESSAGE NEVER)
#note: make list_install_components
#set(CMAKE_INSTALL_DEFAULT_COMPONENT_NAME zsim)

# Offer the user the choice of overriding the installation directories
#set(LIB_INSTALL_DIR     lib     CACHE STRING "Installation directory for libraries")
#set(BIN_INSTALL_DIR     bin     CACHE STRING "Installation directory for executables")
#set(INCLUDE_INSTALL_DIR include CACHE STRING "Installation directory for header files")
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR}")

# Set CMake installation directory
if(WIN32 AND NOT CYGWIN)
    set(DEF_CMAKE_INSTALL_DIR ${LIB_INSTALL_DIR}/cmake)
else()
    set(DEF_CMAKE_INSTALL_DIR ${LIB_INSTALL_DIR})
endif()
set(CMAKE_INSTALL_DIR ${DEF_CMAKE_INSTALL_DIR} CACHE STRING
        "Installation directory for CMake files")

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
    set(var INSTALL_${p}_DIR)
    if(NOT IS_ABSOLUTE "${${p}_INSTALL_DIR}")
        set(${var} "${CMAKE_INSTALL_PREFIX}/${${p}_INSTALL_DIR}")
    endif()
endforeach()

# Add all targets to the build-tree export set
if(ZSIM_BUILD_LIB)
    export(TARGETS ${PROJECT_NAME}
            FILE "${PROJECT_BINARY_DIR}/zsimTargets.cmake" APPEND)
endif()

#if(ZSIM_WITH_other)
#  export(TARGETS other
#    FILE "${PROJECT_BINARY_DIR}/zsimTargets.cmake" APPEND)
#endif()

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE zsim)

# Create the zsConfig.cmake and zsimConfigVersion.cmake files

# ... for the build tree
set(CONF_INCLUDE_DIRS "${ZSIM_INCLUDE_DIRS}")
set(CONF_LIB_DIRS     "${CMAKE_BINARY_DIR}/lib")
set(CONF_MODULE_PATH  "${zsim_SOURCE_DIR}/cmake")
set(CONF_USE_FILE     "${CMAKE_BINARY_DIR}/zsimUse.cmake")
configure_file(${PROJECT_SOURCE_DIR}/cmake/zsConfig.cmake.in
        "${CMAKE_BINARY_DIR}/zsimConfig.cmake" @ONLY)
file(COPY ${PROJECT_SOURCE_DIR}/cmake/zsimUse.cmake DESTINATION ${CMAKE_BINARY_DIR})

# ... for the install tree
set(CONF_INCLUDE_DIRS "${CMAKE_INSTALL_PREFIX}/${INCLUDE_INSTALL_DIR}/${PROJECT_NAME}")
set(CONF_LIB_DIRS     "${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR}")
set(CONF_MODULE_PATH   "${CMAKE_INSTALL_DIR}")
set(CONF_USE_FILE     "${CMAKE_INSTALL_DIR}/zsimUse.cmake")
configure_file(${PROJECT_SOURCE_DIR}/cmake/zsConfig.cmake.in
        "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/zsimConfig.cmake" @ONLY)

# ... for both
configure_file(${PROJECT_SOURCE_DIR}/cmake/zsimConfigVersion.cmake.in
        "${CMAKE_BINARY_DIR}/zsimConfigVersion.cmake" @ONLY)

if(ZSIM_BUILD_LIB)

    set_target_properties(zsim PROPERTIES
            PUBLIC_HEADER "${PROJECT_SOURCE_DIR}/src/zsim.h")

    # For zsExport.h
    install(FILES ${PROJECT_BINARY_DIR}/zsCore/zsExport.h
            DESTINATION include/${PROJECT_NAME}/zsCore )

    # For zsLinearAlgebra.h
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/external/Eigen
            DESTINATION include/${PROJECT_NAME}
            PATTERN "*.txt" EXCLUDE
            PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)

    # For zsCmdLine.h
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/external/tclap
            DESTINATION include/${PROJECT_NAME}
            FILES_MATCHING
            PATTERN "*.h"
            PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)

    # For eiquadprog.hpp
    install(FILES ${PROJECT_SOURCE_DIR}/external/eiquadprog.hpp
            DESTINATION include/${PROJECT_NAME})

    # For zsXmlUtils.h
    install(FILES ${PROJECT_SOURCE_DIR}/external/rapidxml/rapidxml.hpp
            ${PROJECT_SOURCE_DIR}/external/rapidxml/rapidxml_print.hpp
            DESTINATION include/${PROJECT_NAME}/rapidxml/ )


    # For pure install
    #install(DIRECTORY ${PROJECT_SOURCE_DIR}/external/rapidxml
    #        DESTINATION include/${PROJECT_NAME}
    #        FILES_MATCHING
    #        PATTERN "*.hpp"
    #        PATTERN ".svn" EXCLUDE
    #        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)

    # For zsConfig.h
    install(DIRECTORY ${ZSIM_DATA_DIR} DESTINATION share/zsimdata)
    # todo: search environment variable as well
    set(ZSIM_DATA_DIR ${CMAKE_INSTALL_PREFIX}/share/zsimdata/)
    configure_file ("${PROJECT_SOURCE_DIR}/src/zsCore/zsConfig.h.in"
            "${PROJECT_BINARY_DIR}/zsCore/zsConfig_install.h" )
    install(FILES ${PROJECT_BINARY_DIR}/zsCore/zsConfig_install.h
            DESTINATION include/${PROJECT_NAME}/zsCore/ RENAME zsConfig.h)

    # Install cmake files
    install(FILES
            "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/zsimConfig.cmake"
            "${CMAKE_BINARY_DIR}/zsimConfigVersion.cmake"
            "${PROJECT_SOURCE_DIR}/cmake/zsimUse.cmake"
            DESTINATION "${CMAKE_INSTALL_DIR}" COMPONENT devel)

    # Install the export set for use with the install-tree
    #install(EXPORT zsimTargets DESTINATION
    #  "${CMAKE_INSTALL_DIR}" COMPONENT devel)

else(ZSIM_BUILD_LIB)
    message ("Configure with -DZSIM_BUILD_LIB=ON to compile the library")
endif(ZSIM_BUILD_LIB)

# Install docs (if available)
set(DOC_SRC_DIR "${PROJECT_BINARY_DIR}/doc/html/")
#message("DOC_SRC_DIR='${DOC_SRC_DIR}'")

set(TMP_VERSION "${zsim_VERSION}")
string(REGEX REPLACE "[a-zA-Z]+" "" TMP_VERSION ${TMP_VERSION})
#message("TMP_VERSION='${TMP_VERSION}'")
set(DOC_INSTALL_DIR share/doc/zsim-${TMP_VERSION} CACHE PATH
        "Installation directory for documentation")
#message("DOC_INSTALL_DIR='${DOC_INSTALL_DIR}'")

install(DIRECTORY "${DOC_SRC_DIR}"
        COMPONENT doc
        DESTINATION "${DOC_INSTALL_DIR}/"
        USE_SOURCE_PERMISSIONS
        OPTIONAL
        FILES_MATCHING
        PATTERN "*.css"
        PATTERN "*.html"
        PATTERN "*.js"
        PATTERN "*.jpg"
        PATTERN "*.png")
