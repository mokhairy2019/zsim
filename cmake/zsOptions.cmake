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

message ("  zsim_COEFF_TYPE        ${zsim_COEFF_TYPE}")
message ("  zsim_INDEX_TYPE        ${zsim_INDEX_TYPE}")

## #################################################################
## Options list: Standard options
## #################################################################

option(zsim_BUILD_AXL           "Build Axl Plugin"         false  )
if  (${zsim_BUILD_AXL})
    message ("  zsim_BUILD_AXL         ${zsim_BUILD_AXL}")
endif()

option(zsim_BUILD_EXAMPLES      "Build examples"            true   )
if  (${zsim_BUILD_EXAMPLES})
    message ("  zsim_BUILD_EXAMPLES    ${zsim_BUILD_EXAMPLES}")
endif()

option(zsim_BUILD_LIB           "Build shared library"      true   )
message ("  zsim_BUILD_LIB         ${zsim_BUILD_LIB}")

option(zsim_BUILD_MEX           "Build Mex files"           false  )
if  (${zsim_BUILD_MEX})
    message ("  zsim_BUILD_MEX         ${zsim_BUILD_MEX}")
endif()

option(zsim_BUILD_PCH           "Build precompiled headers" false  )
if  (${zsim_BUILD_PCH})
    message ("  zsim_BUILD_PCH         ${zsim_BUILD_PCH}")
endif()

option(zsim_BUILD_PVIEW         "Build Paraview Plugin"     false  )
if  (${zsim_BUILD_PVIEW})
    message ("  zsim_BUILD_PVIEW        ${zsim_BUILD_VIEW}")
endif()

option(zsim_BUILD_RHINOPLUGINS  "Build Rhino THB Plugins"   false  )
if  (${zsim_BUILD_RHINOPLUGINS})
    message ("  zsim_BUILD_RHINOPLUGINS ${zsim_BUILD_RHINOPLUGINS}")
endif()

option(zsim_BUILD_UNITTESTS     "Build unittests"           false  )
if  (${zsim_BUILD_UNITTESTS})
    message ("  zsim_BUILD_UNITTESTS   ${zsim_BUILD_UNITTESTS}")
endif()

option(zsim_EXTRA_DEBUG         "Extra debug features"      false  )
if  (${zsim_EXTRA_DEBUG})
    message ("  zsim_EXTRA_DEBUG       ${zsim_EXTRA_DEBUG}")
endif()

option(zsim_WITH_ADIFF          "With auto-diff"            false  )
if  (${zsim_WITH_ADIFF})
    message ("  zsim_WITH_ADIFF        ${zsim_WITH_ADIFF}")
endif()

option(zsim_WITH_CODIPACK       "With CoDiPack"             false  )
if  (${zsim_WITH_CODIPACK})
    message ("  zsim_WITH_CODIPACK     ${zsim_WITH_CODIPACK}")
endif()

option(zsim_WITH_IPOPT          "With IpOpt"                false  )
if  (${zsim_WITH_IPOPT})
    message ("  zsim_WITH_IPOPT        ${zsim_WITH_IPOPT}")
endif()

#option(zsim_WITH_METIS          "With METIS"                false )
#if  (${zsim_WITH_METIS})
#message ("  zsim_WITH_METIS        ${zsim_WITH_METIS}")
#endif()

option(zsim_WITH_GMP           "With GMP"                  false  )
if  (${zsim_WITH_GMP})
    message ("  zsim_WITH_GMP         ${zsim_WITH_GMP}")
endif()

option(zsim_WITH_MPFR           "With MPFR"                  false  )
if  (${zsim_WITH_MPFR})
    message ("  zsim_WITH_MPFR         ${zsim_WITH_MPFR}")
endif()

option(zsim_WITH_MPI            "With MPI"                  false  )
if  (${zsim_WITH_MPI})
    message ("  zsim_WITH_MPI          ${zsim_WITH_MPI}")
endif()

option(zsim_WITH_MPQ            "With MPQ"                  false  )
if  (${zsim_WITH_MPQ})
    message ("  zsim_WITH_MPQ          ${zsim_WITH_MPQ}")
endif()

option(zsim_WITH_OCC            "With OpenCascade"          false  )
if  (${zsim_WITH_OCC})
    message ("  zsim_WITH_OCC          ${zsim_WITH_OCC}")
endif()

