cmake_minimum_required(VERSION 3.26)

option(OHUD_BUILD_EXAMPLES "Build example projects with you can learn & play" OFF)

if (OHUD_BUILD_EXAMPLES)
    include(cmake/vcpkg.cmake)
    vcpkg_install_if_not_found(glfw3 imgui)
endif ()

project(ohud VERSION 0.0.1 LANGUAGES CXX)


file(GLOB_RECURSE OHUD_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")
file(GLOB_RECURSE OHUD_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")


add_library(ohud STATIC ${OHUD_SOURCES} ${OHUD_HEADERS})
add_library(ohud::ohud ALIAS ohud)

set_target_properties(ohud PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE}"
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON)

target_include_directories(ohud
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
            EXPORT omathTargets
            ARCHIVE DESTINATION lib
            LIBRARY DESTINATION lib
            RUNTIME DESTINATION bin)
else ()
    # Assume that IMGUI linked via VCPKG.
    find_package(imgui CONFIG REQUIRED)
    target_link_libraries(ohud PUBLIC imgui::imgui)
endif ()