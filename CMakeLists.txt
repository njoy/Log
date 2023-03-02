########################################################################
# Preamble
########################################################################

set(subproject OFF)
if(DEFINED PROJECT_NAME)
  set(subproject ON)
endif()

cmake_minimum_required( VERSION 3.24 )
project( Log LANGUAGES CXX )



########################################################################
# Project-wide setup
########################################################################

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED YES )

include(CTest)
include(CMakeDependentOption)

cmake_dependent_option( Log_unit_tests
    "Compile the Log unit tests and integrate with ctest" ON
    BUILD_TESTING AND NOT ${subproject}
)
option( Log_installation
    "Install Log" ON
    )
option( strict_compile
    "Treat all warnings as errors." ON
    )

# Compile flags
set( common_flags "-Wall" "-Wextra" "-Wpedantic" )
set( strict_flags "-Werror" )
set( release_flags "-O3" )
set( debug_flags "-O0" "-g" )


########################################################################
# Dependencies
########################################################################

set( REPOSITORIES "release"
    CACHE STRING
    "Options for where to fetch repositories: develop, release, local"
    )

if( REPOSITORIES STREQUAL "develop" )
    include( cmake/develop_dependencies.cmake )

elseif( REPOSITORIES STREQUAL "release" )
    include( cmake/release_dependencies.cmake )

elseif( REPOSITORIES STREQUAL "local" )
    include( cmake/local_dependencies.cmake )

endif()


########################################################################
# Project targets
########################################################################
include(GNUInstallDirs)

string( CONCAT prefix
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

add_library( Log INTERFACE
    )

add_library( njoy::Log ALIAS Log )

target_include_directories( Log INTERFACE ${prefix} )

# treat spdlog specially due to mixed namespace usage
if (TARGET spdlog::spdlog)
    target_link_libraries(Log INTERFACE spdlog::spdlog)
else()
    target_link_libraries(Log INTERFACE spdlog)
endif()



#######################################################################
# Top-level Only
#######################################################################

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )

    # unit testing
    if( ${Log_unit_tests} )
        include( cmake/unit_testing.cmake )
    endif()

endif()
#######################################################################
# Installation 
#######################################################################

if(Log_installation)
    include(CMakePackageConfigHelpers)

    install(TARGETS Log EXPORT Log-targets
      ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    )

    install(EXPORT Log-targets
      FILE "Log-targets.cmake"
      NAMESPACE njoy::
      DESTINATION share/cmake/Log
    )

    configure_package_config_file(
      ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Log-config.cmake.in
      ${CMAKE_BINARY_DIR}/Log-config.cmake
      INSTALL_DESTINATION share/cmake/Log
    )

    install(DIRECTORY src/
      DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
      FILES_MATCHING PATTERN "*.hpp"
      PATTERN "*test*" EXCLUDE
    )

    install(FILES
      "${PROJECT_BINARY_DIR}/Log-config.cmake"
      DESTINATION share/cmake/Log
    )

    if(NOT subproject)
      set(CPACK_PACKAGE_VENDOR "Los Alamos National Laboratory")
      set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
      include(CPack)
    endif()
endif()

