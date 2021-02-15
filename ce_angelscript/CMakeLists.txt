cmake_minimum_required(VERSION 3.13)

#--------------------------------------------------------------------------------
# Set the name of the target if not already defined
#--------------------------------------------------------------------------------
if(NOT TARGET_CE_ANGELSCRIPT)
    set(TARGET_CE_ANGELSCRIPT ce_angelscript)
endif()

message(STATUS "Current Binary Dir " ${CMAKE_CURRENT_BINARY_DIR})
#--------------------------------------------------------------------------------
# Optionally include add-ons
#--------------------------------------------------------------------------------
option(ANGELSCRIPT_ADD_ON "Include the Angelscript add-on packages in build" ON)

#--------------------------------------------------------------------------------
# Define source groups
#--------------------------------------------------------------------------------
set(ANGELSCRIPT_VERSION 2.33.0)
set(ANGELSCRIPT_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/angelscript_${ANGELSCRIPT_VERSION}/sdk)
set(ANGELSCRIPT_PATH        ${ANGELSCRIPT_ROOT}/angelscript)
set(ANGELSCRIPT_ADD_ON_PATH ${ANGELSCRIPT_ROOT}/add_on)
set(ANGELSCRIPT_HEADERS
    ${ANGELSCRIPT_PATH}/include/angelscript.h
    ${ANGELSCRIPT_PATH}/source/as_array.h
    ${ANGELSCRIPT_PATH}/source/as_builder.h
    ${ANGELSCRIPT_PATH}/source/as_bytecode.h
    ${ANGELSCRIPT_PATH}/source/as_callfunc.h
    ${ANGELSCRIPT_PATH}/source/as_compiler.h
    ${ANGELSCRIPT_PATH}/source/as_config.h
    ${ANGELSCRIPT_PATH}/source/as_configgroup.h
    ${ANGELSCRIPT_PATH}/source/as_context.h
    ${ANGELSCRIPT_PATH}/source/as_criticalsection.h
    ${ANGELSCRIPT_PATH}/source/as_datatype.h
    ${ANGELSCRIPT_PATH}/source/as_debug.h
    ${ANGELSCRIPT_PATH}/source/as_generic.h
    ${ANGELSCRIPT_PATH}/source/as_map.h
    ${ANGELSCRIPT_PATH}/source/as_memory.h
    ${ANGELSCRIPT_PATH}/source/as_module.h
    ${ANGELSCRIPT_PATH}/source/as_objecttype.h
    ${ANGELSCRIPT_PATH}/source/as_outputbuffer.h
    ${ANGELSCRIPT_PATH}/source/as_parser.h
    ${ANGELSCRIPT_PATH}/source/as_property.h
    ${ANGELSCRIPT_PATH}/source/as_restore.h
    ${ANGELSCRIPT_PATH}/source/as_scriptcode.h
    ${ANGELSCRIPT_PATH}/source/as_scriptengine.h
    ${ANGELSCRIPT_PATH}/source/as_scriptfunction.h
    ${ANGELSCRIPT_PATH}/source/as_scriptnode.h
    ${ANGELSCRIPT_PATH}/source/as_scriptobject.h
    ${ANGELSCRIPT_PATH}/source/as_string.h
    ${ANGELSCRIPT_PATH}/source/as_string_util.h
    ${ANGELSCRIPT_PATH}/source/as_texts.h
    ${ANGELSCRIPT_PATH}/source/as_thread.h
    ${ANGELSCRIPT_PATH}/source/as_tokendef.h
    ${ANGELSCRIPT_PATH}/source/as_tokenizer.h
    ${ANGELSCRIPT_PATH}/source/as_typeinfo.h
    ${ANGELSCRIPT_PATH}/source/as_variablescope.h
)