option(zsim_WITH_ONURBS         "With OpenNurbs"            false  )
if  (${zsim_WITH_ONURBS})
    message ("  zsim_WITH_ONURBS       ${zsim_WITH_ONURBS}")
endif()

option(zsim_WITH_OPENMP         "With OpenMP"               false  )
if  (${zsim_WITH_OPENMP})
    message ("  zsim_WITH_OPENMP       ${zsim_WITH_OPENMP}")
endif()

option(zsim_WITH_PARDISO        "With PARDISO"              false  )
if  (${zsim_WITH_PARDISO})
    message ("  zsim_WITH_PARDISO      ${zsim_WITH_PARDISO}")
endif()

option(zsim_WITH_PASTIX         "With PastiX"               false  )
if  (${zsim_WITH_PASTIX})
    message ("  zsim_WITH_PASTIX       ${zsim_WITH_PASTIX}")
endif()

option(zsim_WITH_PSOLID         "With Parasolid"            false  )
if  (${zsim_WITH_PSOLID})
    message ("  zsim_WITH_PSOLID       ${zsim_WITH_PSOLID}")
endif()

option(zsim_WITH_SPECTRA        "With Spectra"              false  )
if  (${zsim_WITH_SPECTRA})
    message ("  zsim_WITH_SPECTRA      ${zsim_WITH_SPECTRA}")
endif()

option(zsim_WITH_SUPERLU        "With SuperLU"              false  )
if  (${zsim_WITH_SUPERLU})
    message ("  zsim_WITH_SUPERLU      ${zsim_WITH_SUPERLU}")
endif()

option(zsim_WITH_TAUCS          "With Taucs"                false  )
if  (${zsim_WITH_TAUCS})
    message ("  zsim_WITH_TAUCS        ${zsim_WITH_TAUCS}")
endif()

option(zsim_WITH_TRILINOS       "With TRILINOS"             false  )
if  (${zsim_WITH_TRILINOS})
    message ("  zsim_WITH_TRILINOS     ${zsim_WITH_TRILINOS}")
endif()

option(zsim_WITH_UMFPACK        "With Umfpack"              false  )
if  (${zsim_WITH_UMFPACK})
    message ("  zsim_WITH_UMFPACK      ${zsim_WITH_UMFPACK}")
endif()

option(zsim_WITH_UNUM           "With Universal NUMber"     false  )
if  (${zsim_WITH_UNUM})
    message ("  zsim_WITH_UNUM         ${zsim_WITH_UNUM}")
endif()

## #################################################################
## Options list: Extra options
## #################################################################

option(EIGEN_USE_MKL_ALL         "Eigen use MKL"                 false  )
if (EIGEN_USE_MKL_ALL)
    message ("  EIGEN_USE_MKL_ALL       ${EIGEN_USE_MKL_ALL}")
endif()

option(zsim_BUILD_CPPLOT        "Build cpplot"                  false  )
if (zsim_BUILD_CPPLOT)
    message ("  zsim_BUILD_CPPLOT      ${zsim_BUILD_CPPLOT}")
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    option(zsim_BUILD_COVERAGE      "Build with coverage"          false )
    if (zsim_BUILD_COVERAGE)
        message ("  zsim_BUILD_COVERAGE    ${zsim_BUILD_COVERAGE}")
    endif()
endif(CMAKE_COMPILER_IS_GNUCXX)

option(zsim_BUILD_QT_APP        "Build Qt application"          false  )
if (zsim_BUILD_QT_APP)
    message ("  zsim_BUILD_QT_APP      ${zsim_BUILD_QT_APP}")
endif()

option(zsim_WARNINGS            "Enable G+Smo related warnings" false  )
if (zsim_WARNINGS)
    message ("  zsim_WARNINGS          ${zsim_WARNINGS}")
endif()

option(zsim_WITH_VTK            "With VTK"                      false  )
if (zsim_WITH_VTK)
    message ("  zsim_WITH_VTK          ${zsim_WITH_VTK}")
endif()

if(DEFINED ${isGit} AND ${isGit} EQUAL 0)
    message(STATUS "Type \"${GIT_EXECUTABLE} submodule\" to see the state of submodules")
endif()

#https://www.threadingbuildingblocks.org/documentation
#message ("  zsim_WITH_ITBB          ${zsim_WITH_ITBB}")

#message(STATUS "Type cmake -LAH to see all variables")
