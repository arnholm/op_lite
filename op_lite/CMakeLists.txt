cmake_minimum_required(VERSION 3.13)

set(LIBRARY_NAME op_lite)

project(${LIBRARY_NAME})

add_compile_definitions(OP_LITE_IMPLEMENTATION)
add_compile_definitions(SQLITE_ENABLE_COLUMN_METADATA)
add_compile_definitions(HAVE_USLEEP)

# Sources included on all platforms
set(_lzmalib_sources 
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
set(_miniz_sources
   miniz/op_miniz.cpp
   miniz/op_miniz.h
   miniz/miniz.c
)
set(_op_containers_sources
   op_map.cpp
   op_map.h
   op_msgpack.h
   op_packed.cpp
   op_packed.h
   op_vector.cpp
   op_vector.h
)
set(_op_type_factory_sources
   op_class_factory.cpp
   op_class_factory.h
   op_type_factory.cpp
   op_type_factory.h
)
set(_op_lite_sources
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
set(_sqLayer_sources
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
set(_sqlite_sources
   sqlite3/sqlite3.c
   sqlite3/sqlite3.h
   sqlite3/sqlite3ext.h
)

# Sources included on Windows only
set(_lzmalib_sources_msvc
   lzmalib/LzFindMt.c
   lzmalib/LzFindMt.h
   lzmalib/Threads.c
   lzmalib/Threads.h
)

source_group(lzmalib          FILES ${_lzmalib_sources})
source_group(lzmalib_WIN_ONLY FILES ${_lzmalib_sources_msvc})
source_group(miniz            FILES ${_miniz_sources})
source_group(sqlite3          FILES ${_sqlite_sources})
source_group(sqLayer          FILES ${_sqLayer_sources})
source_group(op_lite          FILES ${_op_lite_sources})
source_group(op_type_factory  FILES ${_op_type_factory_sources})
source_group(op_containers    FILES ${_op_containers_sources})

# Do not compile this file. Is used as head file only.
set_source_files_properties( miniz/miniz.c PROPERTIES HEADER_FILE_ONLY TRUE)

add_library(${LIBRARY_NAME} "")

target_sources(${LIBRARY_NAME}
   PRIVATE
   ${_lzmalib_sources}
   ${_miniz_sources}
   ${_op_containers_sources}
   ${_op_type_factory_sources}
   ${_op_lite_sources}
   ${_sqLayer_sources}
   ${_sqlite_sources}
)

if (MSVC)
   target_sources(${LIBRARY_NAME}
      PRIVATE
      ${_lzmalib_sources_msvc})
endif()

target_include_directories(${LIBRARY_NAME}
   PUBLIC
   ${CONAN_INCLUDE_DIRS_BOOST}
   ${CONAN_INCLUDE_DIRS_MSGPACK}
)

target_link_libraries(${LIBRARY_NAME} Boost::disable_autolinking)