set(ANGELSCRIPT_SOURCE
    ${ANGELSCRIPT_PATH}/source/as_atomic.cpp
    ${ANGELSCRIPT_PATH}/source/as_builder.cpp
    ${ANGELSCRIPT_PATH}/source/as_bytecode.cpp
    ${ANGELSCRIPT_PATH}/source/as_callfunc.cpp
    ${ANGELSCRIPT_PATH}/source/as_callfunc_mips.cpp
    ${ANGELSCRIPT_PATH}/source/as_callfunc_x86.cpp
    ${ANGELSCRIPT_PATH}/source/as_callfunc_x64_gcc.cpp
    ${ANGELSCRIPT_PATH}/source/as_callfunc_x64_msvc.cpp
    ${ANGELSCRIPT_PATH}/source/as_callfunc_x64_mingw.cpp
    ${ANGELSCRIPT_PATH}/source/as_compiler.cpp
    ${ANGELSCRIPT_PATH}/source/as_configgroup.cpp
    ${ANGELSCRIPT_PATH}/source/as_context.cpp
    ${ANGELSCRIPT_PATH}/source/as_datatype.cpp
    ${ANGELSCRIPT_PATH}/source/as_gc.cpp
    ${ANGELSCRIPT_PATH}/source/as_generic.cpp
    ${ANGELSCRIPT_PATH}/source/as_globalproperty.cpp
    ${ANGELSCRIPT_PATH}/source/as_memory.cpp
    ${ANGELSCRIPT_PATH}/source/as_module.cpp
    ${ANGELSCRIPT_PATH}/source/as_objecttype.cpp
    ${ANGELSCRIPT_PATH}/source/as_outputbuffer.cpp
    ${ANGELSCRIPT_PATH}/source/as_parser.cpp
    ${ANGELSCRIPT_PATH}/source/as_restore.cpp
    ${ANGELSCRIPT_PATH}/source/as_scriptcode.cpp
    ${ANGELSCRIPT_PATH}/source/as_scriptengine.cpp
    ${ANGELSCRIPT_PATH}/source/as_scriptfunction.cpp
    ${ANGELSCRIPT_PATH}/source/as_scriptnode.cpp
    ${ANGELSCRIPT_PATH}/source/as_scriptobject.cpp
    ${ANGELSCRIPT_PATH}/source/as_string.cpp
    ${ANGELSCRIPT_PATH}/source/as_string_util.cpp
    ${ANGELSCRIPT_PATH}/source/as_thread.cpp
    ${ANGELSCRIPT_PATH}/source/as_tokenizer.cpp
    ${ANGELSCRIPT_PATH}/source/as_typeinfo.cpp
    ${ANGELSCRIPT_PATH}/source/as_variablescope.cpp
)

set(ANGELSCRIPT_ADD_ON_SOURCE "")
if(ANGELSCRIPT_ADD_ON)
   set(ANGELSCRIPT_ADD_ON_SOURCE
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc.hpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_common.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_common.hpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_config.hpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_container_deque.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_container_deque.hpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_container_list.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_container_list.hpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_container_listing.hpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_container_listing_heavy.hpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_container_map.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_container_map.hpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_container_mapped_templated_shared.hpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_container_mapped_templated_shared_method.hpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_container_set.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_container_set.hpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_container_shared.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_container_shared.hpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_container_templated_shared.hpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_container_templated_shared_method.hpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_container_tempspec_shared.hpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_container_tempspec_shared_method.hpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_container_unordered_map.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_container_unordered_map.hpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_container_unordered_set.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_container_unordered_set.hpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_container_vector.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_container_vector.hpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_enginestorage.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_enginestorage.hpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_hash.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_hash.hpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_registration.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_serializer.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_serializer.hpp
      ${ANGELSCRIPT_ADD_ON_PATH}/aatc/aatc_templatemagic.hpp
      ${ANGELSCRIPT_ADD_ON_PATH}/autowrapper/aswrappedcall.h
      ${ANGELSCRIPT_ADD_ON_PATH}/autowrapper/generator/generateheader.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/contextmgr/contextmgr.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/contextmgr/contextmgr.h
      ${ANGELSCRIPT_ADD_ON_PATH}/datetime/datetime.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/datetime/datetime.h
      ${ANGELSCRIPT_ADD_ON_PATH}/debugger/debugger.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/debugger/debugger.h
      ${ANGELSCRIPT_ADD_ON_PATH}/scriptany/scriptany.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/scriptany/scriptany.h
      ${ANGELSCRIPT_ADD_ON_PATH}/scriptarray/scriptarray.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/scriptarray/scriptarray.h
      ${ANGELSCRIPT_ADD_ON_PATH}/scriptbuilder/scriptbuilder.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/scriptbuilder/scriptbuilder.h
      ${ANGELSCRIPT_ADD_ON_PATH}/scriptdictionary/scriptdictionary.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/scriptdictionary/scriptdictionary.h
      ${ANGELSCRIPT_ADD_ON_PATH}/scriptfile/scriptfile.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/scriptfile/scriptfile.h
      ${ANGELSCRIPT_ADD_ON_PATH}/scriptfile/scriptfilesystem.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/scriptfile/scriptfilesystem.h
      ${ANGELSCRIPT_ADD_ON_PATH}/scriptgrid/scriptgrid.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/scriptgrid/scriptgrid.h
      ${ANGELSCRIPT_ADD_ON_PATH}/scripthandle/scripthandle.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/scripthandle/scripthandle.h
      ${ANGELSCRIPT_ADD_ON_PATH}/scripthelper/scripthelper.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/scripthelper/scripthelper.h
      ${ANGELSCRIPT_ADD_ON_PATH}/scriptmath/scriptmath.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/scriptmath/scriptmath.h
      ${ANGELSCRIPT_ADD_ON_PATH}/scriptmath/scriptmathcomplex.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/scriptmath/scriptmathcomplex.h
      ${ANGELSCRIPT_ADD_ON_PATH}/scriptstdstring/scriptstdstring.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/scriptstdstring/scriptstdstring.h
      ${ANGELSCRIPT_ADD_ON_PATH}/scriptstdstring/scriptstdstring_utils.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/serializer/serializer.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/serializer/serializer.h
      ${ANGELSCRIPT_ADD_ON_PATH}/weakref/weakref.cpp
      ${ANGELSCRIPT_ADD_ON_PATH}/weakref/weakref.h
   )
