



set(CMAKE_INSTALL_LIBDIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_INSTALL_BINDIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_INSTALL_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)



install(TARGETS dsa
        EXPORT dsa_targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY "${dsa_SOURCE_DIR}/include/dsa"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT dsa_targets
        FILE dsa_targets.cmake
        NAMESPACE tsinghua::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/dsa
)

include(CMakePackageConfigHelpers)

configure_package_config_file(${dsa_SOURCE_DIR}/cmake/templates/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/dsa-config.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/dsa
)
#message("${CMAKE_CURRENT_BINARY_DIR}")
#write_basic_package_version_file(
#        "${CMAKE_CURRENT_BINARY_DIR}/dsa-config-version.cmake"
#        COMPATIBILITY SameMinorVersion)
#
#install(FILES
#        "${CMAKE_CURRENT_BINARY_DIR}/dsa-config.cmake"
#        "${CMAKE_CURRENT_BINARY_DIR}/dsa-config-version.cmake"
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/dsa
#)

# uninstall target
if(NOT TARGET uninstall)
    configure_file(
            "${dsa_SOURCE_DIR}/cmake/templates/cmake_uninstall.cmake.in"
            "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
            IMMEDIATE @ONLY)

    add_custom_target(uninstall
            COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
