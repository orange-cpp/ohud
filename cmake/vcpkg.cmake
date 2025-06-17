if (NOT VCPKG_CONFIGURED)
    set(VCPKG_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/extlibs/vcpkg")

    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/extlibs")
        file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/extlibs")
    endif ()

    if (NOT EXISTS "${VCPKG_ROOT}")
        message(STATUS "${VCPKG_ROOT} cannot find vcpkg directory. Executing git clone, please wait...")
        execute_process(
                COMMAND "git" "clone" "https://github.com/microsoft/vcpkg.git"
                WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/extlibs"
                OUTPUT_VARIABLE CLONE_OUTPUT
                ERROR_VARIABLE CLONE_ERROR
                RESULT_VARIABLE CLONE_STATUS
        )

        if (NOT CLONE_STATUS EQUAL 0)
            message(FATAL_ERROR "VCPKG has not been cloned. Git output:\n${CLONE_OUTPUT}\nGit error:\n${CLONE_ERROR}")
        endif ()
    endif()

    if(WIN32)
        set(VCPKG_TARGET_TRIPLET "x64-windows-static")
        set(VCPKG_BINARY "${VCPKG_ROOT}/vcpkg.exe")
    elseif(UNIX)
        set(VCPKG_TARGET_TRIPLET "x64-linux")
        set(VCPKG_BINARY "${VCPKG_ROOT}/vcpkg")
    endif()

    set(VCPKG_CONFIGURED TRUE)

    if(NOT EXISTS "${VCPKG_BINARY}")
        message(STATUS "${VCPKG_BINARY} not found, bootstrapping vcpkg, please wait...")
        if (WIN32 AND EXISTS "${VCPKG_ROOT}/bootstrap-vcpkg.bat")
            execute_process(
                    COMMAND "powershell" "-Command" "${VCPKG_ROOT}/bootstrap-vcpkg.bat"
                    WORKING_DIRECTORY "${VCPKG_ROOT}"
                    OUTPUT_VARIABLE BOOTSTRAP_OUTPUT
                    ERROR_VARIABLE BOOTSTRAP_ERROR
                    RESULT_VARIABLE BOOTSTRAP_STATUS
            )
        elseif(UNIX AND EXISTS "${VCPKG_ROOT}/bootstrap-vcpkg.sh")
            execute_process(
                    COMMAND "sh" "${VCPKG_ROOT}/bootstrap-vcpkg.sh"
                    WORKING_DIRECTORY "${VCPKG_ROOT}"
                    OUTPUT_VARIABLE BOOTSTRAP_OUTPUT
                    ERROR_VARIABLE BOOTSTRAP_ERROR
                    RESULT_VARIABLE BOOTSTRAP_STATUS
            )
        else ()
            message(FATAL_ERROR "Cannot find bootstrap script to get vcpkg executable")
        endif()

        if (NOT BOOTSTRAP_STATUS EQUAL 0)
            message(FATAL_ERROR "VCPKG bootstrap failed. Output:\n${BOOTSTRAP_OUTPUT}\nError:\n${BOOTSTRAP_ERROR}")
        endif ()
    endif()
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
    message(STATUS "VCPKG configured with no errors")
endif()

function(vcpkg_install PackageName)
    message(STATUS "Wait installing ${PackageName}")
    execute_process(
            COMMAND "${VCPKG_BINARY}" "install" "${PackageName}:${VCPKG_TARGET_TRIPLET}" "--clean-after-build"
            RESULT_VARIABLE INSTALL_RES
            OUTPUT_VARIABLE INSTALL_OUTPUT
            ERROR_VARIABLE INSTALL_ERROR
            WORKING_DIRECTORY ${VCPKG_ROOT}
    )

    if (NOT INSTALL_RES EQUAL 0)
        message(FATAL_ERROR "VCPKG install failed for ${PackageName}. Output:\n${INSTALL_OUTPUT}\nError:\n${INSTALL_ERROR}")
    endif ()
endfunction()

function(vcpkg_install_if_not_found)
    foreach(vcpkg_name IN LISTS ARGN)
        if(NOT EXISTS "${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/share/${vcpkg_name}")
            vcpkg_install(${vcpkg_name})
        else ()
            message(STATUS "Library \"${vcpkg_name}\" is already installed")
        endif()
    endforeach()
endfunction()