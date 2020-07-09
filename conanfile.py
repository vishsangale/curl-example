import conans


class CurlTest(conans.ConanFile):
    name = "curlTest"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"
    requires = "libcurl/7.69.1"
    generators = "cmake", "cmake_paths", "virtualenv", "virtualrunenv"
    default_options = {"*:shared": True}

    def build(self):
        cmake = conans.CMake(self)
        cmake.configure(source_folder=".")
        cmake.build()
