include( FetchContent )


########################################################################
# Forward declarations
########################################################################


########################################################################
# Declare project dependencies
########################################################################

FetchContent_Declare( catch-adapter
    GIT_REPOSITORY  http://github.com/njoy/catch-adapter
    GIT_TAG         origin/build/fetchcontent
    GIT_SHALLOW     TRUE
    )

FetchContent_Declare( spdlog
    GIT_REPOSITORY  https://github.com/gabime/spdlog.git
    GIT_TAG         v0.9.0
    GIT_SHALLOW     TRUE
    )
set( SPDLOG_BUILD_TESTING CACHE BOOL OFF )


########################################################################
# Load dependencies
########################################################################

FetchContent_MakeAvailable(
    catch-adapter
    spdlog
    )

