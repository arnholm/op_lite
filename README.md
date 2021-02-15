# cpde_syslibs
system libraries common to several applications following the CPDE model

## Introduction
CPDE - Cross Platform Development Environment is a set of conventions and tools for building C++ software libraries
and applications. The build system is based on Code::Blocks

## Library synopsis

The follwing libraries are included

| Library name          | Description                     |
| --------------------- | ------------------------------  |
| op_lite               |  A portable, lightweight object persistence library for C++ |
| ce_angelscript        |  CPDE adaption of https://www.angelcode.com/angelscript/ |
| ce_angelscript_ex     |  CPDE extension library to  Angelscript |
| cf_syslib             |  CPDE System library with commonly used classes/functions |

## Building cpde_syslibs
The primary build system is based on Code::Blocks. However, the project files are dependent on following the CPDE conventions.
Alternatively, CMake and Conan can be used. See [README_CMake.md](./buildsystem/README_CMake.md).

