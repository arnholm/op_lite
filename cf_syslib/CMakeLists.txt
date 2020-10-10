cmake_minimum_required(VERSION 3.10)

set(LIBRARY_NAME cf_syslib)

project(${LIBRARY_NAME})

add_compile_definitions(CF_SYSLIB_IMPLEMENTATION)

add_library(${LIBRARY_NAME}
   replace_substring.cpp
   string_trim.cpp
   stringtokens.cpp
   xml_node.cpp
   xml_tree.cpp
)

target_include_directories(${LIBRARY_NAME}
   PUBLIC
   ${CONAN_INCLUDE_DIRS_BOOST}
)

target_link_libraries(${LIBRARY_NAME} Boost::disable_autolinking)



