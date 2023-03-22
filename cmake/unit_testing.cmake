#######################################################################
# Setup
#######################################################################

message( STATUS "Adding Log unit testing" )

add_library( Log_testing INTERFACE )
target_link_libraries( Log_testing INTERFACE Log )

target_link_libraries(Log_testing INTERFACE catch-adapter)

#######################################################################
# Unit testing directories
#######################################################################

add_subdirectory( src/Log/test )
