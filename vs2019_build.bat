@echo off
if not exist build mkdir build
pushd build

@REM if not exist Debug mkdir Debug
@REM pushd Debug
@REM conan install ../.. -s build_type=Debug
@REM cmake -G"Visual Studio 16 2019" ../..
@REM cmake --build . --config Debug --target install --verbose
@REM popd

if not exist Release mkdir Release
pushd Release
conan install ../.. -s build_type=Release
cmake -G"Visual Studio 16 2019" ../..
cmake --build . --config Release --target install --verbose
popd

popd
@echo on