endif()

# Assembly code for MSVC and architecture x86_64

if(MSVC AND CMAKE_CL_64)
    enable_language(ASM_MASM)
    if(CMAKE_ASM_MASM_COMPILER_WORKS)
        set(ANGELSCRIPT_SOURCE ${ANGELSCRIPT_SOURCE} ${ANGELSCRIPT_PATH}/source/as_callfunc_x64_msvc_asm.asm)
    else()
        message(FATAL ERROR "MSVC x86_64 target requires a working assembler")
    endif()
endif()

# Assembly code for ARM target

if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "^arm")
    enable_language(ASM)
    if(CMAKE_ASM_COMPILER_WORKS)
        set(ANGELSCRIPT_SOURCE ${ANGELSCRIPT_SOURCE} ${ANGELSCRIPT_PATH}/source/as_callfunc_arm.cpp ${ANGELSCRIPT_PATH}/source/as_callfunc_arm_gcc.S)
        set_property(SOURCE ${ANGELSCRIPT_PATH}/source/as_callfunc_arm_gcc.S APPEND PROPERTY COMPILE_FLAGS " -Wa,-mimplicit-it=always")
    else()
        message(FATAL ERROR "ARM target requires a working assembler")
    endif()
endif()

#--------------------------------------------------------------------------------
# Build
#--------------------------------------------------------------------------------

message(STATUS "Building STATIC library ${TARGET_CE_ANGELSCRIPT}")
add_library(${TARGET_CE_ANGELSCRIPT} STATIC
    ${ANGELSCRIPT_SOURCE}
    ${ANGELSCRIPT_HEADERS}
    ${ANGELSCRIPT_ADD_ON_SOURCE})

target_compile_definitions(${TARGET_CE_ANGELSCRIPT} PRIVATE CE_ANGELSCRIPT_IMPLEMENTATION)
target_compile_definitions(${TARGET_CE_ANGELSCRIPT} PRIVATE AS_NO_EXCEPTIONS)
target_compile_definitions(${TARGET_CE_ANGELSCRIPT} PRIVATE AS_USE_STLNAMES=1)
target_compile_definitions(${TARGET_CE_ANGELSCRIPT} PRIVATE _CRT_SECURE_NO_WARNINGS)

find_package(Threads)

target_link_libraries(${TARGET_CE_ANGELSCRIPT} Threads::Threads)

# Add dependency to include directories.
#   The interface to this library is defined through the file
#   ce_angelscript.h found in ${ANGELSCRIPT_ROOT}.
#   The add-on's include angelscript.h found under {ANGELSCRIPT_PATH}/include.

file(COPY ${ANGELSCRIPT_ROOT}/ce_angelscript.h    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include/ce_angelscript)
file(COPY ${ANGELSCRIPT_ROOT}/angelscript/include DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include/ce_angelscript/angelscript)
file(COPY ${ANGELSCRIPT_ROOT}/add_on              DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include/ce_angelscript
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")

target_include_directories(${TARGET_CE_ANGELSCRIPT}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE
    ${ANGELSCRIPT_PATH}/include
)

#--------------------------------------------------------------------------------
# Installation
#--------------------------------------------------------------------------------

install(TARGETS ${TARGET_CE_ANGELSCRIPT}
   CONFIGURATIONS Debug Release
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)

install(DIRECTORY ${ANGELSCRIPT_ROOT}/
   DESTINATION include/ce_angelscript
   FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
   PATTERN ".cmp" EXCLUDE
   PATTERN "docs"  EXCLUDE
   PATTERN "samples"  EXCLUDE
   PATTERN "angelscript/projects" EXCLUDE
   PATTERN "angelscript/lib" EXCLUDE
)

#--------------------------------------------------------------------------------
# Tidy up
#--------------------------------------------------------------------------------
unset(ANGELSCRIPT_SOURCE)
unset(ANGELSCRIPT_HEADERS)
unset(ANGELSCRIPT_ADD_ON_SOURCE)

