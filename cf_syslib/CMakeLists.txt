cmake_minimum_required(VERSION 3.10)

#--------------------------------------------------------------------------------
# Set the name of the target if not already defined
#--------------------------------------------------------------------------------
if(NOT TARGET_CF_SYSLIB)
    set(TARGET_CF_SYSLIB cf_syslib)
endif()

#--------------------------------------------------------------------------------
# Build
#--------------------------------------------------------------------------------

set(PUBLIC_HEAD_FILES
   replace_substring.h
   string_trim.h
   stringtokens.h
   xml_node.h
   xml_tree.h
   cf_syslib_config.h
)

set(SOURCE_FILES
   replace_substring.cpp
   string_trim.cpp
   stringtokens.cpp
   xml_node.cpp
   xml_tree.cpp
)

message(STATUS "Building SHARED library ${TARGET_CF_SERIAL}")
add_library(${TARGET_CF_SYSLIB} SHARED ${SOURCE_FILES} ${PUBLIC_HEAD_FILES})

target_compile_definitions(${TARGET_CF_SYSLIB} PRIVATE CF_SYSLIB_IMPLEMENTATION)

file(COPY ${PUBLIC_HEAD_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include/cf_syslib)
target_include_directories(${TARGET_CF_SYSLIB}
   PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
      $<INSTALL_INTERFACE:include>
      ${CONAN_INCLUDE_DIRS_BOOST}
)

target_link_libraries(${TARGET_CF_SYSLIB} Boost::disable_autolinking)

#--------------------------------------------------------------------------------
# Installation
#--------------------------------------------------------------------------------
install(TARGETS ${TARGET_CF_SYSLIB}
   CONFIGURATIONS Debug Release
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)

install(FILES ${PUBLIC_HEAD_FILES}
   DESTINATION include/cf_syslib
)

#--------------------------------------------------------------------------------
# Tidy up
#--------------------------------------------------------------------------------
unset(PUBLIC_HEAD_FILES)
unset(SOURCE_FILES)
