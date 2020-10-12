# Building cpde_syslibs with CMake

## Prerequisites

cpde_syslibs can be built using [CMake](https://cmake.org/). Depencies to 3rd party libraries can be resolved using [Conan](https://conan.io/). Conan is a C/C++ Package Manager. 

### Installing CMake

Refer to [CMake website](https://cmake.org/download/) for how to best install CMake.

### Installing Python (Linux)

Ubuntu 20.04 comes with Python 3 pre-installed. Depending on your version of Linux, you may gave to install it. 

Make sure you have Python 3 installed. The recommended way to install on Ubuntu is as follows.

First install Python3 and pip3 if not already installed (.
```sh
$ sudo apt install python3 python3-pip
$ python3 --version
Python 3.8.5 (or similar)
$ pip3 --version
```
Most likely, you do not need Python 2.x although it is installed as part of Ubuntu. If you are ready to drop previous versions of Python and stick to Python 3, you might as well introduce aliases by placing the following into `~/.bash_aliases`.
```
$ alias python=/usr/bin/python3
$ alias pip=/usr/bin/pip3
```
### Installing Conan

The best way to install Conan is by using the command
```
$ pip3 install conan
```
Add the path `~/.local/bin` to your PATH. 

Check the `conan` command is available.
```
$ conan --version
Conan version 1.30.1
```

## Building

Having installed the prerequisites, the libraries can be buildt using the follow commands.

```
$ mkdir build && cd build
$ conan install ..
$ cmake ..
$ cmake --build .
```


