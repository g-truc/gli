# Readme

![gli](http://gli.g-truc.net/logo.png)

[OpenGL Image](http://gli.g-truc.net/) (*GLI*) is a header only C++ image library for graphics software.

*GLI* provides classes and functions to load image files (*[KTX](https://www.khronos.org/opengles/sdk/tools/KTX/)* and *[DDS](https://msdn.microsoft.com/en-us/library/windows/desktop/bb943990%28v=vs.85%29.aspx)*), facilitate graphics APIs texture creation, compare textures, access texture texels, sample textures, convert textures, generate mipmaps, etc.

This library works perfectly with *[OpenGL](https://www.opengl.org)* or *[Vulkan](https://www.khronos.org/vulkan)* but it also ensures interoperability with other third party libraries and SDK.
It is a good candidate for software rendering (raytracing / rasterisation), image processing, image based software testing or any development context that requires a simple and convenient image library.

*GLI* is written in C++11. It is a platform independent library with no dependence and it supports the following compilers:
- [Apple Clang 4.0](https://developer.apple.com/library/mac/documentation/CompilerTools/Conceptual/LLVMCompilerOverview/index.html) and higher
- [GCC](http://gcc.gnu.org/) 4.6 and higher
- [Intel C++ Composer](https://software.intel.com/en-us/intel-compilers) XE 2013 and higher
- [LLVM](http://llvm.org/) 3.2 and higher
- [Visual C++](http://www.visualstudio.com/) 2010 and higher
- Any conform C++11 compiler

For more information about *GLI*, please have a look at the [API reference documentation](http://gli.g-truc.net/0.8.0/api/index.html).
The source code and the documentation are licensed under the [Happy Bunny License (Modified MIT) or the MIT License](copying.md).

Thanks for contributing to the project by [submitting issues](https://github.com/g-truc/gli/issues) for bug reports and feature requests. Any feedback is welcome at [gli@g-truc.net](mailto://gli@g-truc.net).

## Project Health

| Service | System | Compiler | Status |
| ------- | ------ | -------- | ------ |
| [Drone](https://drone.io/github.com/g-truc/gli) | Linux 64 bits | GCC 4.6.3 | [![Build Status](https://drone.io/github.com/g-truc/gli/status.png)](https://drone.io/github.com/g-truc/gli/latest) |

## [Lastest release](https://github.com/g-truc/gli/releases/latest)

## Links

- [Release notes](releases.md)
- [Code sample: Creating an OpenGL texture object from file](sample-creating-texture-object.md)
- [Code sample: Generating mipmaps and converting float textures to rgb9e5](sample-convert.md)

