cmake_minimum_required(VERSION 3.8)

#--------------------------------------------------------------------------------
# Main CMakeLists file for the cpde_syslibs libraries.
#
# Recommended use:
#   $ mkdir build && cd build
#   $ conan install .. -s build_type=Debug
#   $ cmake --G"Visual Studio 16 2019" -A x64
#--------------------------------------------------------------------------------

project(cf_syslibs)

#--------------------------------------------------------------------------------
# Setup project.
# Defines common parameters for all libraries, such as compiler options.
#--------------------------------------------------------------------------------
set(BUILDSYSTEM_DIR "${CMAKE_CURRENT_LIST_DIR}/buildsystem/cmake")
include(${BUILDSYSTEM_DIR}/main.cmake)
main_cmake_setup()

#--------------------------------------------------------------------------------
# Configure conan packages
# Prerequisite: You need to call `conan install` before `cmake`.
#--------------------------------------------------------------------------------
if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(TARGETS)
 else()
    message(FATAL_ERROR "Conan packages not configured. Run `conan install`")
endif()

#--------------------------------------------------------------------------------
# Boost. Expect to find. Sets some aliases used later.
#--------------------------------------------------------------------------------
find_package("Boost" REQUIRED)

#--------------------------------------------------------------------------------
# Msgpack. Ignore if not found. Using Conan-variables anyway.
#--------------------------------------------------------------------------------
find_package("msgpack" QUIET)

#--------------------------------------------------------------------------------
# Add source directories
#--------------------------------------------------------------------------------
add_subdirectory(cf_syslib)
add_subdirectory(cf_serial)
add_subdirectory(op_lite)
add_subdirectory(ce_angelscript)

