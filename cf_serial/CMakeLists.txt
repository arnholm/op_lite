cmake_minimum_required(VERSION 3.10)

set(LIBRARY_NAME cf_serial_static)

project(${LIBRARY_NAME})

add_compile_definitions(CF_SERIAL_IMPLEMENTATION)

# cf_serial library is only offered as static
add_library(${LIBRARY_NAME} STATIC
   cf_reader.cpp
   cf_serial_simple.cpp
)

target_include_directories(${LIBRARY_NAME}
   PUBLIC
   ${Boost_INCLUDE_DIRS}
)

target_link_libraries(${LIBRARY_NAME}  Boost::disable_autolinking)



