cmake_minimum_required(VERSION 3.10)

#--------------------------------------------------------------------------------
# Set the name of the target if not already defined
#--------------------------------------------------------------------------------
if(NOT TARGET_CF_SERIAL)
    set(TARGET_CF_SERIAL cf_serial)
endif()

#--------------------------------------------------------------------------------
# Build
#--------------------------------------------------------------------------------


set(PUBLIC_HEAD_FILES
   cf_reader.h
   cf_serial_simple.h
)

set(SOURCE_FILES
   cf_reader.cpp
   cf_serial_simple.cpp
)

# cf_serial library is only offered as static
message(STATUS "Building STATIC library ${TARGET_CF_SERIAL}")
add_library(${TARGET_CF_SERIAL} STATIC
   ${SOURCE_FILES} ${PUBLIC_HEAD_FILES}
   cf_serial_config.h
)

target_include_directories(${TARGET_CF_SERIAL}
   PRIVATE
   ${Boost_INCLUDE_DIRS}
)

target_compile_definitions(${TARGET_CF_SERIAL} PRIVATE CF_SERIAL_IMPLEMENTATION)

target_link_libraries(${TARGET_CF_SERIAL}  Boost::disable_autolinking)

#--------------------------------------------------------------------------------
# Installation
#--------------------------------------------------------------------------------
install(TARGETS ${TARGET_CF_SERIAL}
   CONFIGURATIONS Debug Release
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)

install(FILES ${PUBLIC_HEAD_FILES}
   DESTINATION include/cf_serial
)

#--------------------------------------------------------------------------------
# Tidy up
#--------------------------------------------------------------------------------
unset(PUBLIC_HEAD_FILES)
unset(SOURCE_FILES)


