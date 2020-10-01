cmake_minimum_required(VERSION 3.10)

project(cf_syslib)

add_definitions( -DCF_SYSLIB_IMPLEMENTATION)

add_library(cf_syslib
   replace_substring.cpp
   string_trim.cpp
   stringtokens.cpp
   xml_node.cpp
   xml_tree.cpp
)

