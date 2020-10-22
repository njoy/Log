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

FetchContent_Declare( spdlog-adapter
    GIT_REPOSITORY  http://github.com/njoy/spdlog-adapter
    GIT_TAG         origin/build/fetchcontent
    GIT_SHALLOW     TRUE
    )


########################################################################
# Load dependencies
########################################################################

FetchContent_MakeAvailable(
    catch-adapter
    spdlog-adapter
    )