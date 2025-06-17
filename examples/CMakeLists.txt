project(ohud_showcase)


add_executable(ohud_example ohud_example.cpp gui/main_window.cpp gui/main_window.hpp)

set_target_properties(ohud_example PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE}"
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON)


find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(ohud_example PRIVATE glfw imgui::imgui ohud opengl32)