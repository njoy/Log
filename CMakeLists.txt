########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.14 )
project( Log 
  VERSION 0.0
  LANGUAGES CXX )


########################################################################
# Project-wide setup
########################################################################

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED YES )

option( Log_unit_tests
    "Compile the Log unit tests and integrate with ctest" ON
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

set( SPDLOG_BUILD_TESTING CACHE BOOL OFF )
set( REPOSITORIES "release"
    CACHE STRING
    "Options for where to fetch repositories: develop, release, local"
    )

if( REPOSITORIES STREQUAL "develop" )
    include( cmake/develop_dependencies.cmake )

elseif( REPOSITORIES STREQUAL "release" )
    include( cmake/release_dependencies.cmake )


########################################################################
# Project targets
########################################################################

add_library( Log INTERFACE )

string( CONCAT prefix
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_include_directories(Log INTERFACE "${prefix}")

# If spdlog is found via building its name is spdlog, if installed it is spdlog::spdlog
if (TARGET spdlog::spdlog)
  target_link_libraries( Log INTERFACE spdlog::spdlog )
endif()

if (TARGET spdlog)
  target_link_libraries( Log INTERFACE spdlog )
endif()



#######################################################################
# Top-level Only
#######################################################################

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )

    # unit testing
    if( Log_unit_tests )
        include( cmake/unit_testing.cmake )
    endif()

endif()

#######################################################################
# Installation 
#######################################################################
install(TARGETS Log EXPORT Log-targets
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

install(EXPORT Log-targets
  FILE "Log-targets.cmake"
  DESTINATION share/cmake/Log)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
write_basic_package_version_file("Log-config-version.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Log-config.cmake.in
  ${CMAKE_BINARY_DIR}/Log-config.cmake
  INSTALL_DESTINATION share/cmake/Log)

install(DIRECTORY src/
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
  FILES_MATCHING PATTERN "*.hpp"
  PATTERN "*test*" EXCLUDE
)

install(FILES
  "${PROJECT_BINARY_DIR}/Log-config.cmake"
  "${PROJECT_BINARY_DIR}/Log-config-version.cmake"
  DESTINATION share/cmake/Log)

if(NOT subproject)
  set(CPACK_PACKAGE_VENDOR "Los Alamos National Laboratory")
  set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
  set(CPACK_PACKAGE_CONTACT "wim@lanl.gov")
  include(CPack)
endif()
