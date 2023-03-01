cmake_minimum_required( VERSION 3.24 )
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/.cmake)
include( shacl_FetchContent )

#######################################################################
# Declare project dependencies
#######################################################################

shacl_FetchContent_Declare( catch-adapter
    GIT_REPOSITORY  ../../njoy/catch-adapter
    GIT_TAG         origin/master
    GIT_SHALLOW     TRUE
    )

shacl_FetchContent_Declare( spdlog
    GIT_REPOSITORY  ../../gabime/spdlog
    GIT_TAG         a51b4856377a71f81b6d74b9af459305c4c644f8
    )
set( SPDLOG_BUILD_TESTING CACHE BOOL OFF )

#######################################################################
# Load dependencies
#######################################################################

shacl_FetchContent_MakeAvailable(
    spdlog
    )

if (${Log_unit_tests})
    shacl_FetchContent_MakeAvailable(catch-adapter)
endif()

