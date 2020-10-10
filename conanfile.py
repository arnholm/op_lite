from conans import ConanFile, CMake, tools

class CpdeSyslibsConan(ConanFile):
    name = "cpde_syslibs"
    version = "0.1"
    license = """Copyright (C) 2017 Carsten Arnholm arnholm@arnholm.org

                cpde_syslibs uses variable licensing, see individual source files for details.

                cpde_syslibs is provided "AS IS" with NO WARRANTY OF ANY KIND, INCLUDING
                THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR
                PURPOSE."""
    url = "https://github.com/arnholm/cpde_syslibs.git"
    settings = "os", "compiler", "build_type", "arch"
    requires = "boost/1.74.0", "msgpack/3.3.0"
    options = {"shared": [True, False]}
    default_options = {"shared": True }
    generators = "cmake"
    exports_sources = "CMakeLists.txt", "buildsystem/cmake/*", \
        "cf_syslib/*", "!cf_syslib/.cmp"

    def build(self):
        cmake = CMake(self)
        cmake.definitions['CMAKE_BUILD_WITH_INSTALL_RPATH'] = True
        cmake.verbose = True
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.exp", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
