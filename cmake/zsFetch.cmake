######################################################################
## zsFetch.cmake
## This file is part of the zsim library.
##
## Author: Mohamed Mahmoud
######################################################################

include(CMakeParseArguments)

#latest CMake has FetchContent
function(zsim_fetch_directory)
    set(GF_NAME "${ARGV0}")
    set(oneValueArgs
            # Protect the following options
            DESTINATION
            SOURCE_DIR
            BINARY_DIR
            CONFIGURE_COMMAND
            BUILD_COMMAND
            INSTALL_COMMAND
            TEST_COMMAND )
    cmake_parse_arguments(GF "${GF_NAME}" "${oneValueArgs}" "" ${ARGN})
    #message( GF_UNPARSED_ARGUMENTS "= ${GF_UNPARSED_ARGUMENTS}")

    file(GLOB RESULT ${zsim_SOURCE_DIR}/${GF_DESTINATION}/${GF_NAME})
    list(LENGTH RESULT RESULT_LENGTH)
    if(NOT RESULT_LENGTH EQUAL 0)
        message(STATUS "Enabling remote module ${GF_NAME} (${GF_DESTINATION}) - found")
        return()
    endif()

    message(STATUS "Enabling remote module ${GF_NAME} (${GF_DESTINATION})")
    set(GF_SOURCE_DIR   "${zsim_SOURCE_DIR}/${GF_DESTINATION}/${GF_NAME}")
    set(GF_BINARY_DIR   "${zsim_BINARY_DIR}/${GF_DESTINATION}/${GF_NAME}_fetch")
    set(GF_DOWNLOAD_DIR "${zsim_BINARY_DIR}/${GF_DESTINATION}/${GF_NAME}_fetch")
    set(${GF_NAME}_SOURCE_DIR "${GF_SOURCE_DIR}" PARENT_SCOPE)
    set(${GF_NAME}_BINARY_DIR "${GF_BINARY_DIR}" PARENT_SCOPE)
    file(REMOVE "${GF_DOWNLOAD_DIR}/CMakeCache.txt")

    #  if(NOT EXISTS ${GF_DOWNLOAD_DIR}/CMakeLists.txt)
    file(WRITE ${GF_DOWNLOAD_DIR}/CMakeLists.txt "if(POLICY CMP0048)\ncmake_policy(SET CMP0048 NEW)\nendif()\nif(POLICY CMP0054)\ncmake_policy(SET CMP0054 NEW)\nendif()\ncmake_minimum_required(VERSION 2.8.8)\nproject(${GF_NAME}_fetch NONE)\ninclude(ExternalProject)\nExternalProject_Add(${GF_NAME}_fetch\n ${GF_UNPARSED_ARGUMENTS}\n SOURCE_DIR          \"${GF_SOURCE_DIR}\"\n BINARY_DIR          \"${GF_BINARY_DIR}\"\n CONFIGURE_COMMAND   \"\"\n BUILD_COMMAND       \"\"\n INSTALL_COMMAND     \"\"\n TEST_COMMAND        \"\")\n")
    #  endif()

    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}"
            -D "CMAKE_MAKE_PROGRAM:FILE=${CMAKE_MAKE_PROGRAM}" .
            OUTPUT_QUIET
            RESULT_VARIABLE result
            WORKING_DIRECTORY "${GF_DOWNLOAD_DIR}" )
    if(result)
        message(SEND_ERROR "Configure step for ${GF_NAME} failed: ${result}")
    endif()

    #! Update step requires the git sources to be available
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
            OUTPUT_QUIET
            RESULT_VARIABLE result
            WORKING_DIRECTORY "${GF_DOWNLOAD_DIR}" )
    if(result)
        message(SEND_ERROR "Build step for ${GF_NAME} failed: ${result}")
    endif()

    file(GLOB RESULT ${zsim_SOURCE_DIR}/${GF_DESTINATION}/${GF_NAME})
    list(LENGTH RESULT RESULT_LENGTH)
    if(RESULT_LENGTH EQUAL 0)
        message(SEND_ERROR "Enabling remote module ${GF_NAME} (${GF_DESTINATION}) - not found")
    else()
        message(STATUS "Enabling remote module ${GF_NAME} (${GF_DESTINATION}) - downloaded")
    endif()

endfunction()

# called to fetch/download a submodule form git (working) and svn (in progress)
# (ARGV0) SUBMODULE:  name of submodule
# (ARGVN)             Used to give Update Command, unittests/CMakeLists.txt-15-#07.08.18
function(zsim_fetch_module SUBMODULE)

    # TODO: online/offline mode

    get_repo_info(ZSIM_REPO ZSIM_REPO_REV) # or set manually

    #if (NOT DEFINED ZSIM_FETCH_PROT)
    #  set(ZSIM_FETCH_PROT https) #ssh
    #endif()

    #message("Fetch ${SUBMODULE} (repository: ${ZSIM_REPO}, revision: ${ZSIM_REPO_REV}, protocol: ${ZSIM_FETCH_PROT}, username: ${ZSIM_UNAME}, password: ${ZSIM_PASS})")

    if("x${ZSIM_REPO}" STREQUAL "xgit")
        #if("x${ZSIM_FETCH_PROT}" STREQUAL "xssh")
        #  set(git_repo git@github.com:zsim/${SUBMODULE}.git)
        #elseif("x${ZSIM_FETCH_PROT}" STREQUAL "xhttps")
        #  set(git_repo https://github.com/zsim/${SUBMODULE}.git)
        #endif()
        # zsim_fetch_directory(${ARGN} GIT_REPOSITORY  ${git_repo} DESTINATION  extensions)

        if(NOT EXISTS "${zsim_SOURCE_DIR}/extensions/${SUBMODULE}/CMakeLists.txt")
            message(STATUS "Initializing remote submodule ${SUBMODULE}")
            find_package(Git REQUIRED)

            # init SUBMODULE
            execute_process(COMMAND "${GIT_EXECUTABLE}" "submodule" "update" "--init" "extensions/${SUBMODULE}"
                    WORKING_DIRECTORY ${zsim_SOURCE_DIR}
                    #RESULT_VARIABLE gresult
                    #OUTPUT_QUIET
                    )
        endif()

    elseif("x${ZSIM_REPO}" STREQUAL "xsvn")
        #if("x${ZSIM_FETCH_PROT}" STREQUAL "xssh") message(ERROR "GitHub does not support svn+ssh") endif()
        zsim_fetch_directory(${SUBMODULE}
                SVN_REPOSITORY https://github.com/zsim/${SUBMODULE}/trunk
                SVN_USERNAME ${ZSIM_UNAME} # Username for Subversion checkout and update
                SVN_PASSWORD ${ZSIM_PASS}  # Password for Subversion checkout and update
                SVN_TRUST_CERT 1            # Trust the Subversion server site certificate
                DESTINATION  extensions
                )
    else()
        zsim_fetch_directory(${SUBMODULE}
                URL https://github.com/zsim/${SUBMODULE}/archive/master.zip
                DESTINATION  extensions
                )
    endif()

    # get list of programs to compile
    if(EXISTS "${zsim_SOURCE_DIR}/extensions/${SUBMODULE}/CMakeLists.txt")
        add_subdirectory(${zsim_SOURCE_DIR}/extensions/${SUBMODULE} ${zsim_BINARY_DIR}/extensions/${SUBMODULE})
    endif()

endfunction()
