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
/// @file gli/core/gl.inl
/// @date 2013-11-09 / 2013-11-09
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#include <algorithm>

namespace gli
{
	inline gl::gl()
	{
		static format const Table[] =
		{
			{INTERNAL_RG4_EXT, EXTERNAL_RGBA, TYPE_UINT8_RG4_EXT},			//FORMAT_R4G4_UNORM,
			{INTERNAL_RG4_EXT, EXTERNAL_RGBA, TYPE_UINT8_RG4_EXT},			//FORMAT_R4G4_USCALED,
			{INTERNAL_RGBA4, EXTERNAL_RGBA, TYPE_UINT16_RGBA4},				//FORMAT_R4G4B4A4_UNORM,
			{INTERNAL_RGBA4, EXTERNAL_RGBA, TYPE_UINT16_RGBA4},				//FORMAT_R4G4B4A4_USCALED,
			{INTERNAL_R5G6B5, EXTERNAL_RGB, TYPE_UINT16_R5G6B5},			//FORMAT_R5G6B5_UNORM,
			{INTERNAL_R5G6B5, EXTERNAL_RGB, TYPE_UINT16_R5G6B5},			//FORMAT_R5G6B5_USCALED,
			{INTERNAL_RGB5A1, EXTERNAL_RGBA, TYPE_UINT16_RGB5A1},			//FORMAT_R5G5B5A1_UNORM,
			{INTERNAL_RGB5A1, EXTERNAL_RGBA, TYPE_UINT16_RGB5A1},			//FORMAT_R5G5B5A1_USCALED,

			{INTERNAL_R8_UNORM, EXTERNAL_RED, TYPE_U8},						//FORMAT_R8_UNORM,
			{INTERNAL_R8_SNORM, EXTERNAL_RED, TYPE_I8},						//FORMAT_R8_SNORM,
			{INTERNAL_R8_UNORM, EXTERNAL_RED, TYPE_U8},						//FORMAT_R8_USCALED,
			{INTERNAL_R8_SNORM, EXTERNAL_RED, TYPE_I8},						//FORMAT_R8_SSCALED,
			{INTERNAL_R8U, EXTERNAL_RED_INTEGER, TYPE_U8},					//FORMAT_R8_UINT,
			{INTERNAL_R8I, EXTERNAL_RED_INTEGER, TYPE_I8},					//FORMAT_R8_SINT,
			{INTERNAL_SR8, EXTERNAL_RED, TYPE_U8},							//FORMAT_R8_SRGB,

			{INTERNAL_RG8_UNORM, EXTERNAL_RG, TYPE_U8},						//FORMAT_RG8_UNORM,
			{INTERNAL_RG8_SNORM, EXTERNAL_RG, TYPE_I8},						//FORMAT_RG8_SNORM,
			{INTERNAL_RG8_UNORM, EXTERNAL_RG, TYPE_U8},						//FORMAT_RG8_USCALED,
			{INTERNAL_RG8_SNORM, EXTERNAL_RG, TYPE_I8},						//FORMAT_RG8_SSCALED,
			{INTERNAL_RG8U, EXTERNAL_RG_INTEGER, TYPE_U8},					//FORMAT_RG8_UINT,
			{INTERNAL_RG8I, EXTERNAL_RG_INTEGER, TYPE_I8},					//FORMAT_RG8_SINT,
			{INTERNAL_SRG8, EXTERNAL_RG, TYPE_U8},							//FORMAT_RG8_SRGB,

			{INTERNAL_RGB8_UNORM, EXTERNAL_RGB, TYPE_U8},					//FORMAT_RGB8_UNORM,
			{INTERNAL_RGB8_SNORM, EXTERNAL_RGB, TYPE_I8},					//FORMAT_RGB8_SNORM,
			{INTERNAL_RGB8_UNORM, EXTERNAL_RGB, TYPE_U8},					//FORMAT_RGB8_USCALED,
			{INTERNAL_RGB8_SNORM, EXTERNAL_RGB, TYPE_I8},					//FORMAT_RGB8_SSCALED,
			{INTERNAL_RGB8U, EXTERNAL_RGB_INTEGER, TYPE_U8},				//FORMAT_RGB8_UINT,
			{INTERNAL_RGB8I, EXTERNAL_RGB_INTEGER, TYPE_I8},				//FORMAT_RGB8_SINT,
			{INTERNAL_SRGB8, EXTERNAL_RGB, TYPE_U8},						//FORMAT_RGB8_SRGB,

			{INTERNAL_RGBA8_UNORM, EXTERNAL_RGBA, TYPE_U8},					//FORMAT_RGBA8_UNORM,
			{INTERNAL_RGBA8_SNORM, EXTERNAL_RGBA, TYPE_I8},					//FORMAT_RGBA8_SNORM,
			{INTERNAL_RGBA8_UNORM, EXTERNAL_RGBA, TYPE_U8},					//FORMAT_RGBA8_USCALED,
			{INTERNAL_RGBA8_SNORM, EXTERNAL_RGBA, TYPE_I8},					//FORMAT_RGBA8_SSCALED,
			{INTERNAL_RGBA8U, EXTERNAL_RGBA_INTEGER, TYPE_U8},				//FORMAT_RGBA8_UINT,
			{INTERNAL_RGBA8I, EXTERNAL_RGBA_INTEGER, TYPE_I8},				//FORMAT_RGBA8_SINT,
			{INTERNAL_SRGB8_ALPHA8, EXTERNAL_RGBA, TYPE_U8},				//FORMAT_RGBA8_SRGB,

			{INTERNAL_RGB10A2_UNORM, EXTERNAL_RGBA, TYPE_UINT32_RGB10A2},			//FORMAT_RGB10A2_UNORM,
			{INTERNAL_RGB10A2_SNORM_EXT, EXTERNAL_RGBA, TYPE_UINT32_RGB10A2},		//FORMAT_RGB10A2_SNORM,
			{INTERNAL_RGB10A2_UNORM, EXTERNAL_RGBA, TYPE_UINT32_RGB10A2},			//FORMAT_RGB10A2_USCALE,
			{INTERNAL_RGB10A2_SNORM_EXT, EXTERNAL_RGBA, TYPE_UINT32_RGB10A2},		//FORMAT_RGB10A2_SSCALE,
			{INTERNAL_RGB10A2U, EXTERNAL_RGBA_INTEGER, TYPE_UINT32_RGB10A2},		//FORMAT_RGB10A2_UINT,
			{INTERNAL_RGB10A2I_EXT, EXTERNAL_RGBA_INTEGER, TYPE_UINT32_RGB10A2},	//FORMAT_RGB10A2_SINT,

			{INTERNAL_R16_UNORM, EXTERNAL_RED, TYPE_U16},					//FORMAT_R16_UNORM,
			{INTERNAL_R16_SNORM, EXTERNAL_RED, TYPE_I16},					//FORMAT_R16_SNORM,
			{INTERNAL_R16_UNORM, EXTERNAL_RED, TYPE_U16},					//FORMAT_R16_UNORM,
			{INTERNAL_R16_SNORM, EXTERNAL_RED, TYPE_I16},					//FORMAT_R16_SNORM,
			{INTERNAL_R16U, EXTERNAL_RED_INTEGER, TYPE_U16},				//FORMAT_R16_UINT,
			{INTERNAL_R16I, EXTERNAL_RED_INTEGER, TYPE_I16},				//FORMAT_R16_SINT,
			{INTERNAL_R16F, EXTERNAL_RED, TYPE_F16},						//FORMAT_R16_SFLOAT,

			{INTERNAL_RG16_UNORM, EXTERNAL_RG, TYPE_U16},					//FORMAT_RG16_UNORM,
			{INTERNAL_RG16_SNORM, EXTERNAL_RG, TYPE_I16},					//FORMAT_RG16_SNORM,
			{INTERNAL_RG16_UNORM, EXTERNAL_RG, TYPE_U16},					//FORMAT_RG16_USCALE,
			{INTERNAL_RG16_SNORM, EXTERNAL_RG, TYPE_I16},					//FORMAT_RG16_SSCALE,
			{INTERNAL_RG16U, EXTERNAL_RG_INTEGER, TYPE_U16},				//FORMAT_RG16_UINT,
			{INTERNAL_RG16I, EXTERNAL_RG_INTEGER, TYPE_I16},				//FORMAT_RG16_SINT,
			{INTERNAL_RG16F, EXTERNAL_RG, TYPE_F16},						//FORMAT_RG16_SFLOAT,

			{INTERNAL_RGB16_UNORM, EXTERNAL_RGB, TYPE_U16},					//FORMAT_RGB16_UNORM,
			{INTERNAL_RGB16_SNORM, EXTERNAL_RGB, TYPE_I16},					//FORMAT_RGB16_SNORM,
			{INTERNAL_RGB16_UNORM, EXTERNAL_RGB, TYPE_U16},					//FORMAT_RGB16_USCALE,
			{INTERNAL_RGB16_SNORM, EXTERNAL_RGB, TYPE_I16},					//FORMAT_RGB16_USCALE,
			{INTERNAL_RGB16U, EXTERNAL_RGB_INTEGER, TYPE_U16},				//FORMAT_RGB16_UINT,
			{INTERNAL_RGB16I, EXTERNAL_RGB_INTEGER, TYPE_I16},				//FORMAT_RGB16_SINT,
			{INTERNAL_RGB16F, EXTERNAL_RGB, TYPE_F16},						//FORMAT_RGB16_SFLOAT,

			{INTERNAL_RGBA16_UNORM, EXTERNAL_RGBA, TYPE_U16},				//FORMAT_RGBA16_UNORM,
			{INTERNAL_RGBA16_SNORM, EXTERNAL_RGBA, TYPE_I16},				//FORMAT_RGBA16_SNORM,
			{INTERNAL_RGBA16_UNORM, EXTERNAL_RGBA, TYPE_U16},				//FORMAT_RGBA16_USCALE,
			{INTERNAL_RGBA16_SNORM, EXTERNAL_RGBA, TYPE_I16},				//FORMAT_RGBA16_SSCALE,
			{INTERNAL_RGBA16U, EXTERNAL_RGBA_INTEGER, TYPE_U16},			//FORMAT_RGBA16_UINT,
			{INTERNAL_RGBA16I, EXTERNAL_RGBA_INTEGER, TYPE_I16},			//FORMAT_RGBA16_SINT,
			{INTERNAL_RGBA16F, EXTERNAL_RGBA, TYPE_F16},					//FORMAT_RGBA16_SFLOAT,

			{INTERNAL_R32U, EXTERNAL_RED_INTEGER, TYPE_U32},				//FORMAT_R32_UINT,
			{INTERNAL_R32I, EXTERNAL_RED_INTEGER, TYPE_I32},				//FORMAT_R32_SINT,
			{INTERNAL_R32F, EXTERNAL_RED, TYPE_F32},						//FORMAT_R32_SFLOAT,

			{INTERNAL_RG32U, EXTERNAL_RG_INTEGER, TYPE_U32},				//FORMAT_RG32_UINT,
			{INTERNAL_RG32I, EXTERNAL_RG_INTEGER, TYPE_I32},				//FORMAT_RG32_SINT,
			{INTERNAL_RG32F, EXTERNAL_RG, TYPE_F32},						//FORMAT_RG32_SFLOAT,

			{INTERNAL_RGB32U, EXTERNAL_RGB_INTEGER, TYPE_U32},				//FORMAT_RGB32_UINT,
			{INTERNAL_RGB32I, EXTERNAL_RGB_INTEGER, TYPE_I32},				//FORMAT_RGB32_SINT,
			{INTERNAL_RGB32F, EXTERNAL_RGB, TYPE_F32},						//FORMAT_RGB32_SFLOAT,

			{INTERNAL_RGBA32U, EXTERNAL_RGBA_INTEGER, TYPE_U32},			//FORMAT_RGBA32_UINT,
			{INTERNAL_RGBA32I, EXTERNAL_RGBA_INTEGER, TYPE_I32},			//FORMAT_RGBA32_SINT,
			{INTERNAL_RGBA32F, EXTERNAL_RGBA, TYPE_F32},					//FORMAT_RGBA32_SFLOAT,

			{INTERNAL_R64F_EXT, EXTERNAL_RED, TYPE_F64_EXT},				//FORMAT_R64_SFLOAT,
			{INTERNAL_RG64F_EXT, EXTERNAL_RG, TYPE_F64_EXT},				//FORMAT_RG64_SFLOAT,
			{INTERNAL_RGB64F_EXT, EXTERNAL_RGB, TYPE_F64_EXT},				//FORMAT_RGB64_SFLOAT,
			{INTERNAL_RGBA64F_EXT, EXTERNAL_RGBA, TYPE_F64_EXT},			//FORMAT_RGBA64_SFLOAT,

			{INTERNAL_RG11B10F, EXTERNAL_RGB, TYPE_UINT32_RG11B10F},		//FORMAT_RG11B10_UFLOAT,
			{INTERNAL_RGB9E5, EXTERNAL_RGB, TYPE_UINT32_RGB9_E5},			//FORMAT_RGB9E5_UFLOAT,

			{INTERNAL_D16, EXTERNAL_DEPTH, TYPE_NONE},								//FORMAT_D16_UNORM,
			{INTERNAL_D24, EXTERNAL_DEPTH, TYPE_NONE},								//FORMAT_D24_UNORM,
			{INTERNAL_D32F, EXTERNAL_DEPTH, TYPE_NONE},								//FORMAT_D32_UFLOAT,
			{INTERNAL_S8_EXT, EXTERNAL_STENCIL, TYPE_NONE},							//FORMAT_S8_UNORM,
			{INTERNAL_D16S8_EXT, EXTERNAL_DEPTH, TYPE_NONE},						//FORMAT_D16_UNORM_S8_UINT,
			{INTERNAL_D24S8, EXTERNAL_DEPTH_STENCIL, TYPE_NONE},					//FORMAT_D24_UNORM_S8_UINT,
			{INTERNAL_D32FS8X24, EXTERNAL_DEPTH_STENCIL, TYPE_NONE},				//FORMAT_D32_SFLOAT_S8_UINT,

			{INTERNAL_RGBA_DXT1, EXTERNAL_NONE, TYPE_NONE},							//FORMAT_RGBA_DXT1_UNORM,
			{INTERNAL_SRGB_ALPHA_DXT1, EXTERNAL_NONE, TYPE_NONE},					//FORMAT_RGBA_DXT1_SRGB,
			{INTERNAL_RGBA_DXT3, EXTERNAL_NONE, TYPE_NONE},							//FORMAT_RGBA_DXT3_UNORM,
			{INTERNAL_SRGB_ALPHA_DXT3, EXTERNAL_NONE, TYPE_NONE},					//FORMAT_RGBA_DXT3_SRGB,
			{INTERNAL_RGBA_DXT5, EXTERNAL_NONE, TYPE_NONE},							//FORMAT_RGBA_DXT5_UNORM,
			{INTERNAL_SRGB_ALPHA_DXT5, EXTERNAL_NONE, TYPE_NONE},					//FORMAT_RGBA_DXT5_SRGB,
			{INTERNAL_R_ATI1N_UNORM, EXTERNAL_NONE, TYPE_NONE},						//FORMAT_R_ATI1N_UNORM,
			{INTERNAL_R_ATI1N_SNORM, EXTERNAL_NONE, TYPE_NONE},						//FORMAT_R_ATI1N_SNORM,
			{INTERNAL_RG_ATI2N_UNORM, EXTERNAL_NONE, TYPE_NONE},					//FORMAT_RG_ATI2N_UNORM,
			{INTERNAL_RG_ATI2N_SNORM, EXTERNAL_NONE, TYPE_NONE},					//FORMAT_RG_ATI2N_SNORM,
			{INTERNAL_RGB_BP_UNSIGNED_FLOAT, EXTERNAL_NONE, TYPE_NONE},				//FORMAT_RGB_BP_UFLOAT,
			{INTERNAL_RGB_BP_SIGNED_FLOAT, EXTERNAL_NONE, TYPE_NONE},				//FORMAT_RGB_BP_SFLOAT,
			{INTERNAL_RGB_BP_UNORM, EXTERNAL_NONE, TYPE_NONE},						//FORMAT_RGB_BP_UNORM,
			{INTERNAL_SRGB_BP_UNORM, EXTERNAL_NONE, TYPE_NONE},						//FORMAT_RGB_BP_SRGB,

			{INTERNAL_RGB_ETC2, EXTERNAL_NONE, TYPE_NONE},							//FORMAT_RGB_ETC2_UNORM,
			{INTERNAL_SRGB8_ETC2, EXTERNAL_NONE, TYPE_NONE},						//FORMAT_RGB_ETC2_SRGB,
			{INTERNAL_RGBA_PUNCHTHROUGH_ETC2, EXTERNAL_NONE, TYPE_NONE},			//FORMAT_RGBA_ETC2_PUNCHTHROUGH_UNORM,
			{INTERNAL_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2, EXTERNAL_NONE, TYPE_NONE},	//FORMAT_RGBA_ETC2_PUNCHTHROUGH_SRGB,
			{INTERNAL_RGBA_ETC2, EXTERNAL_NONE, TYPE_NONE},							//FORMAT_RGBA_ETC2_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ETC2_EAC, EXTERNAL_NONE, TYPE_NONE},				//FORMAT_RGBA_ETC2_SRGB,
			{INTERNAL_R11_EAC, EXTERNAL_NONE, TYPE_NONE},							//FORMAT_R11_EAC_UNORM,
			{INTERNAL_SIGNED_R11_EAC, EXTERNAL_NONE, TYPE_NONE},					//FORMAT_R11_EAC_SNORM,
			{INTERNAL_RG11_EAC, EXTERNAL_NONE, TYPE_NONE},							//FORMAT_RG11_EAC_UNORM,
			{INTERNAL_SIGNED_RG11_EAC, EXTERNAL_NONE, TYPE_NONE},					//FORMAT_RG11_EAC_SNORM,

			{INTERNAL_RGBA_ASTC_4x4, EXTERNAL_NONE, TYPE_NONE},						//FORMAT_RGBA_ASTC4X4_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_4x4, EXTERNAL_NONE, TYPE_NONE},				//FORMAT_RGBA_ASTC4X4_SRGB,
			{INTERNAL_RGBA_ASTC_5x4, EXTERNAL_NONE, TYPE_NONE},						//FORMAT_RGBA_ASTC5X4_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_5x4, EXTERNAL_NONE, TYPE_NONE},				//FORMAT_RGBA_ASTC5X4_SRGB,
			{INTERNAL_RGBA_ASTC_5x5, EXTERNAL_NONE, TYPE_NONE},						//FORMAT_RGBA_ASTC5X5_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_5x5, EXTERNAL_NONE, TYPE_NONE},				//FORMAT_RGBA_ASTC5X5_SRGB,
			{INTERNAL_RGBA_ASTC_6x5, EXTERNAL_NONE, TYPE_NONE},						//FORMAT_RGBA_ASTC6X5_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_6x5, EXTERNAL_NONE, TYPE_NONE},				//FORMAT_RGBA_ASTC6X5_SRGB,
			{INTERNAL_RGBA_ASTC_6x6, EXTERNAL_NONE, TYPE_NONE},						//FORMAT_RGBA_ASTC6X6_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_6x6, EXTERNAL_NONE, TYPE_NONE},				//FORMAT_RGBA_ASTC6X6_SRGB,
			{INTERNAL_RGBA_ASTC_8x5, EXTERNAL_NONE, TYPE_NONE},						//FORMAT_RGBA_ASTC8X5_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_8x5, EXTERNAL_NONE, TYPE_NONE},				//FORMAT_RGBA_ASTC8X5_SRGB,
			{INTERNAL_RGBA_ASTC_8x6, EXTERNAL_NONE, TYPE_NONE},						//FORMAT_RGBA_ASTC8X6_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_8x6, EXTERNAL_NONE, TYPE_NONE},				//FORMAT_RGBA_ASTC8X6_SRGB,
			{INTERNAL_RGBA_ASTC_8x8, EXTERNAL_NONE, TYPE_NONE},						//FORMAT_RGBA_ASTC8X8_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_8x8, EXTERNAL_NONE, TYPE_NONE},				//FORMAT_RGBA_ASTC8X8_SRGB,
			{INTERNAL_RGBA_ASTC_10x5, EXTERNAL_NONE, TYPE_NONE},					//FORMAT_RGBA_ASTC10X5_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_10x5, EXTERNAL_NONE, TYPE_NONE},			//FORMAT_RGBA_ASTC10X5_SRGB,
			{INTERNAL_RGBA_ASTC_10x6, EXTERNAL_NONE, TYPE_NONE},					//FORMAT_RGBA_ASTC10X6_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_10x6, EXTERNAL_NONE, TYPE_NONE},			//FORMAT_RGBA_ASTC10X6_SRGB,
			{INTERNAL_RGBA_ASTC_10x8, EXTERNAL_NONE, TYPE_NONE},					//FORMAT_RGBA_ASTC10X8_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_10x8, EXTERNAL_NONE, TYPE_NONE},			//FORMAT_RGBA_ASTC10X8_SRGB,
			{INTERNAL_RGBA_ASTC_10x10, EXTERNAL_NONE, TYPE_NONE},					//FORMAT_RGBA_ASTC10X10_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_10x10, EXTERNAL_NONE, TYPE_NONE},			//FORMAT_RGBA_ASTC10X10_SRGB,
			{INTERNAL_RGBA_ASTC_12x10, EXTERNAL_NONE, TYPE_NONE},					//FORMAT_RGBA_ASTC12X10_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_12x10, EXTERNAL_NONE, TYPE_NONE},			//FORMAT_RGBA_ASTC12X10_SRGB,
			{INTERNAL_RGBA_ASTC_12x12, EXTERNAL_NONE, TYPE_NONE},					//FORMAT_RGBA_ASTC12X12_UNORM,
			{INTERNAL_SRGB8_ALPHA8_ASTC_12x12, EXTERNAL_NONE, TYPE_NONE},			//FORMAT_RGBA_ASTC12X12_SRGB,

			{INTERNAL_RGBA4, EXTERNAL_BGRA, TYPE_UINT16_RGBA4},						//FORMAT_BGRA4_UNORM,
			{INTERNAL_RGBA4, EXTERNAL_BGRA, TYPE_UINT16_RGBA4},						//FORMAT_BGRA4_USCALED,
			{INTERNAL_R5G6B5, EXTERNAL_BGR, TYPE_UINT16_R5G6B5},					//FORMAT_B5G6R5_UNORM,
			{INTERNAL_R5G6B5, EXTERNAL_BGR, TYPE_UINT16_R5G6B5},					//FORMAT_B5G6R5_USCALED,
			{INTERNAL_RGB5A1, EXTERNAL_BGRA, TYPE_UINT16_RGB5A1},					//FORMAT_BGR5A1_UNORM,
			{INTERNAL_RGB5A1, EXTERNAL_BGRA, TYPE_UINT16_RGB5A1},					//FORMAT_BGRA1_USCALED,

			{INTERNAL_RGB8_UNORM, EXTERNAL_BGR, TYPE_U8},							//FORMAT_BGR8_UNORM,
			{INTERNAL_RGB8_SNORM, EXTERNAL_BGR, TYPE_I8},							//FORMAT_BGR8_SNORM,
			{INTERNAL_RGB8_UNORM, EXTERNAL_BGR, TYPE_U8},							//FORMAT_BGR8_USCALED,
			{INTERNAL_RGB8_SNORM, EXTERNAL_BGR, TYPE_I8},							//FORMAT_BGR8_SSCALED,
			{INTERNAL_RGB8U, EXTERNAL_BGR_INTEGER, TYPE_U8},						//FORMAT_BGR8_UINT,
			{INTERNAL_RGB8I, EXTERNAL_BGR_INTEGER, TYPE_I8},						//FORMAT_BGR8_SINT,
			{INTERNAL_SRGB8, EXTERNAL_BGR, TYPE_U8},								//FORMAT_BGR8_SRGB,

			{INTERNAL_RGBA8_UNORM, EXTERNAL_BGRA, TYPE_U8},							//FORMAT_BGRA8_UNORM,
			{INTERNAL_RGBA8_SNORM, EXTERNAL_BGRA, TYPE_I8},							//FORMAT_BGRA8_SNORM,
			{INTERNAL_RGBA8_UNORM, EXTERNAL_BGRA, TYPE_U8},							//FORMAT_BGRA8_USCALED,
			{INTERNAL_RGBA8_SNORM, EXTERNAL_BGRA, TYPE_I8},							//FORMAT_BGRA8_SSCALED,
			{INTERNAL_RGBA8U, EXTERNAL_BGRA_INTEGER, TYPE_U8},						//FORMAT_BGRA8_UINT,
			{INTERNAL_RGBA8I, EXTERNAL_BGRA_INTEGER, TYPE_I8},						//FORMAT_BGRA8_SINT,
			{INTERNAL_SRGB8_ALPHA8, EXTERNAL_BGRA, TYPE_U8},						//FORMAT_BGRA8_SRGB,

			{INTERNAL_RGB10A2_UNORM, EXTERNAL_RGBA, TYPE_UINT32_RGB10A2},			//FORMAT_BGR10A2_UNORM,
			{INTERNAL_RGB10A2_SNORM_EXT, EXTERNAL_RGBA, TYPE_UINT32_RGB10A2},		//FORMAT_BGR10A2_SNORM,
			{INTERNAL_RGB10A2_UNORM, EXTERNAL_RGBA, TYPE_UINT32_RGB10A2},			//FORMAT_BGR10A2_USCALE,
			{INTERNAL_RGB10A2_SNORM_EXT, EXTERNAL_RGBA, TYPE_UINT32_RGB10A2},		//FORMAT_BGR10A2_SSCALE,
			{INTERNAL_RGB10A2U, EXTERNAL_RGBA_INTEGER, TYPE_UINT32_RGB10A2},		//FORMAT_BGR10A2_UINT,
			{INTERNAL_RGB10A2I_EXT, EXTERNAL_RGBA_INTEGER, TYPE_UINT32_RGB10A2},	//FORMAT_BGR10A2_SINT,

			{INTERNAL_RG3B2, EXTERNAL_RGB, TYPE_UINT8_RG3B2},						//FORMAT_RG3B2_UNORM,
			{INTERNAL_RGB8_UNORM, EXTERNAL_BGRA, TYPE_U8},							//FORMAT_BGRX8_UNORM,
			{INTERNAL_SRGB8, EXTERNAL_BGRA, TYPE_U8},								//FORMAT_BGRX8_SRGB,

			{INTERNAL_R8_UNORM, EXTERNAL_RED, TYPE_U8},								//FORMAT_L8_UNORM,
			{INTERNAL_R8_UNORM, EXTERNAL_RED, TYPE_U8},								//FORMAT_A8_UNORM,
			{INTERNAL_RG8_UNORM, EXTERNAL_RG, TYPE_U8},								//FORMAT_LA8_UNORM,
			{INTERNAL_R16_UNORM, EXTERNAL_RED, TYPE_U16},							//FORMAT_L16_UNORM,
			{INTERNAL_R16_UNORM, EXTERNAL_RED, TYPE_U16},							//FORMAT_A16_UNORM,
			{INTERNAL_RG16_UNORM, EXTERNAL_RG, TYPE_U16},							//FORMAT_LA16_UNORM,

			{INTERNAL_RGB_PVRTC_4BPPV1, EXTERNAL_NONE, TYPE_NONE},					//FORMAT_RGB_PVRTC1_8X8_UNORM,
			{INTERNAL_SRGB_PVRTC_2BPPV1, EXTERNAL_NONE, TYPE_NONE},					//FORMAT_RGB_PVRTC1_8X8_SRGB,
			{INTERNAL_RGB_PVRTC_2BPPV1, EXTERNAL_NONE, TYPE_NONE},					//FORMAT_RGB_PVRTC1_16X8_UNORM,
			{INTERNAL_SRGB_PVRTC_4BPPV1, EXTERNAL_NONE, TYPE_NONE},					//FORMAT_RGB_PVRTC1_16X8_SRGB,
			{INTERNAL_RGBA_PVRTC_4BPPV1, EXTERNAL_NONE, TYPE_NONE},					//FORMAT_RGBA_PVRTC1_8X8_UNORM,
			{INTERNAL_SRGB_ALPHA_PVRTC_2BPPV1, EXTERNAL_NONE, TYPE_NONE},			//FORMAT_RGBA_PVRTC1_8X8_SRGB,
			{INTERNAL_RGBA_PVRTC_2BPPV1, EXTERNAL_NONE, TYPE_NONE},					//FORMAT_RGBA_PVRTC1_16X8_UNORM,
			{INTERNAL_SRGB_ALPHA_PVRTC_4BPPV1, EXTERNAL_NONE, TYPE_NONE},			//FORMAT_RGBA_PVRTC1_16X8_SRGB,
			{INTERNAL_RGBA_PVRTC_4BPPV2, EXTERNAL_NONE, TYPE_NONE},					//FORMAT_RGBA_PVRTC2_4X4_UNORM,
			{INTERNAL_SRGB_ALPHA_PVRTC_4BPPV2, EXTERNAL_NONE, TYPE_NONE},			//FORMAT_RGBA_PVRTC2_4X4_SRGB,
			{INTERNAL_RGBA_PVRTC_2BPPV2, EXTERNAL_NONE, TYPE_NONE},					//FORMAT_RGBA_PVRTC2_8X4_UNORM,
			{INTERNAL_SRGB_ALPHA_PVRTC_2BPPV2, EXTERNAL_NONE, TYPE_NONE},			//FORMAT_RGBA_PVRTC2_8X4_SRGB,

			{INTERNAL_RGB_ETC, EXTERNAL_NONE, TYPE_NONE},							//FORMAT_RGB_ETC_UNORM,
			{INTERNAL_ATC_RGB, EXTERNAL_NONE, TYPE_NONE},							//FORMAT_RGB_ATC_UNORM,
			{INTERNAL_ATC_RGBA_EXPLICIT_ALPHA, EXTERNAL_NONE, TYPE_NONE},			//FORMAT_RGBA_ATC_EXPLICIT_UNORM,
			{INTERNAL_ATC_RGBA_INTERPOLATED_ALPHA, EXTERNAL_NONE, TYPE_NONE},		//FORMAT_RGBA_ATC_INTERPOLATED_UNORM,
		};

		static_assert(sizeof(Table) / sizeof(Table[0]) == FORMAT_COUNT, "GLI error: format descriptor list doesn't match number of supported formats");

		std::copy(&Table[0], &Table[0] + FORMAT_COUNT, this->Translation.begin());
	}

