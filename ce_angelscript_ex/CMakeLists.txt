cmake_minimum_required(VERSION 3.13)

#--------------------------------------------------------------------------------
# Set the name of the target if not already defined
#--------------------------------------------------------------------------------
if(NOT TARGET_CE_ANGELSCRIPT_EX)
    set(TARGET_CE_ANGELSCRIPT_EX ce_angelscript_ex)
endif()

set(_AS_STREAMS_SOURCE
    as_istream.cpp
    as_istream.h
    as_ostream.cpp
    as_ostream.h
)

set(_AS_XML_SOURCE
    as_class.cpp
    as_class.h
    as_constructor.cpp
    as_constructor.h
    as_description.cpp
    as_description.h
    as_doc.cpp
    as_doc.h
    as_line.cpp
    as_line.h
    as_member_function.cpp
    as_member_function.h
    as_parameter.cpp
    as_parameter.h
    as_return.cpp
    as_return.h
    as_xml.cpp
    as_xml.h
)

set(_IOSTREAM_SOURCE
    ASIStream.cpp
    ASIStream.h
    ASOStream.cpp
    ASOStream.h
    ASStreams.cpp
    ASStreams.h
)

source_group(as_streams FILES ${_AS_STREAMS_SOURCE})
source_group(as_xml     FILES ${_AS_XML_SOURCE})
source_group(iostream   FILES ${_IOSTREAM_SOURCE})


find_package(Threads)

message(STATUS "Building STATIC library ${TARGET_CE_ANGELSCRIPT_EX}")
add_library(${TARGET_CE_ANGELSCRIPT_EX} STATIC "")

target_compile_definitions(${TARGET_CE_ANGELSCRIPT_EX} PRIVATE CE_ANGELSCRIPT_EX_IMPLEMENTATION)
target_compile_definitions(${TARGET_CE_ANGELSCRIPT_EX} PRIVATE AS_USE_STLNAMES=1)
target_compile_definitions(${TARGET_CE_ANGELSCRIPT_EX} PRIVATE _CRT_SECURE_NO_WARNINGS)

target_include_directories(${TARGET_CE_ANGELSCRIPT_EX}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CONAN_INCLUDE_DIRS_BOOST}
)

target_sources(${TARGET_CE_ANGELSCRIPT_EX}
    PRIVATE
    ${_AS_STREAMS_SOURCE}
    ${_AS_XML_SOURCE}
    ${_IOSTREAM_SOURCE}
    as_args.cpp
    as_args_impl.cpp
    as_assert.cpp
    as_factory.cpp
    as_file.cpp
    as_include_callback.cpp
    as_initializer_vector.cpp
    as_reftype.cpp
    as_typeid.cpp
    as_vector.cpp
    as_args.h
    as_args_impl.h
    as_assert.h
    as_factory.h
    as_file.h
    as_include_callback.h
    as_initializer_vector.h
    as_reftype.h
    as_typeid.h
    as_vector.h
    ce_angelscript_ex_config.h
)

if(MSVC)
    target_compile_definitions(${TARGET_CE_ANGELSCRIPT_EX} PRIVATE CRT_SECURE_NO_WARNINGS)    
endif()

# Fix x64 issues on Linux
if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64" AND UNIX AND NOT APPLE)
    target_compile_options(${TARGET_CE_ANGELSCRIPT_EX} PRIVATE -fPIC)
endif()

target_link_libraries(${TARGET_CE_ANGELSCRIPT_EX}
    ${TARGET_CE_ANGELSCRIPT}
    ${TARGET_CF_SYSLIB}
    Threads::Threads)


#--------------------------------------------------------------------------------
# Installation
#--------------------------------------------------------------------------------

install(TARGETS ${TARGET_CE_ANGELSCRIPT_EX}
   CONFIGURATIONS Debug Release
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
   DESTINATION include/ce_angelscript_ex
   FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
   PATTERN ".cmp" EXCLUDE
 
)

#--------------------------------------------------------------------------------
# Tidy up
#--------------------------------------------------------------------------------
unset(_AS_STREAMS_SOURCE)
unset(_AS_XML_SOURCE)
unset(_IOSTREAM_SOURCE)
unset(PUBLIC_HEAD_FILES)