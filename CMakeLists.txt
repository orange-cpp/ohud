cmake_minimum_required(VERSION 3.26)

option(OHUD_BUILD_EXAMPLES "Build example projects with you can learn & play" ${PROJECT_IS_TOP_LEVEL})

if (OHUD_BUILD_EXAMPLES)
    include(cmake/vcpkg.cmake)
    vcpkg_install_if_not_found(glfw3 imgui)
endif ()

project(ohud VERSION 0.0.1 LANGUAGES CXX)


file(GLOB_RECURSE OHUD_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")
file(GLOB_RECURSE OHUD_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")


add_library(${PROJECT_NAME} STATIC ${OHUD_SOURCES} ${OHUD_HEADERS})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE}"
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>   # Use this path when building the project
        $<INSTALL_INTERFACE:include>                             # Use this path when the project is installed
)

if (OHUD_BUILD_EXAMPLES)
    find_package(imgui CONFIG REQUIRED)
    add_subdirectory(examples)
endif ()

# IMGUI is being linked as submodule
if (TARGET imgui)
    target_link_libraries(ohud PUBLIC imgui)
    install(TARGETS imgui
            EXPORT ohudTargets
            ARCHIVE DESTINATION lib
            LIBRARY DESTINATION lib
            RUNTIME DESTINATION bin)
else ()
    # Assume that IMGUI linked via VCPKG.
    find_package(imgui CONFIG REQUIRED)
    target_link_libraries(ohud PUBLIC imgui::imgui)
endif ()

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        ARCHIVE DESTINATION lib COMPONENT ${PROJECT_NAME}
        LIBRARY DESTINATION lib COMPONENT ${PROJECT_NAME}
        RUNTIME DESTINATION bin COMPONENT ${PROJECT_NAME}
)
install(DIRECTORY include/ DESTINATION include COMPONENT ${PROJECT_NAME})
install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION lib/cmake/${PROJECT_NAME} COMPONENT ${PROJECT_NAME}
)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)
configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
)
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION lib/cmake/${PROJECT_NAME}
)
