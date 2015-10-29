///////////////////////////////////////////////////////////////////////////////////
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
/// @file gli/core/format.inl
/// @date 2012-10-16 / 2015-06-16
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace gli{
namespace detail
{
	enum
	{
		CAP_COMPRESSED_BIT = (1 << 0),
		CAP_PACKED_BIT = (1 << 1),
		CAP_NORMALIZED_BIT = (1 << 2),
		CAP_SCALED_BIT = (1 << 3),
		CAP_UNSIGNED_BIT = (1 << 4),
		CAP_SIGNED_BIT = (1 << 5),
		CAP_INTEGER_BIT = (1 << 6),
		CAP_FLOAT_BIT = (1 << 7),
		CAP_DEPTH_BIT = (1 << 8),
		CAP_STENCIL_BIT = (1 << 9),
		CAP_COLORSPACE_SRGB_BIT = (1 << 10),
		CAP_SWIZZLE_BIT = (1 << 11),
		CAP_LUMINANCE_ALPHA_BIT = (1 << 12)
	};

	struct formatInfo
	{
		std::uint8_t BlockSize;
		glm::u8vec3 BlockDimensions;
		std::uint8_t Component;
		swizzles Swizzles;
		std::uint16_t Flags;
	};

	inline formatInfo const & get_format_info(format Format)
	{
		assert(Format >= FORMAT_FIRST && Format <= FORMAT_LAST);

		static formatInfo const Table[] =
		{
			{  1, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_PACKED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},				//FORMAT_R4G4_UNORM,
			{  1, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_PACKED_BIT | CAP_SCALED_BIT | CAP_UNSIGNED_BIT},					//FORMAT_R4G4_USCALED,
			{  2, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_PACKED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},				//FORMAT_R4G4B4A4_UNORM,
			{  2, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_PACKED_BIT | CAP_SCALED_BIT | CAP_UNSIGNED_BIT},					//FORMAT_R4G4B4A4_USCALED,
			{  2, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_PACKED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},				//FORMAT_R5G6B5_UNORM,
			{  2, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_PACKED_BIT | CAP_SCALED_BIT | CAP_UNSIGNED_BIT},					//FORMAT_R5G6B5_USCALED,
			{  2, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_PACKED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},				//FORMAT_R5G5B5A1_UNORM,
			{  2, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_PACKED_BIT | CAP_SCALED_BIT | CAP_UNSIGNED_BIT},					//FORMAT_R5G5B5A1_USCALED,

			{  1, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_R8_UNORM,
			{  1, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_NORMALIZED_BIT | CAP_SIGNED_BIT},									//FORMAT_R8_SNORM,
			{  1, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_SCALED_BIT | CAP_UNSIGNED_BIT},										//FORMAT_R8_USCALED,
			{  1, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_SCALED_BIT | CAP_SIGNED_BIT},										//FORMAT_R8_SSCALED,
			{  1, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_INTEGER_BIT | CAP_UNSIGNED_BIT},										//FORMAT_R8_UINT,
			{  1, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_INTEGER_BIT | CAP_SIGNED_BIT},										//FORMAT_R8_SINT,
			{  1, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT | CAP_COLORSPACE_SRGB_BIT},		//FORMAT_R8_SRGB,

			{  2, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RG8_UNORM,
			{  2, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_NORMALIZED_BIT | CAP_SIGNED_BIT},									//FORMAT_RG8_SNORM,
			{  2, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_SCALED_BIT | CAP_UNSIGNED_BIT},										//FORMAT_RG8_USCALED,
			{  2, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_SCALED_BIT | CAP_SIGNED_BIT},										//FORMAT_RG8_SSCALED,
			{  2, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_INTEGER_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RG8_UINT,
			{  2, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_INTEGER_BIT | CAP_SIGNED_BIT},										//FORMAT_RG8_SINT,
			{  2, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_NORMALIZED_BIT | CAP_SIGNED_BIT | CAP_COLORSPACE_SRGB_BIT},			//FORMAT_RG8_SRGB,

			{  3, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RGB8_UNORM,
			{  3, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_NORMALIZED_BIT | CAP_SIGNED_BIT},									//FORMAT_RGB8_SNORM,
			{  3, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_SCALED_BIT | CAP_UNSIGNED_BIT},										//FORMAT_RGB8_USCALED,
			{  3, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_SCALED_BIT | CAP_SIGNED_BIT},										//FORMAT_RGB8_SSCALED,
			{  3, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_INTEGER_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RGB8_UINT,
			{  3, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_INTEGER_BIT | CAP_SIGNED_BIT},										//FORMAT_RGB8_SINT,
			{  3, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT | CAP_COLORSPACE_SRGB_BIT},		//FORMAT_RGB8_SRGB,

			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},								//FORMAT_RGBA8_UNORM,
			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_NORMALIZED_BIT | CAP_SIGNED_BIT},									//FORMAT_RGBA8_SNORM,
			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_SCALED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RGBA8_USCALED,
			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_SCALED_BIT | CAP_SIGNED_BIT},										//FORMAT_RGBA8_SSCALED,
			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_INTEGER_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RGBA8_UINT,
			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_INTEGER_BIT | CAP_SIGNED_BIT},									//FORMAT_RGBA8_SINT,
			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT | CAP_COLORSPACE_SRGB_BIT},		//FORMAT_RGBA8_SRGB,

			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT | CAP_PACKED_BIT},				//FORMAT_RGB10A2_UNORM,
			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_NORMALIZED_BIT | CAP_SIGNED_BIT | CAP_PACKED_BIT},				//FORMAT_RGB10A2_SNORM,
			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_SCALED_BIT | CAP_UNSIGNED_BIT | CAP_PACKED_BIT},					//FORMAT_RGB10A2_USCALE,
			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_SCALED_BIT | CAP_SIGNED_BIT | CAP_PACKED_BIT},					//FORMAT_RGB10A2_SSCALE,
			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_INTEGER_BIT | CAP_UNSIGNED_BIT | CAP_PACKED_BIT},					//FORMAT_RGB10A2_UINT,
			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_INTEGER_BIT | CAP_SIGNED_BIT | CAP_PACKED_BIT},					//FORMAT_RGB10A2_SINT,

			{  2, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_R16_UNORM,
			{  2, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_NORMALIZED_BIT | CAP_SIGNED_BIT},									//FORMAT_R16_SNORM,
			{  2, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_SCALED_BIT | CAP_UNSIGNED_BIT},										//FORMAT_R16_USCALE,
			{  2, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_SCALED_BIT | CAP_SIGNED_BIT},										//FORMAT_R16_SSCALE,
			{  2, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_INTEGER_BIT | CAP_UNSIGNED_BIT},										//FORMAT_R16_UINT,
			{  2, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_INTEGER_BIT | CAP_SIGNED_BIT},										//FORMAT_R16_SINT,
			{  2, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_FLOAT_BIT | CAP_SIGNED_BIT},											//FORMAT_R16_SFLOAT,

			{  4, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RG16_UNORM,
			{  4, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_NORMALIZED_BIT | CAP_SIGNED_BIT},									//FORMAT_RG16_SNORM,
			{  4, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_SCALED_BIT | CAP_UNSIGNED_BIT},										//FORMAT_RG16_USCALE,
			{  4, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_SCALED_BIT | CAP_SIGNED_BIT},										//FORMAT_RG16_SSCALE,
			{  4, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_INTEGER_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RG16_UINT,
			{  4, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_INTEGER_BIT | CAP_SIGNED_BIT},										//FORMAT_RG16_SINT,
			{  4, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_FLOAT_BIT | CAP_SIGNED_BIT},										//FORMAT_RG16_SFLOAT,

			{  6, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGB16_UNORM,
			{  6, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_NORMALIZED_BIT | CAP_SIGNED_BIT},		//FORMAT_RGB16_SNORM,
			{  6, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_SCALED_BIT | CAP_UNSIGNED_BIT},			//FORMAT_RGB16_USCALE,
			{  6, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_SCALED_BIT | CAP_SIGNED_BIT},			//FORMAT_RGB16_SSCALE,
			{  6, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_INTEGER_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGB16_UINT,
			{  6, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_INTEGER_BIT | CAP_SIGNED_BIT},			//FORMAT_RGB16_SINT,
			{  6, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_FLOAT_BIT | CAP_SIGNED_BIT},			//FORMAT_RGB16_SFLOAT,

			{  8, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},	//FORMAT_RGBA16_UNORM,
			{  8, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_NORMALIZED_BIT | CAP_SIGNED_BIT},		//FORMAT_RGBA16_SNORM,
			{  8, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_SCALED_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGBA16_USCALE,
			{  8, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_SCALED_BIT | CAP_SIGNED_BIT},			//FORMAT_RGBA16_SSCALE,
			{  8, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_INTEGER_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGBA16_UINT,
			{  8, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_INTEGER_BIT | CAP_SIGNED_BIT},		//FORMAT_RGBA16_SINT,
			{  8, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_FLOAT_BIT | CAP_SIGNED_BIT},			//FORMAT_RGBA16_SFLOAT,

			{  4, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_INTEGER_BIT | CAP_UNSIGNED_BIT},			//FORMAT_R32_UINT,
			{  4, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_INTEGER_BIT | CAP_SIGNED_BIT},			//FORMAT_R32_SINT,
			{  4, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_FLOAT_BIT | CAP_SIGNED_BIT},				//FORMAT_R32_SFLOAT,

			{  8, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_INTEGER_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RG32_UINT,
			{  8, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_INTEGER_BIT | CAP_SIGNED_BIT},			//FORMAT_RG32_SINT,
			{  8, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_FLOAT_BIT | CAP_SIGNED_BIT},			//FORMAT_RG32_SFLOAT,

			{ 12, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_INTEGER_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGB32_UINT,
			{ 12, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_INTEGER_BIT | CAP_SIGNED_BIT},			//FORMAT_RGB32_SINT,
			{ 12, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_FLOAT_BIT | CAP_SIGNED_BIT},			//FORMAT_RGB32_SFLOAT,

			{ 16, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_INTEGER_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGBA32_UINT,
			{ 16, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_INTEGER_BIT | CAP_SIGNED_BIT},		//FORMAT_RGBA32_SINT,
			{ 16, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_FLOAT_BIT | CAP_SIGNED_BIT},			//FORMAT_RGBA32_SFLOAT,

			{  8, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_FLOAT_BIT | CAP_SIGNED_BIT},				//FORMAT_R64_SFLOAT,
			{ 16, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_FLOAT_BIT | CAP_SIGNED_BIT},			//FORMAT_RG64_SFLOAT,
			{ 24, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_FLOAT_BIT | CAP_SIGNED_BIT},			//FORMAT_RGB64_SFLOAT,
			{ 32, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_FLOAT_BIT | CAP_SIGNED_BIT},			//FORMAT_RGBA64_SFLOAT,

			{  4, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_PACKED_BIT | CAP_FLOAT_BIT | CAP_SIGNED_BIT},		//FORMAT_RG11B10_UFLOAT,
			{  4, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_PACKED_BIT | CAP_FLOAT_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGB9E5_UFLOAT,

			{  2, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_DEPTH_BIT | CAP_INTEGER_BIT},						//FORMAT_D16_UNORM,
			{  3, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_DEPTH_BIT | CAP_INTEGER_BIT},						//FORMAT_D24_UNORM,
			{  4, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_DEPTH_BIT | CAP_FLOAT_BIT},						//FORMAT_D32_UFLOAT,
			{  1, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_DEPTH_BIT | CAP_STENCIL_BIT},						//FORMAT_S8_UNORM,
			{  3, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_DEPTH_BIT | CAP_INTEGER_BIT | CAP_STENCIL_BIT},	//FORMAT_D16_UNORM_S8_UINT,
			{  4, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_DEPTH_BIT | CAP_INTEGER_BIT | CAP_STENCIL_BIT},	//FORMAT_D24_UNORM_S8_UINT,
			{  5, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_DEPTH_BIT | CAP_FLOAT_BIT | CAP_STENCIL_BIT},		//FORMAT_D32_SFLOAT_S8_UINT,

			{  8, glm::u8vec3(4, 4, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RGBA_DXT1_UNORM,
			{  8, glm::u8vec3(4, 4, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGBA_DXT1_SRGB,
			{ 16, glm::u8vec3(4, 4, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RGBA_DXT3_UNORM,
			{ 16, glm::u8vec3(4, 4, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGBA_DXT3_SRGB,
			{ 16, glm::u8vec3(4, 4, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RGBA_DXT5_UNORM,
			{ 16, glm::u8vec3(4, 4, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGBA_DXT5_SRGB,
			{  8, glm::u8vec3(4, 4, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},										//FORMAT_R_ATI1N_UNORM,
			{  8, glm::u8vec3(4, 4, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_SIGNED_BIT},										//FORMAT_R_ATI1N_SNORM,
			{ 16, glm::u8vec3(4, 4, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},										//FORMAT_RG_ATI2N_UNORM,
			{ 16, glm::u8vec3(4, 4, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_SIGNED_BIT},										//FORMAT_RG_ATI2N_SNORM,
			{ 16, glm::u8vec3(4, 4, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_COMPRESSED_BIT | CAP_FLOAT_BIT | CAP_UNSIGNED_BIT},											//FORMAT_RGB_BP_UFLOAT,
			{ 16, glm::u8vec3(4, 4, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_COMPRESSED_BIT | CAP_FLOAT_BIT | CAP_SIGNED_BIT},											//FORMAT_RGB_BP_SFLOAT,
			{ 16, glm::u8vec3(4, 4, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RGB_BP_UNORM,
			{ 16, glm::u8vec3(4, 4, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},			//FORMAT_RGB_BP_SRGB,

			{  8, glm::u8vec3(4, 4, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RGB_ETC2_UNORM,
			{  8, glm::u8vec3(4, 4, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGB_ETC2_SRGB,
			{  8, glm::u8vec3(4, 4, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RGBA_ETC2_PUNCHTHROUGH_UNORM,
			{  8, glm::u8vec3(4, 4, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGBA_ETC2_PUNCHTHROUGH_SRGB,
			{ 16, glm::u8vec3(4, 4, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RGBA_ETC2_UNORM,
			{ 16, glm::u8vec3(4, 4, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGBA_ETC2_SRGB,
			{  8, glm::u8vec3(4, 4, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_R11_EAC_UNORM,
			{  8, glm::u8vec3(4, 4, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_SIGNED_BIT},									//FORMAT_R11_EAC_SNORM,
			{ 16, glm::u8vec3(4, 4, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RG11_EAC_UNORM,
			{ 16, glm::u8vec3(4, 4, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_SIGNED_BIT},									//FORMAT_RG11_EAC_SNORM,

			{ 16, glm::u8vec3(4, 4, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RGBA_ASTC4X4_UNORM,
			{ 16, glm::u8vec3(4, 4, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGBA_ASTC4X4_SRGB,
			{ 16, glm::u8vec3(5, 4, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RGBA_ASTC5X4_UNORM,
			{ 16, glm::u8vec3(5, 4, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGBA_ASTC5X4_SRGB,
			{ 16, glm::u8vec3(5, 5, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RGBA_ASTC5X5_UNORM,
			{ 16, glm::u8vec3(5, 5, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGBA_ASTC5X5_SRGB,
			{ 16, glm::u8vec3(6, 5, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RGBA_ASTC6X5_UNORM,
			{ 16, glm::u8vec3(6, 5, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGBA_ASTC6X5_SRGB,
			{ 16, glm::u8vec3(6, 6, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RGBA_ASTC6X6_UNORM,
			{ 16, glm::u8vec3(6, 6, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGBA_ASTC6X6_SRGB,
			{ 16, glm::u8vec3(8, 5, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RGBA_ASTC8X5_UNORM,
			{ 16, glm::u8vec3(8, 5, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGBA_ASTC8X5_SRGB,
			{ 16, glm::u8vec3(8, 6, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RGBA_ASTC8X6_UNORM,
			{ 16, glm::u8vec3(8, 6, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGBA_ASTC8X6_SRGB,
			{ 16, glm::u8vec3(8, 8, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RGBA_ASTC8X8_UNORM,
			{ 16, glm::u8vec3(8, 8, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGBA_ASTC8X8_SRGB,
			{ 16, glm::u8vec3(10, 5, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RGBA_ASTC10X5_UNORM,
			{ 16, glm::u8vec3(10, 5, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGBA_ASTC10X5_SRGB,
			{ 16, glm::u8vec3(10, 6, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RGBA_ASTC10X6_UNORM,
			{ 16, glm::u8vec3(10, 6, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGBA_ASTC10X6_SRGB,
			{ 16, glm::u8vec3(10, 8, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RGBA_ASTC10X8_UNORM,
			{ 16, glm::u8vec3(10, 8, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGBA_ASTC10X8_SRGB,
			{ 16, glm::u8vec3(10, 10, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},								//FORMAT_RGBA_ASTC10X10_UNORM,
			{ 16, glm::u8vec3(10, 10, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGBA_ASTC10X10_SRGB,
			{ 16, glm::u8vec3(12, 10, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},								//FORMAT_RGBA_ASTC12X10_UNORM,
			{ 16, glm::u8vec3(12, 10, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGBA_ASTC12X10_SRGB,
			{ 16, glm::u8vec3(12, 12, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},								//FORMAT_RGBA_ASTC12X12_UNORM,
			{ 16, glm::u8vec3(12, 12, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGBA_ASTC12X12_SRGB,

			{  2, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ALPHA), CAP_PACKED_BIT| CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT | CAP_SWIZZLE_BIT},					//FORMAT_BGRA4_UNORM,
			{  2, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ALPHA), CAP_PACKED_BIT| CAP_SCALED_BIT | CAP_UNSIGNED_BIT | CAP_SWIZZLE_BIT},						//FORMAT_BGRA4_USCALED,
			{  2, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ONE), CAP_PACKED_BIT| CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT | CAP_SWIZZLE_BIT},					//FORMAT_B5G6R5_UNORM,
			{  2, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ONE), CAP_PACKED_BIT| CAP_SCALED_BIT | CAP_UNSIGNED_BIT | CAP_SWIZZLE_BIT},						//FORMAT_B5G6R5_USCALED,
			{  2, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ALPHA), CAP_PACKED_BIT| CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT | CAP_SWIZZLE_BIT},					//FORMAT_BGR5A1_UNORM,
			{  2, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ALPHA), CAP_PACKED_BIT| CAP_SCALED_BIT | CAP_UNSIGNED_BIT | CAP_SWIZZLE_BIT},						//FORMAT_BGRA1_USCALED,

			{  3, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ONE), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT | CAP_SWIZZLE_BIT},									//FORMAT_BGR8_UNORM,
			{  3, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ONE), CAP_NORMALIZED_BIT | CAP_SIGNED_BIT | CAP_SWIZZLE_BIT},										//FORMAT_BGR8_SNORM,
			{  3, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ONE), CAP_SCALED_BIT | CAP_UNSIGNED_BIT | CAP_SWIZZLE_BIT},										//FORMAT_BGR8_USCALED,
			{  3, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ONE), CAP_SCALED_BIT | CAP_SIGNED_BIT | CAP_SWIZZLE_BIT},											//FORMAT_BGR8_SSCALED,
			{  3, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ONE), CAP_INTEGER_BIT | CAP_UNSIGNED_BIT | CAP_SWIZZLE_BIT},										//FORMAT_BGR8_UINT,
			{  3, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ONE), CAP_INTEGER_BIT | CAP_SIGNED_BIT | CAP_SWIZZLE_BIT},										//FORMAT_BGR8_SINT,
			{  3, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ONE), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_SWIZZLE_BIT},			//FORMAT_BGR8_SRGB,

			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ALPHA), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT | CAP_SWIZZLE_BIT},									//FORMAT_BGRA8_UNORM,
			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ALPHA), CAP_NORMALIZED_BIT | CAP_SIGNED_BIT | CAP_SWIZZLE_BIT},									//FORMAT_BGRA8_SNORM,
			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ALPHA), CAP_SCALED_BIT | CAP_UNSIGNED_BIT | CAP_SWIZZLE_BIT},										//FORMAT_BGRA8_USCALED,
			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ALPHA), CAP_SCALED_BIT | CAP_SIGNED_BIT | CAP_SWIZZLE_BIT},										//FORMAT_BGRA8_SSCALED,
			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ALPHA), CAP_INTEGER_BIT | CAP_UNSIGNED_BIT | CAP_SWIZZLE_BIT},									//FORMAT_BGRA8_UINT,
			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ALPHA), CAP_INTEGER_BIT | CAP_SIGNED_BIT | CAP_SWIZZLE_BIT},										//FORMAT_BGRA8_SINT,
			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ALPHA), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_SWIZZLE_BIT},		//FORMAT_BGRA8_SRGB,

			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ALPHA), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT | CAP_PACKED_BIT | CAP_SWIZZLE_BIT},				//FORMAT_BGR10A2_UNORM,
			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ALPHA), CAP_NORMALIZED_BIT | CAP_SIGNED_BIT | CAP_PACKED_BIT | CAP_SWIZZLE_BIT},					//FORMAT_BGR10A2_SNORM,
			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ALPHA), CAP_SCALED_BIT | CAP_UNSIGNED_BIT | CAP_PACKED_BIT | CAP_SWIZZLE_BIT},					//FORMAT_BGR10A2_USCALE,
			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ALPHA), CAP_SCALED_BIT | CAP_SIGNED_BIT | CAP_PACKED_BIT | CAP_SWIZZLE_BIT},						//FORMAT_BGR10A2_SSCALE,
			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ALPHA), CAP_INTEGER_BIT | CAP_UNSIGNED_BIT | CAP_PACKED_BIT | CAP_SWIZZLE_BIT},					//FORMAT_BGR10A2_UINT,
			{  4, glm::u8vec3(1, 1, 1), 4, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ALPHA), CAP_INTEGER_BIT | CAP_SIGNED_BIT | CAP_PACKED_BIT | CAP_SWIZZLE_BIT},						//FORMAT_BGR10A2_SINT,

			{  1, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_PACKED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},									//FORMAT_RG3B2_UNORM,
			{  4, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ONE), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT | CAP_SWIZZLE_BIT},									//FORMAT_BGRX8_UNORM,
			{  4, glm::u8vec3(1, 1, 1), 3, swizzles(SWIZZLE_BLUE, SWIZZLE_GREEN, SWIZZLE_RED, SWIZZLE_ONE), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT | CAP_SWIZZLE_BIT | CAP_COLORSPACE_SRGB_BIT},			//FORMAT_BGRX8_SRGB,

			{  1, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT | CAP_LUMINANCE_ALPHA_BIT},							//FORMAT_L8_UNORM,
			{  1, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_RED), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT | CAP_LUMINANCE_ALPHA_BIT},							//FORMAT_A8_UNORM,
			{  2, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_GREEN), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT | CAP_LUMINANCE_ALPHA_BIT},							//FORMAT_LA8_UNORM,
			{  2, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ONE), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT | CAP_LUMINANCE_ALPHA_BIT},							//FORMAT_L16_UNORM,
			{  2, glm::u8vec3(1, 1, 1), 1, swizzles(SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_RED), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT | CAP_LUMINANCE_ALPHA_BIT},							//FORMAT_A16_UNORM,
			{  4, glm::u8vec3(1, 1, 1), 2, swizzles(SWIZZLE_RED, SWIZZLE_ZERO, SWIZZLE_ZERO, SWIZZLE_GREEN), CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT | CAP_LUMINANCE_ALPHA_BIT},							//FORMAT_LA16_UNORM,

			{ 32, glm::u8vec3(8, 8, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},								//FORMAT_RGB_PVRTC1_8X8_UNORM,
			{ 32, glm::u8vec3(8, 8, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGB_PVRTC1_8X8_SRGB,
			{ 32, glm::u8vec3(16, 8, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},								//FORMAT_RGB_PVRTC1_16X8_UNORM,
			{ 32, glm::u8vec3(16, 8, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},		//FORMAT_RGB_PVRTC1_16X8_SRGB,
			{ 32, glm::u8vec3(8, 8, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},								//FORMAT_RGBA_PVRTC1_8X8_UNORM,
			{ 32, glm::u8vec3(8, 8, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},	//FORMAT_RGBA_PVRTC1_8X8_SRGB,
			{ 32, glm::u8vec3(16, 8, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},								//FORMAT_RGBA_PVRTC1_16X8_UNORM,
			{ 32, glm::u8vec3(16, 8, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},	//FORMAT_RGBA_PVRTC1_16X8_SRGB,
			{  8, glm::u8vec3(4, 4, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},								//FORMAT_RGBA_PVRTC2_4X4_UNORM,
			{  8, glm::u8vec3(4, 4, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},	//FORMAT_RGBA_PVRTC2_4X4_SRGB,
			{  8, glm::u8vec3(8, 4, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},								//FORMAT_RGBA_PVRTC2_8X4_UNORM,
			{  8, glm::u8vec3(8, 4, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_COLORSPACE_SRGB_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},	//FORMAT_RGBA_PVRTC2_8X4_SRGB,

			{  8, glm::u8vec3(4, 4, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},								//FORMAT_RGB_ETC_UNORM,
			{  8, glm::u8vec3(4, 4, 1), 3, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ONE), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},								//FORMAT_RGB_ATC_UNORM,
			{ 16, glm::u8vec3(4, 4, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},								//FORMAT_RGBA_ATC_EXPLICIT_UNORM,
			{ 16, glm::u8vec3(4, 4, 1), 4, swizzles(SWIZZLE_RED, SWIZZLE_GREEN, SWIZZLE_BLUE, SWIZZLE_ALPHA), CAP_COMPRESSED_BIT | CAP_NORMALIZED_BIT | CAP_UNSIGNED_BIT},								//FORMAT_RGBA_ATC_INTERPOLATED_UNORM,
		};

		GLM_STATIC_ASSERT(sizeof(Table) / sizeof(Table[0]) == FORMAT_COUNT, "GLI error: format descriptor list doesn't match number of supported formats");
		assert(Format != static_cast<format>(FORMAT_INVALID));

		return Table[Format - FORMAT_FIRST];
	};

	inline std::uint32_t bits_per_pixel(format Format)
	{
		detail::formatInfo const & Info = detail::get_format_info(Format);

		return Info.BlockSize * 8 / (Info.BlockDimensions.x * Info.BlockDimensions.y * Info.BlockDimensions.z);
	}
}//namespace detail

	inline bool is_compressed(format Format)
	{
		return detail::get_format_info(Format).Flags & detail::CAP_COMPRESSED_BIT ? true : false;
	}

	inline bool is_srgb(format Format)
	{
		return detail::get_format_info(Format).Flags & detail::CAP_COLORSPACE_SRGB_BIT ? true : false;
	}

	inline size_t block_size(format Format)
	{
		return detail::get_format_info(Format).BlockSize;
	}

	inline ivec3 block_dimensions(format Format)
	{
		return gli::ivec3(detail::get_format_info(Format).BlockDimensions);
	}

	inline size_t component_count(format Format)
	{
		return detail::get_format_info(Format).Component;
	}
}//namespace gli
