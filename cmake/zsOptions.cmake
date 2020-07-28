######################################################################
## CMakeLists.txt ---
## This file is part of the zsim library.
##
## Author: Mohamed Mahmoud
######################################################################

message ("Configuration (cmake ${CMAKE_VERSION}):")

message ("  Source folder:          ${CMAKE_SOURCE_DIR}")
if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
    find_package(Git)
    execute_process(COMMAND ${GIT_EXECUTABLE} log --pretty=format:%h -n 1
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            RESULT_VARIABLE isGit
            OUTPUT_VARIABLE gitHash)
    if(${isGit} EQUAL 0)
        message("  Git commit:             ${gitHash}")
    endif()
endif()
message ("  CMAKE_BUILD_TYPE        ${CMAKE_BUILD_TYPE}")
message ("  CMAKE_C_COMPILER        ${CMAKE_C_COMPILER}")
message ("  CMAKE_CXX_COMPILER      ${CMAKE_CXX_COMPILER}")
message ("  CMAKE_CXX_STANDARD      ${CMAKE_CXX_STANDARD}")

message ("  ZSIM_COEFF_TYPE        ${ZSIM_COEFF_TYPE}")
message ("  ZSIM_INDEX_TYPE        ${ZSIM_INDEX_TYPE}")

## #################################################################
## Options list: Standard options
## #################################################################

option(ZSIM_BUILD_AXL           "Build Axl Plugin"         false  )
if  (${ZSIM_BUILD_AXL})
    message ("  ZSIM_BUILD_AXL         ${ZSIM_BUILD_AXL}")
endif()

option(ZSIM_BUILD_EXAMPLES      "Build examples"            true   )
if  (${ZSIM_BUILD_EXAMPLES})
    message ("  ZSIM_BUILD_EXAMPLES    ${ZSIM_BUILD_EXAMPLES}")
endif()

option(ZSIM_BUILD_LIB           "Build shared library"      true   )
message ("  ZSIM_BUILD_LIB         ${ZSIM_BUILD_LIB}")

option(ZSIM_BUILD_MEX           "Build Mex files"           false  )
if  (${ZSIM_BUILD_MEX})
    message ("  ZSIM_BUILD_MEX         ${ZSIM_BUILD_MEX}")
endif()

option(ZSIM_BUILD_PCH           "Build precompiled headers" false  )
if  (${ZSIM_BUILD_PCH})
    message ("  ZSIM_BUILD_PCH         ${ZSIM_BUILD_PCH}")
endif()

option(ZSIM_BUILD_PVIEW         "Build Paraview Plugin"     false  )
if  (${ZSIM_BUILD_PVIEW})
    message ("  ZSIM_BUILD_PVIEW        ${ZSIM_BUILD_VIEW}")
endif()

option(ZSIM_BUILD_RHINOPLUGINS  "Build Rhino THB Plugins"   false  )
if  (${ZSIM_BUILD_RHINOPLUGINS})
    message ("  ZSIM_BUILD_RHINOPLUGINS ${ZSIM_BUILD_RHINOPLUGINS}")
endif()

option(ZSIM_BUILD_UNITTESTS     "Build unittests"           true  )
if  (${ZSIM_BUILD_UNITTESTS})
    message ("  ZSIM_BUILD_UNITTESTS   ${ZSIM_BUILD_UNITTESTS}")
endif()

option(ZSIM_EXTRA_DEBUG         "Extra debug features"      false  )
if  (${ZSIM_EXTRA_DEBUG})
    message ("  ZSIM_EXTRA_DEBUG       ${ZSIM_EXTRA_DEBUG}")
endif()

option(ZSIM_WITH_ADIFF          "With auto-diff"            false  )
if  (${ZSIM_WITH_ADIFF})
    message ("  ZSIM_WITH_ADIFF        ${ZSIM_WITH_ADIFF}")
endif()

option(ZSIM_WITH_CODIPACK       "With CoDiPack"             false  )
if  (${ZSIM_WITH_CODIPACK})
    message ("  ZSIM_WITH_CODIPACK     ${ZSIM_WITH_CODIPACK}")
endif()

option(ZSIM_WITH_IPOPT          "With IpOpt"                false  )
if  (${ZSIM_WITH_IPOPT})
    message ("  ZSIM_WITH_IPOPT        ${ZSIM_WITH_IPOPT}")
endif()

#option(ZSIM_WITH_METIS          "With METIS"                false )
#if  (${ZSIM_WITH_METIS})
#message ("  ZSIM_WITH_METIS        ${ZSIM_WITH_METIS}")
#endif()

option(ZSIM_WITH_GMP           "With GMP"                  false  )
if  (${ZSIM_WITH_GMP})
    message ("  ZSIM_WITH_GMP         ${ZSIM_WITH_GMP}")
endif()

option(ZSIM_WITH_MPFR           "With MPFR"                  false  )
if  (${ZSIM_WITH_MPFR})
    message ("  ZSIM_WITH_MPFR         ${ZSIM_WITH_MPFR}")
endif()

option(ZSIM_WITH_MPI            "With MPI"                  false  )
if  (${ZSIM_WITH_MPI})
    message ("  ZSIM_WITH_MPI          ${ZSIM_WITH_MPI}")