	inline gl::target const & gl::translate(gli::target Target) const
	{
		static gl::target const Table[] =
		{
			gl::TARGET_1D,
			gl::TARGET_1D_ARRAY,
			gl::TARGET_2D,
			gl::TARGET_2D_ARRAY,
			gl::TARGET_3D,
			gl::TARGET_RECT,
			gl::TARGET_RECT_ARRAY,
			gl::TARGET_CUBE,
			gl::TARGET_CUBE_ARRAY
		};
		static_assert(sizeof(Table) / sizeof(Table[0]) == TARGET_COUNT, "GLI error: target descriptor list doesn't match number of supported targets");

		return Table[Target];
	}

	inline gl::format const & gl::translate(gli::format Format) const
	{
		assert(Format >= FORMAT_FIRST && Format <= FORMAT_LAST);
		return this->Translation[Format - FORMAT_FIRST];
	}

	inline gl::swizzles gl::translate(gli::swizzles const & Swizzles) const
	{
		static gl::swizzle const Table[] =
		{
			gl::SWIZZLE_RED,
			gl::SWIZZLE_GREEN,
			gl::SWIZZLE_BLUE,
			gl::SWIZZLE_ALPHA,
			gl::SWIZZLE_ZERO,
			gl::SWIZZLE_ONE
		};
		static_assert(sizeof(Table) / sizeof(Table[0]) == SWIZZLE_COUNT, "GLI error: swizzle descriptor list doesn't match number of supported swizzles");

		return gl::swizzles(Table[Swizzles.r], Table[Swizzles.g], Table[Swizzles.b], Table[Swizzles.a]);
	}

	inline gli::format gl::find(gl::internalFormat InternalFormat, gl::externalFormat ExternalFormat, gl::typeFormat Type)
	{
		for(int FormatIndex = FORMAT_FIRST; FormatIndex <= FORMAT_LAST; ++FormatIndex)
		{
			std::size_t const Index = FormatIndex - FORMAT_FIRST;
			if (this->Translation[Index].Internal != InternalFormat)
				continue;
			if (this->Translation[Index].External != ExternalFormat)
				continue;
			if (this->Translation[Index].Type != Type)
				continue;
			return static_cast<gli::format>(FormatIndex);
		}
		return static_cast<gli::format>(FORMAT_INVALID);
	}

}//namespace gli
