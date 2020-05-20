########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.16 )
project( Log LANGUAGES CXX )

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
    INTERFACE spdlog-adapter
    )
