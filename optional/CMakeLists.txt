## CMakeLists.txt ---
##
## Author: Mohamed Mahmoud
######################################################################

project(optional)
#add_custom_target(${PROJECT_NAME})
#set_property(TARGET ${PROJECT_NAME} PROPERTY LABELS ${PROJECT_NAME})

## Parasolid option
if(ZSIM_WITH_PSOLID)

    FILE(GLOB parasolid_exe ${CMAKE_CURRENT_SOURCE_DIR}/gsParasolid*.cpp)
    foreach(file ${parasolid_exe})
        add_zsim_executable(${file})
        mark_zsim_optional (${file})
        get_filename_component(namewe ${file} NAME_WE)
        add_dependencies(examples ${namewe})
        set_property(TEST ${namewe} PROPERTY LABELS "examples")
    endforeach()

    #set_property(TARGET gsParasolid_test APPEND PROPERTY
    #INCLUDE_DIRECTORIES ${PARASOLID_INCLUDE_DIR} )

endif(ZSIM_WITH_PSOLID)


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/)
