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
    GIT_TAG         a51b4856377a71f81b6d74b9af459305c4c644f8
    GIT_SHALLOW     TRUE
    )
set( SPDLOG_BUILD_EXAMPLES OFF )
set( SPDLOG_BUILD_TESTING OFF )


########################################################################
# Load dependencies
########################################################################

FetchContent_MakeAvailable(
    catch-adapter
    spdlog
    )

