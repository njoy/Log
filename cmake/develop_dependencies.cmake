cmake_minimum_required( VERSION 3.14 )
include( FetchContent )

#######################################################################
# Declare project dependencies
#######################################################################

FetchContent_Declare( catch-adapter
    GIT_REPOSITORY  https://github.com/njoy/catch-adapter
    GIT_TAG         origin/master
    GIT_SHALLOW     TRUE
    )

FetchContent_Declare( spdlog
    GIT_REPOSITORY  https://github.com/gabime/spdlog
    GIT_TAG         a51b4856377a71f81b6d74b9af459305c4c644f8
    )

#######################################################################
# Load dependencies
#######################################################################

FetchContent_MakeAvailable(
    catch-adapter
    spdlog
    )
