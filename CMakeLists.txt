project( Log )

if( NOT DEFINED Log_DEPENDENCIES )
    set( Log_DEPENDENCIES TRUE )
endif()

add_library( Log INTERFACE )
target_include_directories( Log INTERFACE src/ )
target_link_libraries( Log INTERFACE catch-adapter INTERFACE spdlog-adapter )
