cmake_minimum_required(VERSION 3.13)

#--------------------------------------------------------------------------------
# Set the name of the target if not already defined
#--------------------------------------------------------------------------------
if(NOT TARGET_OP_LITE)
    set(TARGET_OP_LITE op_lite)
endif()


#--------------------------------------------------------------------------------
# Define source groups
#--------------------------------------------------------------------------------
set(LZMALIB_SOURCES 
   lzmalib/7zTypes.h
   lzmalib/Alloc.c
   lzmalib/Alloc.h
   lzmalib/Compiler.h
   lzmalib/LzFind.c
   lzmalib/LzFind.h
   lzmalib/LzHash.h
   lzmalib/LzmaDec.c
   lzmalib/LzmaDec.h
   lzmalib/LzmaEnc.c
   lzmalib/LzmaEnc.h
   lzmalib/LzmaLib.c
   lzmalib/LzmaLib.h
   lzmalib/op_lzma.cpp
   lzmalib/op_lzma.h
   lzmalib/Precomp.h
)
set(MINIZ_SOURCES
   miniz/op_miniz.cpp
   miniz/op_miniz.h
   miniz/miniz.c
)
set(OP_CONTAINER_SOURCES
   op_map.cpp
   op_map.h
   op_msgpack.h
   op_packed.cpp
   op_packed.h
   op_vector.cpp
   op_vector.h
)
set(OP_TYPE_FACTORY_SOURCES
   op_class_factory.cpp
   op_class_factory.h
   op_type_factory.cpp
   op_type_factory.h
)
set(OP_LITE_SOURCES
   op_class_name.cpp
   op_class_name.h
   op_database.cpp
   op_database.h
   op_database_helper.cpp
   op_database_helper.h
   op_lite_config.h
   op_manager.cpp
   op_manager.h
   op_new.cpp
   op_new.h
   op_object.cpp
   op_object.h
   op_ptr.cpp
   op_ptr.h
   op_root.cpp
   op_root.h
   op_transaction.cpp
   op_transaction.h
   op_unique_ptr.cpp
   op_unique_ptr.h
   op_value.cpp
   op_value.h
   op_version.h
)
set(SQLAYER_SOURCES
   sqBlob.cpp
   sqBlob.h
   sqColumn.cpp
   sqColumn.h
   sqDatabase.cpp
   sqDatabase.h
   sqQuery.cpp 
   sqQuery.h 
   sqRef.cpp 
   sqRef.h 
   sqRow.cpp
   sqRow.h
   sqStatement.cpp
   sqStatement.h
   sqTable.cpp
   sqTable.h
   sqTransaction.cpp
   sqTransaction.h
   sqValue.cpp
   sqValue.h
)
set(SQLITE_SOURCES
   sqlite3/sqlite3.c
   sqlite3/sqlite3.h
   sqlite3/sqlite3ext.h
)

# Sources included on Windows only
set(LZMALIB_SOURCES_msvc
   lzmalib/LzFindMt.c
   lzmalib/LzFindMt.h
   lzmalib/Threads.c
   lzmalib/Threads.h
)

source_group(lzmalib          FILES ${LZMALIB_SOURCES})
source_group(miniz            FILES ${MINIZ_SOURCES})
source_group(sqlite3          FILES ${SQLITE_SOURCES})
source_group(sqLayer          FILES ${SQLAYER_SOURCES})
source_group(op_lite          FILES ${OP_LITE_SOURCES})
source_group(op_type_factory  FILES ${OP_TYPE_FACTORY_SOURCES})
source_group(op_containers    FILES ${OP_CONTAINER_SOURCES})

# Do not compile this file. Is used as head file only.
set_source_files_properties( miniz/miniz.c PROPERTIES HEADER_FILE_ONLY TRUE)

#--------------------------------------------------------------------------------
# Build
#--------------------------------------------------------------------------------

add_library(${TARGET_OP_LITE} "")

get_target_property(target_type ${TARGET_OP_LITE} TYPE)
if (target_type STREQUAL STATIC_LIBRARY)
   message(STATUS "Building STATIC library ${TARGET_CF_SERIAL}")
   target_compile_definitions(${TARGET_OP_LITE} PRIVATE OP_LITE_STATIC_LIBRARY)
else()
   message(STATUS "Building SHARED library ${TARGET_CF_SERIAL}")
endif()

target_compile_definitions(${TARGET_OP_LITE} PRIVATE OP_LITE_IMPLEMENTATION)
target_compile_definitions(${TARGET_OP_LITE} PRIVATE SQLITE_ENABLE_COLUMN_METADATA)
target_compile_definitions(${TARGET_OP_LITE} PRIVATE HAVE_USLEEP)
if (MSVC)
   target_compile_definitions(${TARGET_OP_LITE} PRIVATE _CRT_SECURE_NO_WARNINGS)
   target_compile_definitions(${TARGET_OP_LITE} PRIVATE _CRT_NONSTDC_NO_DEPRECATE)
   target_compile_definitions(${TARGET_OP_LITE} PRIVATE _CRT_SECURE_DEPRECATE)
else()
   target_compile_definitions(${TARGET_OP_LITE} PRIVATE _7ZIP_ST)
endif()


target_sources(${TARGET_OP_LITE}
   PRIVATE
   ${LZMALIB_SOURCES}
   ${MINIZ_SOURCES}
   ${OP_CONTAINER_SOURCES}
   ${OP_TYPE_FACTORY_SOURCES}
   ${OP_LITE_SOURCES}
   ${SQLAYER_SOURCES}
   ${SQLITE_SOURCES}
)

if (MSVC)
   source_group(lzmalib_WIN_ONLY FILES ${LZMALIB_SOURCES_msvc})
   target_sources(${TARGET_OP_LITE}
      PRIVATE
      ${LZMALIB_SOURCES_msvc})
endif()



target_include_directories(${TARGET_OP_LITE}
   PRIVATE
   ${CONAN_INCLUDE_DIRS_BOOST}
   ${CONAN_INCLUDE_DIRS_MSGPACK}
)

target_link_libraries(${TARGET_OP_LITE} Boost::disable_autolinking)

#--------------------------------------------------------------------------------
# Installation
#--------------------------------------------------------------------------------

install(TARGETS ${TARGET_OP_LITE}
   CONFIGURATIONS Debug Release
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
   DESTINATION include/op_lite
   FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
   PATTERN ".cmp" EXCLUDE
   PATTERN "doc"  EXCLUDE
)

#--------------------------------------------------------------------------------
# Tidy up
#--------------------------------------------------------------------------------
unset(LZMALIB_SOURCES)
unset(MINIZ_SOURCES)
unset(SQLITE_SOURCES)
unset(SQLAYER_SOURCES)
unset(OP_LITE_SOURCES)
unset(OP_TYPE_FACTORY_SOURCES)
unset(OP_CONTAINER_SOURCES)
