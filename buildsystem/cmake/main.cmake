macro(main_cmake_setup)

    # --------------------------------------------------------------------------
    # Build settings
    # --------------------------------------------------------------------------

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
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi /MP")
        set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG:full /OPT:REF /OPT:ICF /Zi")
        set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /NODEFAULTLIB:libcmtd.lib")
        set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /NODEFAULTLIB:msvcrtd.lib")
        set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /INCREMENTAL:NO")

        set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG:full /OPT:REF /OPT:ICF /Zi")     
    endif()

endmacro()