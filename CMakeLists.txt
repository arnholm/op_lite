cmake_minimum_required(VERSION 3.10)

project(cf_syslibs)

#
# Macros
#
macro(remove_cxx_flag flag)
  string(REPLACE "${flag}" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
endmacro()

#
# Options
#
option(BUILD_SHARED_LIBS "Build shared libraries if ON (default)" ON)

#
# Target naming and output directories
#
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_DEBUG_POSTFIX d)


#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_SANDARD_REQUIRED True)
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
if(MSVC)
    add_compile_options("/MD" "/Ox" "/GF" "/EHsc" "/W3" 
        "/D_CRT_SECURE_NO_WARNINGS" 
        "/D_CRT_NONSTDC_NO_DEPRECATE"
        "/D_CRT_SECURE_DEPRECATE"
    )
else()
    remove_cxx_flag("-O3")
    add_compile_options("-W" "-std=c++0x" "-fexceptions" "-Os" "-DNPOCH" -pipe) 
endif()

add_subdirectory(cf_syslib)

