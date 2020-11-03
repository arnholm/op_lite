@echo off
if not exist build mkdir build
pushd build

if not exist Debug mkdir Debug
pushd Debug
conan install ../.. -s build_type=Debug
cmake -G"Visual Studio 16 2019" ../..
cmake --build . --config Debug --target install --verbose
popd

if not exist Release mkdir Release
pushd Release
conan install ../.. -s build_type=Release
cmake -G"Visual Studio 16 2019" ../..
cmake --build . --config Release --target install --verbose
popd

popd
@echo on