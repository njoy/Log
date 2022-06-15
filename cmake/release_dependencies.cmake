cmake_minimum_required( VERSION 3.14 )
include( FetchContent )

#######################################################################
# Declare project dependencies
#######################################################################

FetchContent_Declare( spdlog
    GIT_REPOSITORY  https://github.com/gabime/spdlog
    GIT_TAG         v1.x
    )

FetchContent_Declare( catch-adapter
    GIT_REPOSITORY  https://github.com/njoy/catch-adapter
    GIT_TAG         fb84b82ebf7a4789aa43cea560680cf745c6ee4f
    )

#######################################################################
# Load dependencies
#######################################################################

FetchContent_MakeAvailable(
    spdlog
    catch-adapter
    )
