#--------------------------------------------------------------------------------
# Main CMakeLists file for the cpde_syslibs libraries.
#
# The cpde_syslibs are a collection of libraries which are not entirely dependent
# of each other. This makefile build all the targets.
# 
# The followings projects/sub-projects are defined:
# project_cf_syslibs:   This main project
# project_cf_syslib:    Builds the cf_syslib library
# project_cf_serial:    Builds the cf_serial library
# project_op_lite:      Builds the op_lite library
# project_ce_angelscript: Builds the ce_angelscript and ce_angelscript_ex libraries
#
# Recommended use:
#   $ mkdir build && cd build
#   $ conan install .. -s build_type=Debug
#   $ cmake --G"Visual Studio 16 2019" -A x64 ..
#   $ cmake --build .
#--------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.8)
project(project_cf_syslibs)

#--------------------------------------------------------------------------------
# Setup project.
# Defines common parameters for all libraries, such as compiler options.
#--------------------------------------------------------------------------------
set(BUILDSYSTEM_DIR "${CMAKE_CURRENT_LIST_DIR}/buildsystem/cmake")
include(${BUILDSYSTEM_DIR}/main.cmake)
main_cmake_setup()

message(STATUS "CMAKE_INSTALL_PREFIX " ${CMAKE_INSTALL_PREFIX} )

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
# Name the targets. This can be used to override default names
# given in the subdirectories.
#--------------------------------------------------------------------------------
set(TARGET_CF_SYSLIB          "cf_syslib")
set(TARGET_CF_SERIAL          "cf_serial")
set(TARGET_OP_LITE            "op_lite")
set(TARGET_CE_ANGELSCRIPT     "ce_angelscript")
set(TARGET_CE_ANGELSCRIPT_EX  "ce_angelscript_ex")

#--------------------------------------------------------------------------------
# Define sub-projects. Add sub directories, one for each target.
#--------------------------------------------------------------------------------
project(project_cf_syslib)
add_subdirectory(cf_syslib)

project(project_cf_serial)
add_subdirectory(cf_serial)

project(project_op_lite)
add_subdirectory(op_lite)

project(project_ce_angelscript)
add_subdirectory(ce_angelscript)
add_subdirectory(ce_angelscript_ex)

#--------------------------------------------------------------------------------
# Setup target's dependencies
#--------------------------------------------------------------------------------
add_dependencies(${TARGET_CE_ANGELSCRIPT_EX}
    ${TARGET_CE_ANGELSCRIPT} ${TARGET_CF_SYSLIB}
)
