########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.14 )
project( Log LANGUAGES CXX )

########################################################################
# Project-wide setup
########################################################################

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED YES )

option( Log_unit_tests
    "Compile the Log unit tests and integrate with ctest" ON
    )

########################################################################
# Dependencies
########################################################################

include( cmake/Log_dependencies.cmake )

########################################################################
# Project targets
########################################################################

add_library( Log INTERFACE )
target_include_directories( Log INTERFACE src/ )
target_link_libraries( Log
    INTERFACE catch-adapter
    INTERFACE spdlog
    )

#######################################################################
# Top-level Only
#######################################################################

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )

    # unit testing
    if( Log_unit_tests )
        include( cmake/unit_testing.cmake )
    endif()

endif()
