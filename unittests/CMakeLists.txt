######################################################################
## CMakeLists.txt ---
## This file is part of the Zsim library.
##
## Author: Mohamed Mahmoud
######################################################################

project(unittests)

set(CMAKE_DIRECTORY_LABELS "${PROJECT_NAME}") #CMake 3.10

include(zsFetch)
zsim_fetch_module(zsUnitTest
        #  UPDATE_COMMAND "${CMAKE_COMMAND} -E echo (offline mode)"
        )

include(zsConfig)

# set include directory
set(ZSUNITTEST_INCLUDE_DIR ${zsim_SOURCE_DIR}/extensions/zsUnitTest
        CACHE INTERNAL "zsUnitTest include directory")

install(DIRECTORY ${ZSUNITTEST_INCLUDE_DIR} DESTINATION
        DESTINATION include/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h")

include_directories(${ZSUNITTEST_INCLUDE_DIR})

# Collect source file names
aux_zs_cpp_directory(${PROJECT_SOURCE_DIR} unittests_SRCS)

add_executable(${PROJECT_NAME} zsim_unittest.h ${unittests_SRCS} main.cpp)
target_link_libraries(${PROJECT_NAME} zsim UnitTestPP)
set_target_properties(${PROJECT_NAME} PROPERTIES LABELS "${PROJECT_NAME}" FOLDER "${PROJECT_NAME}")


# TODO: Reqctivate this after understanding it
#[[if (NOT NOSNIPPETS)
    add_dependencies(${PROJECT_NAME} doc-snippets) # doc-snippets are tests as well
endif()]]

foreach(file ${unittests_SRCS})
    get_filename_component(testname ${file} NAME_WE) # name without extension
    add_test(NAME unit_${testname} COMMAND $<TARGET_FILE:unittests> ${file})
    set_property(TEST unit_${testname} PROPERTY LABELS unittests)
endforeach(file ${FILES})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
