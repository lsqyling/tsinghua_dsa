
install(TARGETS dsa_static dsa_shared
        EXPORT dsa_targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

install(DIRECTORY "${dsa_SOURCE_DIR}/include/dsa"
        DESTINATION include
)

install(EXPORT dsa_targets
        FILE dsa_targets.cmake
        NAMESPACE dsa::
        DESTINATION lib/cmake/dsa
)

include(CMakePackageConfigHelpers)

configure_package_config_file(${dsa_SOURCE_DIR}/cmake/templates/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/dsa-config.cmake"
        INSTALL_DESTINATION lib/cmake/dsa
)
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/dsa-config-version.cmake"
        COMPATIBILITY SameMinorVersion)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/dsa-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/dsa-config-version.cmake"
        DESTINATION lib/cmake/dsa
)

# uninstall target
if(NOT TARGET uninstall)
    configure_file(
            "${dsa_SOURCE_DIR}/cmake/templates/cmake_uninstall.cmake.in"
            "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
            IMMEDIATE @ONLY)

    add_custom_target(uninstall
            COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
