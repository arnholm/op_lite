@echo off

if not exist build mkdir build
pushd build

@echo on
conan install .. -s build_type=Debug
cmake -G"Visual Studio 16 2019" -A x64 -DCMAKE_INSTALL_PREFIX=.\install ..
cmake --build . --config Debug --verbose
@echo off

popd
@echo on