endif()

option(ZSIM_WITH_MPQ            "With MPQ"                  false  )
if  (${ZSIM_WITH_MPQ})
    message ("  ZSIM_WITH_MPQ          ${ZSIM_WITH_MPQ}")
endif()

option(ZSIM_WITH_OCC            "With OpenCascade"          false  )
if  (${ZSIM_WITH_OCC})
    message ("  ZSIM_WITH_OCC          ${ZSIM_WITH_OCC}")
endif()

option(ZSIM_WITH_ONURBS         "With OpenNurbs"            false  )
if  (${ZSIM_WITH_ONURBS})
    message ("  ZSIM_WITH_ONURBS       ${ZSIM_WITH_ONURBS}")
endif()

option(ZSIM_WITH_OPENMP         "With OpenMP"               false  )
if  (${ZSIM_WITH_OPENMP})
    message ("  ZSIM_WITH_OPENMP       ${ZSIM_WITH_OPENMP}")
endif()

option(ZSIM_WITH_PARDISO        "With PARDISO"              false  )
if  (${ZSIM_WITH_PARDISO})
    message ("  ZSIM_WITH_PARDISO      ${ZSIM_WITH_PARDISO}")
endif()

option(ZSIM_WITH_PASTIX         "With PastiX"               false  )
if  (${ZSIM_WITH_PASTIX})
    message ("  ZSIM_WITH_PASTIX       ${ZSIM_WITH_PASTIX}")
endif()

option(ZSIM_WITH_PSOLID         "With Parasolid"            false  )
if  (${ZSIM_WITH_PSOLID})
    message ("  ZSIM_WITH_PSOLID       ${ZSIM_WITH_PSOLID}")
endif()

option(ZSIM_WITH_SPECTRA        "With Spectra"              false  )
if  (${ZSIM_WITH_SPECTRA})
    message ("  ZSIM_WITH_SPECTRA      ${ZSIM_WITH_SPECTRA}")
endif()

option(ZSIM_WITH_SUPERLU        "With SuperLU"              false  )
if  (${ZSIM_WITH_SUPERLU})
    message ("  ZSIM_WITH_SUPERLU      ${ZSIM_WITH_SUPERLU}")
endif()

option(ZSIM_WITH_TAUCS          "With Taucs"                false  )
if  (${ZSIM_WITH_TAUCS})
    message ("  ZSIM_WITH_TAUCS        ${ZSIM_WITH_TAUCS}")
endif()

option(ZSIM_WITH_TRILINOS       "With TRILINOS"             false  )
if  (${ZSIM_WITH_TRILINOS})
    message ("  ZSIM_WITH_TRILINOS     ${ZSIM_WITH_TRILINOS}")
endif()

option(ZSIM_WITH_UMFPACK        "With Umfpack"              false  )
if  (${ZSIM_WITH_UMFPACK})
    message ("  ZSIM_WITH_UMFPACK      ${ZSIM_WITH_UMFPACK}")
endif()

option(ZSIM_WITH_UNUM           "With Universal NUMber"     false  )
if  (${ZSIM_WITH_UNUM})
    message ("  ZSIM_WITH_UNUM         ${ZSIM_WITH_UNUM}")
endif()

## #################################################################
## Options list: Extra options
## #################################################################

option(EIGEN_USE_MKL_ALL         "Eigen use MKL"                 false  )
if (EIGEN_USE_MKL_ALL)
    message ("  EIGEN_USE_MKL_ALL       ${EIGEN_USE_MKL_ALL}")
endif()

option(ZSIM_BUILD_CPPLOT        "Build cpplot"                  false  )
if (ZSIM_BUILD_CPPLOT)
    message ("  ZSIM_BUILD_CPPLOT      ${ZSIM_BUILD_CPPLOT}")
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    option(ZSIM_BUILD_COVERAGE      "Build with coverage"          false )
    if (ZSIM_BUILD_COVERAGE)
        message ("  ZSIM_BUILD_COVERAGE    ${ZSIM_BUILD_COVERAGE}")
    endif()
endif(CMAKE_COMPILER_IS_GNUCXX)

option(ZSIM_BUILD_QT_APP        "Build Qt application"          false  )
if (ZSIM_BUILD_QT_APP)
    message ("  ZSIM_BUILD_QT_APP      ${ZSIM_BUILD_QT_APP}")
endif()

option(ZSIM_WARNINGS            "Enable Zsim related warnings" false  )
if (ZSIM_WARNINGS)
    message ("  ZSIM_WARNINGS          ${ZSIM_WARNINGS}")
endif()

option(ZSIM_WITH_VTK            "With VTK"                      false  )
if (ZSIM_WITH_VTK)
    message ("  ZSIM_WITH_VTK          ${ZSIM_WITH_VTK}")
endif()

if(DEFINED ${isGit} AND ${isGit} EQUAL 0)
    message(STATUS "Type \"${GIT_EXECUTABLE} submodule\" to see the state of submodules")
endif()

#https://www.threadingbuildingblocks.org/documentation
#message ("  ZSIM_WITH_ITBB          ${ZSIM_WITH_ITBB}")

#message(STATUS "Type cmake -LAH to see all variables")
