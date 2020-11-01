cmake_minimum_required(VERSION 3.13)

macro(main_cmake_setup)

    # --------------------------------------------------------------------------
    # Build settings
    # --------------------------------------------------------------------------

    # Default is build-type Release
    if (NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Release)
    endif()

    # Default is to build shared libraries
    option(BUILD_SHARED_LIBS "Build shared libraries if ON (default)" ON)

    # Debug postfix to distinguish build products.
    set(CMAKE_DEBUG_POSTFIX "d")

    # Target output directories
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

    # Set c++11 standard and disable compiler extensions
    set(CMAKE_CXX_STANDARD          11)
    set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
    set(CMAKE_CXX_EXTENSIONS        FALSE)

    # Set common compiler and linker options for Microsoft Visual C++ Compiler
    if (MSVC)
        add_compile_definitions(_WIN32_WINNT=0x0601)
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MP")
        set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /OPT:REF /OPT:ICF")
        set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /NODEFAULTLIB:libcmtd.lib")
        set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /NODEFAULTLIB:msvcrtd.lib")
        set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /INCREMENTAL:NO")

        set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG:full /OPT:REF /OPT:ICF")     
    endif()

    # Fix x64 issues on Linux
    if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64" AND UNIX AND NOT APPLE)
        add_compile_options(-fPIC)
    endif()

    # --------------------------------------------------------------------------
    # Install settings
    # --------------------------------------------------------------------------

    # Set the environmental variable CPDE_USR if not set already
    if (NOT DEFINED ENV{CPDE_USR})
        set(ENV{CPDE_USR} ${CMAKE_BINARY_DIR}/install)
    endif()

    # Installation prefix accordingly.
    if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
        if (DEFINED ENV{CPDE_USR})
            set(CMAKE_INSTALL_PREFIX
                 "$ENV{CPDE_USR}" CACHE PATH
                 "Default installation prefix set to CPDE_USR env var" FORCE)
        else()
            set(CMAKE_INSTALL_PREFIX
                 "$ENV{CPDE_USR}" CACHE PATH
                 "Default installation prefix set to ./install" FORCE)
        endif()
    endif()

endmacro()
