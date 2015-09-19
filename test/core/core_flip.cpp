//////////////////////////////////////////////////////////////////////////////////
/// OpenGL Image (gli.g-truc.net)
///
/// Copyright (c) 2008 - 2015 G-Truc Creation (www.g-truc.net)
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///
/// @ref core
/// @file gli/core/copy.cpp
/// @date 2013-02-04 / 2013-11-25
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#include <gli/gli.hpp>
#include <iostream>

template <typename texture, typename genType>
int test_texture
(
	texture const & Texture,
	genType const & ClearColor,
	genType const & FirstColor
)
{
	int Error(0);

	texture TextureA(gli::copy(Texture));
	TextureA.template clear<genType>(ClearColor);
	*TextureA.template data<genType>() = FirstColor;

	texture TextureB = gli::flip(TextureA);
	Error += TextureA != TextureB ? 0 : 1;

	texture TextureC = gli::flip(TextureB);
	Error += TextureC == TextureA ? 0 : 1;
	
	return Error;
}

struct dxt1_block {
	uint16_t Color0;
	uint16_t Color1;
	uint8_t Row0;
	uint8_t Row1;
	uint8_t Row2;
	uint8_t Row3;
};

struct dxt3_block {
	uint16_t AlphaRow0;
	uint16_t AlphaRow1;
	uint16_t AlphaRow2;
	uint16_t AlphaRow4;
	uint16_t Color0;
	uint16_t Color1;
	uint8_t Row0;
	uint8_t Row1;
	uint8_t Row2;
	uint8_t Row3;
};

struct dxt5_block {
	uint8_t Alpha0;
	uint8_t Alpha1;
	uint16_t AlphaRows0;
	uint16_t AlphaRows1;
	uint16_t AlphaRows3;
	uint16_t Color0;
	uint16_t Color1;
	uint8_t Row0;
	uint8_t Row1;
	uint8_t Row2;
	uint8_t Row3;
};

int main()
{
	static_assert(sizeof(dxt1_block) == 8, "");
	static_assert(sizeof(dxt3_block) == 16, "");
	static_assert(sizeof(dxt5_block) == 16, "");
	
	int Error(0);

	gli::texture2D::dim_type const TextureSize(32);
	std::size_t const Levels = gli::levels(TextureSize);

	Error += test_texture(
		gli::texture2D(gli::FORMAT_R8_UNORM, TextureSize, Levels),
		glm::uint8(255), glm::uint8(0));

	Error += test_texture(
		gli::texture2D(gli::FORMAT_RGB8_UNORM, TextureSize, Levels),
		glm::u8vec3(255, 128, 0), glm::u8vec3(0, 128, 255));

	Error += test_texture(
		gli::texture2D(gli::FORMAT_RGBA8_UNORM, TextureSize, Levels),
		glm::u8vec4(255, 128, 0, 255), glm::u8vec4(0, 128, 255, 255));

	Error += test_texture(
		gli::texture2D(gli::FORMAT_RGBA32_SFLOAT, TextureSize, Levels),
		glm::f32vec4(1.0, 0.5, 0.0, 1.0), glm::f32vec4(0.0, 0.5, 1.0, 1.0));

	Error += test_texture(
		gli::texture2D(gli::FORMAT_RGB_DXT1_UNORM, TextureSize, Levels),
		dxt1_block{63712u, 255u, 228u, 144u, 64u, 0u}, dxt1_block{2516u, 215u, 152u, 173u, 215u, 106u});
		
	Error += test_texture(
		gli::texture2D(gli::FORMAT_RGBA_DXT3_UNORM, TextureSize, Levels),
		dxt3_block{12514u, 1512u, 12624u, 16614u, 63712u, 255u, 228u, 144u, 64u, 0u}, dxt3_block{36125u, 2416u, 46314u, 10515u, 2516u, 215u, 152u, 173u, 215u, 106u});
		
	Error += test_texture(
		gli::texture2D(gli::FORMAT_RGBA_DXT5_UNORM, TextureSize, Levels),
		dxt5_block{255u, 0u, 16414u, 12845u, 62020u, 63712u, 255u, 228u, 144u, 64u, 0u}, dxt5_block{0u, 255u, 16016u, 58582u, 15304u, 2516u, 215u, 152u, 173u, 215u, 106u});
		
	Error += test_texture(
		gli::texture2DArray(gli::FORMAT_RGBA8_UNORM, TextureSize, 4, Levels),
		glm::u8vec4(255, 128, 0, 255), glm::u8vec4(0, 128, 255, 255));

	Error += test_texture(
		gli::texture2DArray(gli::FORMAT_RGBA32_SFLOAT, TextureSize, 4, Levels),
		glm::f32vec4(1.0, 0.5, 0.0, 1.0), glm::f32vec4(0.0, 0.5, 1.0, 1.0));
		
	Error += test_texture(
		gli::textureCube(gli::FORMAT_RGBA8_UNORM, TextureSize, Levels),
		glm::u8vec4(255, 128, 0, 255), glm::u8vec4(0, 128, 255, 255));

	Error += test_texture(
		gli::textureCube(gli::FORMAT_RGBA32_SFLOAT, TextureSize, Levels),
		glm::f32vec4(1.0, 0.5, 0.0, 1.0), glm::f32vec4(0.0, 0.5, 1.0, 1.0));
		
	Error += test_texture(
		gli::textureCubeArray(gli::FORMAT_RGBA8_UNORM, TextureSize, 4, Levels),
		glm::u8vec4(255, 128, 0, 255), glm::u8vec4(0, 128, 255, 255));

	Error += test_texture(
		gli::textureCubeArray(gli::FORMAT_RGBA32_SFLOAT, TextureSize, 4, Levels),
		glm::f32vec4(1.0, 0.5, 0.0, 1.0), glm::f32vec4(0.0, 0.5, 1.0, 1.0));

	return Error;
}
