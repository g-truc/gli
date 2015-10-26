![gli](doc/logo.png)

[OpenGL Image](http://gli.g-truc.net/) (*GLI*) is a header only C++ image library for graphics software.

*GLI* provides classes and functions to load image files (*[KTX](https://www.khronos.org/opengles/sdk/tools/KTX/)* and *[DDS](https://msdn.microsoft.com/en-us/library/windows/desktop/bb943990%28v=vs.85%29.aspx)*), facilitating graphics APIs texture creation, comparing, manipulating textures, etc.

This library works perfectly with *[OpenGL](https://www.opengl.org)* but it also ensures interoperability with other third party libraries and SDK. It is a good candidate for software rendering (raytracing / rasterisation), image processing, physic simulations and any development context that requires a simple and convenient image library.

*GLI* is written in C++11. It is a platform independent library with no dependence and it supports the following compilers:
- [Apple Clang 4.0](https://developer.apple.com/library/mac/documentation/CompilerTools/Conceptual/LLVMCompilerOverview/index.html) and higher
- [GCC](http://gcc.gnu.org/) 4.6 and higher
- [Intel C++ Composer](https://software.intel.com/en-us/intel-compilers) XE 2013 and higher
- [LLVM](http://llvm.org/) 3.2 and higher
- [Visual C++](http://www.visualstudio.com/) 2010 and higher
- Any conform C++11 compiler

For more information about *GLI*, please have a look at the [API reference documentation](http://gli.g-truc.net/0.7.0/api/index.html).
The source code and the documentation are licensed under the [Happy Bunny License (Modified MIT) or the MIT License](./copying.txt).

To clone *GLI* and its dependency [*GLM*](http://glm.g-truc.net/) (which is included as a submodule), please clone this repo with `git clone --recursive`.  To update your clone's copy of *GLM*, run the command `git submodule foreach git pull origin master`.

Thanks for contributing to the project by <link href="https://github.com/g-truc/gli/issues">submitting issues</link> for bug reports and feature requests. Any feedback is welcome at <link href="mailto://gli@g-truc.net">gli@g-truc.net</link>.

```c++
#include <gli/gli.hpp>

/// Filename can be KTX or DDS files
GLuint createTexture(char const* Filename)
{
	gli::texture Texture = gli::load(Filename);
	if(Texture.empty())
		return 0;

	gli::gl GL;
	gli::gl::format const Format = GL.translate(Texture.format());
	GLenum Target = GL.translate(Texture.target());

	GLuint TextureName = 0;
	glGenTextures(1, &TextureName);
	glBindTexture(Target, TextureName);
	glTexParameteri(Target, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(Target, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(Texture.levels() - 1));
	glTexParameteri(Target, GL_TEXTURE_SWIZZLE_R, Format.Swizzle[0]);
	glTexParameteri(Target, GL_TEXTURE_SWIZZLE_G, Format.Swizzle[1]);
	glTexParameteri(Target, GL_TEXTURE_SWIZZLE_B, Format.Swizzle[2]);
	glTexParameteri(Target, GL_TEXTURE_SWIZZLE_A, Format.Swizzle[3]);

	glm::tvec3<GLsizei> const Dimensions(Texture.dimensions());
	GLsizei const FaceTotal = static_cast<GLsizei>(Texture.layers() * Texture.faces());

	switch(Texture.target())
	{
	case gli::TARGET_1D:
		glTexStorage1D(
			Target, static_cast<GLint>(Texture.levels()), Format.Internal, Dimensions.x);
		break;
	case gli::TARGET_1D_ARRAY:
	case gli::TARGET_2D:
	case gli::TARGET_CUBE:
		glTexStorage2D(
			Target, static_cast<GLint>(Texture.levels()), Format.Internal,
			Dimensions.x, Texture.target() == gli::TARGET_2D ? Dimensions.y : FaceTotal);
		break;
	case gli::TARGET_2D_ARRAY:
	case gli::TARGET_3D:
	case gli::TARGET_CUBE_ARRAY:
		glTexStorage3D(
			Target, static_cast<GLint>(Texture.levels()), Format.Internal,
			Dimensions.x, Dimensions.y,
			Texture.target() == gli::TARGET_3D ? Dimensions.z : FaceTotal);
		break;
	default:
		assert(0);
		break;
	}

	for(std::size_t Layer = 0; Layer < Texture.layers(); ++Layer)
	for(std::size_t Face = 0; Face < Texture.faces(); ++Face)
	for(std::size_t Level = 0; Level < Texture.levels(); ++Level)
	{
		GLsizei const LayerGL = static_cast<GLsizei>(Layer);
		glm::tvec3<GLsizei> Dimensions(Texture.dimensions(Level));
		Target = gli::is_target_cube(Texture.target())
			? static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + Face)
			: Target;

		switch(Texture.target())
		{
		case gli::TARGET_1D:
			if(gli::is_compressed(Texture.format()))
				glCompressedTexSubImage1D(
					Target, static_cast<GLint>(Level), 0, Dimensions.x,
					Format.Internal, static_cast<GLsizei>(Texture.size(Level)),
					Texture.data(Layer, Face, Level));
			else
				glTexSubImage1D(
					Target, static_cast<GLint>(Level), 0, Dimensions.x,
					Format.External, Format.Type,
					Texture.data(Layer, Face, Level));
			break;
		case gli::TARGET_1D_ARRAY:
		case gli::TARGET_2D:
		case gli::TARGET_CUBE:
			if(gli::is_compressed(Texture.format()))
				glCompressedTexSubImage2D(
					Target, static_cast<GLint>(Level),
					0, 0,
					Dimensions.x,
					Texture.target() == gli::TARGET_1D_ARRAY ? : Dimensions.y,
					Format.Internal, static_cast<GLsizei>(Texture.size(Level)),
					Texture.data(Layer, Face, Level));
			else
				glTexSubImage2D(
					Target, static_cast<GLint>(Level),
					0, 0,
					Dimensions.x,
					Texture.target() == gli::TARGET_1D_ARRAY ? LayerGL : Dimensions.y,
					Format.External, Format.Type,
					Texture.data(Layer, Face, Level));
			break;
		case gli::TARGET_2D_ARRAY:
		case gli::TARGET_3D:
		case gli::TARGET_CUBE_ARRAY:
			if(gli::is_compressed(Texture.format()))
				glCompressedTexSubImage3D(
					Target, static_cast<GLint>(Level),
					0, 0, 0,
					Dimensions.x, Dimensions.y,
					Texture.target() == gli::TARGET_3D ? Dimensions.z : LayerGL,
					Format.Internal, static_cast<GLsizei>(Texture.size(Level)),
					Texture.data(Layer, Face, Level));
			else
				glTexSubImage3D(
					Target, static_cast<GLint>(Level),
					0, 0, 0,
					Dimensions.x, Dimensions.y,
					Texture.target() == gli::TARGET_3D ? Dimensions.z : LayerGL,
					Format.External, Format.Type,
					Texture.data(Layer, Face, Level));
			break;
		default: assert(0); break;
		}
	}
	return TextureName;
}
```

## Project Health

| Service | System | Compiler | Status |
| ------- | ------ | -------- | ------ |
| [Drone](https://drone.io/github.com/g-truc/gli) | Linux 64 bits | GCC 4.6.3 | [![Build Status](https://drone.io/github.com/g-truc/gli/status.png)](https://drone.io/github.com/g-truc/gli/latest) |

## [Lastest release](https://github.com/g-truc/gli/releases/latest)

## Release notes

#### [GLI 0.8.0.0](https://github.com/g-truc/gli/releases/latest) - 2015-XX-XX
- Added texture swizzle support
- Added support for load and store
- Added support for many new formats
- Added KMG support and spec proposal
- Added texture memory swizzle support
- Added generate_mipmaps for uncompressed formats
- Added sampler 1D, 2D and 3D
- Added sampler texel fetch and texel write
- Added texture lod
- Added sampler clear
- Reordered formats
- Fixed PVRTC2 support
- Fixed luminance and alpha translation to OpenGL #56
- Fixed DXGI_FORMAT_B8G8R8X8_UNORM_SRGB support #59
- Fixed FORMAT_RGBA8_UNORM DDS loading using DDPF_RGBA mode #60

#### [GLI 0.7.0.0](https://github.com/g-truc/gli/releases/tag/0.7.0.0) - 2015-09-01
- Added KTX loading and saving
- Added gli::load for generic file loading, either DDS or KTX files depending on filename extensions
- Added gli::save for generic file saving, either DDS or KTX files depending on filename extensions
- Added texture views using different texture format, including compressed texture formats
- Added fine granularity includes
- Improved API documentation
- Much faster texture comparisons is non optimal cases. (Measured ~21x faster on Intel IVB)
- Explicitly handling of texture targets: fixed various cases of cubemap and texture arrays failing to load with DDS
- Fixed GCC build
- Fixed warnings
- Fixed saved DDS header size on #52

#### [GLI 0.6.1.1](https://github.com/g-truc/gli/releases/tag/0.6.1.1) - 2015-07-18
- Updated API documentation
- Fixed link error

#### [GLI 0.6.1.0](https://github.com/g-truc/gli/releases/tag/0.6.1.0) - 2015-07-18
- Fixed interface inconsistencies
- Improved clear(), data() and size() performance using caching
- Removed internal dependence to std::fstream
- Added FORMAT_BGRX8_UNORM and FORMAT_BGRX8_SRGB support #48, #43
- Improved FORMAT_RGB8_UNORM loading

#### [GLI 0.6.0.0](https://github.com/g-truc/gli/releases/tag/0.6.0.0) - 2015-06-28
- Large refactoring
- Added loading DDS from memory
- Added saving DDS to memory
- Improved DDS coverage for R, RG, RGB and RGBA formats
- Added DDS ASTC, PVRTC, ATC and ETC support
- Added DDS alpha, luminance and alpha luminance support
- Added PVRTC2, ETC2 and EAC formats

#### [GLI 0.5.1.1](https://github.com/g-truc/gli/releases/tag/0.5.1.1) - 2014-01-20
- Fixed swizzled RGB channel when reading back a DDS
- Fixed getMask* link error

#### [GLI 0.5.1.0](https://github.com/g-truc/gli/releases/tag/0.5.1.0) - 2014-01-18
- Added flip function
- Added level_count function
- Fixed interaction with std::map (#33)
- Added texelFetch and texelWrite functions

#### [GLI 0.5.0.0](https://github.com/g-truc/gli/releases/tag/0.5.0.0) - 2013-11-24
- Essencially a rewrite of the library
- Added explicit copies
- Added single memory allocation per texture storage
- Added texture views
- Added texture copies
- Added comparison operators
- Added clear

#### GLI 0.4.1.0: 2013-03-10
- Added DDS saving
- Fixed GCC build
- Fixed XCode build

#### GLI 0.4.0.0: 2013-01-28
- Large API refactoring
- Performance improvements at loading: 50x in debug and 50% in release build
- Added texture2DArray
- Added textureCube and textureCubeArray
- Added texture3D
- Added texture1D and texture1DArray
- Improved DDS loading support

#### GLI 0.3.0.3: 2011-04-05
- Fixed bugs

#### GLI 0.3.0.2: 2011-02-08
- Fixed bugs

#### GLI 0.3.0.1: 2010-10-15
- Fixed bugs

#### GLI 0.3.0.0: 2010-10-01
- Added DDS10 load and store (BC1 - BC7)
- Added extension system
- Added automatic OpenGL texture object creation from file

#### GLI 0.2.2.0: 2010-09-07
- Added DDS exporter

#### GLI 0.2.1.1: 2010-05-12
- Fixed GCC build

#### GLI 0.2.1.0: 2010-02-15
- Added texelWrite function
- Fixed Visual Studio 2010 warnings
- Added readme.txt and copying.txt

#### GLI 0.2.0.0: 2010-01-10
- Updated API
- Removed Boost dependency

#### GLI 0.1.1.0: 2009-09-18
- Fixed DDS loader
- Added RGB8 to DDS loader
- Added component swizzle operation
- Added 32 bits integer components support
- Fixed texel fetch

#### GLI 0.1.0.0: 2009-03-28
- Added TGA loader
- Added DDS loader
- Added duplicate, crop, partial copy
- Added mipmaps generation.

