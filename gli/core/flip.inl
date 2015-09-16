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
/// @file gli/core/flip.inl
/// @date 2014-01-17 / 2014-01-17
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace gli
{
namespace detail
{
	inline void flip(image ImageDst, image ImageSrc, std::size_t BlockSize)
	{
		std::size_t const LineSize = BlockSize * ImageDst.dimensions().x;

		for(std::size_t y = 0; y < ImageDst.dimensions().y; ++y)
		{
			std::size_t OffsetDst = LineSize * y;
			std::size_t OffsetSrc = ImageSrc.size() - (LineSize * (y + 1));

			memcpy(
				ImageDst.data<glm::byte>() + OffsetDst,
				ImageSrc.data<glm::byte>() + OffsetSrc,
				LineSize);
		}
	}

	inline void flip_block_s3tc(glm::byte* BlockDst, glm::byte* BlockSrc, format Format, bool HeightTwo)
	{
		// DXT1
		if(Format == FORMAT_RGB_DXT1_UNORM || Format == FORMAT_RGB_DXT1_SRGB)
		{
			std::array<glm::byte, 8> BlockFlip;
	
			// 0, 1 color1
			// 2, 3 color2
			// 4, 5, 6, 7 color rows
			if(HeightTwo)
			{
				BlockFlip[0] = BlockSrc[0];
				BlockFlip[1] = BlockSrc[1];
				BlockFlip[2] = BlockSrc[2];
				BlockFlip[3] = BlockSrc[3];
				BlockFlip[4] = BlockSrc[5];
				BlockFlip[5] = BlockSrc[4];
				BlockFlip[6] = BlockFlip[7] = 0;
				
				memcpy(BlockDst, BlockFlip.data(), 8);
				return;
			}

			BlockFlip[0] = BlockSrc[0];
			BlockFlip[1] = BlockSrc[1];
			BlockFlip[2] = BlockSrc[2];
			BlockFlip[3] = BlockSrc[3];
			BlockFlip[4] = BlockSrc[7];
			BlockFlip[5] = BlockSrc[6];
			BlockFlip[6] = BlockSrc[5];
			BlockFlip[7] = BlockSrc[4];
			
			memcpy(BlockDst, BlockFlip.data(), 8);
			return;
		}

		// DXT1 w/ alpha
		if(Format == FORMAT_RGBA_DXT1_UNORM || Format == FORMAT_RGBA_DXT1_SRGB)
		{
			// ?? can't find any spec for how a DXT1 texture with alpha is laid out
			assert(false);
		}

		// DXT3
		if(Format == FORMAT_RGBA_DXT3_UNORM || Format == FORMAT_RGBA_DXT3_SRGB)
		{
			std::array<glm::byte, 16> BlockFlip;

			// 0 - 7 alpha pixels (two bytes per row)
			// 8, 9 color1
			// 10, 11 color2
			// 12, 13, 14, 15 pixel rows
			if(HeightTwo)
			{
				// flip alpha
				BlockFlip[0] = BlockSrc[2];
				BlockFlip[1] = BlockSrc[3];
				BlockFlip[2] = BlockSrc[0];
				BlockFlip[3] = BlockSrc[1];
				BlockFlip[4] = BlockFlip[5] = BlockFlip[6] = BlockFlip[7] = 0;

				// save color
				BlockFlip[8] = BlockSrc[8];
				BlockFlip[9] = BlockSrc[9];
				BlockFlip[10] = BlockSrc[10];
				BlockFlip[11] = BlockSrc[11];

				// flip color
				BlockFlip[12] = BlockSrc[13];
				BlockFlip[13] = BlockSrc[12];
				BlockFlip[14] = BlockFlip[15] = 0;
			
				memcpy(BlockDst, BlockFlip.data(), 16);
				return;
			}

			// flip alpha
			BlockFlip[0] = BlockSrc[6];
			BlockFlip[1] = BlockSrc[7];
			BlockFlip[2] = BlockSrc[4];
			BlockFlip[3] = BlockSrc[5];
			BlockFlip[4] = BlockSrc[2];
			BlockFlip[5] = BlockSrc[3];
			BlockFlip[6] = BlockSrc[0];
			BlockFlip[7] = BlockSrc[1];

			// save color
			BlockFlip[8] = BlockSrc[8];
			BlockFlip[9] = BlockSrc[9];
			BlockFlip[10] = BlockSrc[10];
			BlockFlip[11] = BlockSrc[11];

			// flip color
			BlockFlip[12] = BlockSrc[15];
			BlockFlip[13] = BlockSrc[14];
			BlockFlip[14] = BlockSrc[13];
			BlockFlip[15] = BlockSrc[12];
			
			memcpy(BlockDst, BlockFlip.data(), 16);
			return;
		}

		// DXT5
		if(Format == FORMAT_RGBA_DXT5_UNORM || Format == FORMAT_RGBA_DXT5_SRGB)
		{
			std::array<glm::byte, 16> BlockFlip;

			// 0 alpha1
			// 1 alpha2
			// 2, 3, 4, 5, 6, 7 alpha data (3 bits per pixel)
			// 8, 9 color1
			// 10, 11 color2
			// 12, 13, 14, 15 pixel rows
			if(HeightTwo)
			{
				// save alpha
				BlockFlip[0] = BlockSrc[0];
				BlockFlip[1] = BlockSrc[1];

				// flip alpha
				BlockFlip[2] = (BlockSrc[3] & 0b11110000) >> 4 + (BlockSrc[4] & 0b1111) << 4;
				BlockFlip[3] = (BlockSrc[4] & 0b11110000) >> 4 + (BlockSrc[2] & 0b1111) << 4;
				BlockFlip[4] = (BlockSrc[2] & 0b11110000) >> 4 + (BlockSrc[3] & 0b1111) << 4;
				BlockFlip[5] = BlockFlip[6] = BlockFlip[7] = 0;

				// save color
				BlockFlip[8] = BlockSrc[8];
				BlockFlip[9] = BlockSrc[9];
				BlockFlip[10] = BlockSrc[10];
				BlockFlip[11] = BlockSrc[11];

				// flip color
				BlockFlip[12] = BlockSrc[13];
				BlockFlip[13] = BlockSrc[12];
				BlockFlip[14] = BlockFlip[15] = 0;
			
				memcpy(BlockDst, BlockFlip.data(), 16);
				return;
			}

			// save alpha
			BlockFlip[0] = BlockSrc[0];
			BlockFlip[1] = BlockSrc[1];

			// flip alpha
			BlockFlip[2] = (BlockSrc[6] & 0b11110000) >> 4 + (BlockSrc[7] & 0b1111) << 4;
			BlockFlip[3] = (BlockSrc[7] & 0b11110000) >> 4 + (BlockSrc[5] & 0b1111) << 4;
			BlockFlip[4] = (BlockSrc[5] & 0b11110000) >> 4 + (BlockSrc[6] & 0b1111) << 4;
			BlockFlip[5] = (BlockSrc[3] & 0b11110000) >> 4 + (BlockSrc[4] & 0b1111) << 4;
			BlockFlip[6] = (BlockSrc[4] & 0b11110000) >> 4 + (BlockSrc[2] & 0b1111) << 4;
			BlockFlip[7] = (BlockSrc[2] & 0b11110000) >> 4 + (BlockSrc[3] & 0b1111) << 4;

			// save color
			BlockFlip[8] = BlockSrc[8];
			BlockFlip[9] = BlockSrc[9];
			BlockFlip[10] = BlockSrc[10];
			BlockFlip[11] = BlockSrc[11];

			// flip color
			BlockFlip[12] = BlockSrc[15];
			BlockFlip[13] = BlockSrc[14];
			BlockFlip[14] = BlockSrc[13];
			BlockFlip[15] = BlockSrc[12];

			memcpy(BlockDst, BlockFlip.data(), 16);
			return;
		}
		
		// invalid format specified (unknown S3TC format?)
		assert(false);
	}

	inline void flip_s3tc(image ImageDst, image ImageSrc, format Format)
	{
		if(ImageSrc.dimensions().y == 1)
		{
			memcpy(ImageDst.data(),
				   ImageSrc.data(),
				   ImageSrc.size());
			return;
		}

		std::size_t const XBlocks = ImageSrc.dimensions().x <= 4 ? 1 : ImageSrc.dimensions().x / 4;

		if(ImageSrc.dimensions().y == 2)
		{
			for(std::size_t i_block = 0; i_block < XBlocks; ++i_block)
				flip_block_s3tc(ImageDst.data<glm::byte>() + i_block * block_size(Format), ImageSrc.data<glm::byte>() + i_block * block_size(Format), Format, true);
			
			return;
		}

		std::size_t const MaxYBlock = ImageSrc.dimensions().y / 4 - 1;
		for(std::size_t i_row = 0; i_row <= MaxYBlock; ++i_row)
			for(std::size_t i_block = 0; i_block < XBlocks; ++i_block)
				flip_block_s3tc(ImageDst.data<glm::byte>() + (MaxYBlock - i_row) * block_size(Format) * XBlocks + i_block * block_size(Format), ImageSrc.data<glm::byte>() + i_row * block_size(Format) * XBlocks + i_block * block_size(Format), Format, false);
	}
}//namespace detail

template <>
inline texture2D flip(texture2D const & Texture)
{
	assert(!is_compressed(Texture.format()) || is_compressed_s3tc(Texture.format()));

	texture2D Flip(Texture.format(), Texture.dimensions(), Texture.levels());

	if(!is_compressed(Texture.format()))
	{
		gli::size_t const BlockSize = block_size(Texture.format());

		for(std::size_t Level = 0; Level < Flip.levels(); ++Level)
			detail::flip(Flip[Level], Texture[Level], BlockSize);
	}
	else
		for(std::size_t Level = 0; Level < Flip.levels(); ++Level)
			detail::flip_s3tc(Flip[Level], Texture[Level], Texture.format());

	return Flip;
}

template <>
inline texture2DArray flip(texture2DArray const & Texture)
{
	assert(!is_compressed(Texture.format()) || is_compressed_s3tc(Texture.format()));

	texture2DArray Flip(Texture.format(), Texture.dimensions(), Texture.layers(), Texture.levels());

	if(!is_compressed(Texture.format()))
	{
		gli::size_t const BlockSize = block_size(Texture.format());

		for(std::size_t Layer = 0; Layer < Flip.layers(); ++Layer)
		for(std::size_t Level = 0; Level < Flip.levels(); ++Level)
			detail::flip(Flip[Layer][Level], Texture[Layer][Level], BlockSize);
	}
	else
		for(std::size_t Layer = 0; Layer < Flip.layers(); ++Layer)
		for(std::size_t Level = 0; Level < Flip.levels(); ++Level)
			detail::flip_s3tc(Flip[Layer][Level], Texture[Layer][Level], Texture.format());

	return Flip;
}

template <>
inline textureCube flip(textureCube const & Texture)
{
	assert(!is_compressed(Texture.format()) || is_compressed_s3tc(Texture.format()));

	textureCube Flip(Texture.format(), Texture.dimensions(), Texture.levels());

	if(!is_compressed(Texture.format()))
	{
		gli::size_t const BlockSize = block_size(Texture.format());

		for(std::size_t Face = 0; Face < Flip.faces(); ++Face)
		for(std::size_t Level = 0; Level < Flip.levels(); ++Level)
			detail::flip(Flip[Face][Level], Texture[Face][Level], BlockSize);
	}
	else
		for(std::size_t Face = 0; Face < Flip.faces(); ++Face)
		for(std::size_t Level = 0; Level < Flip.levels(); ++Level)
			detail::flip_s3tc(Flip[Face][Level], Texture[Face][Level], Texture.format());

	return Flip;
}

template <>
inline textureCubeArray flip(textureCubeArray const & Texture)
{
	assert(!is_compressed(Texture.format()) || is_compressed_s3tc(Texture.format()));

	textureCubeArray Flip(Texture.format(), Texture.dimensions(), Texture.layers(), Texture.levels());

	if(!is_compressed(Texture.format()))
	{
		gli::size_t const BlockSize = block_size(Texture.format());

		for(std::size_t Layer = 0; Layer < Flip.layers(); ++Layer)
		for(std::size_t Face = 0; Face < Flip.faces(); ++Face)
		for(std::size_t Level = 0; Level < Flip.levels(); ++Level)
			detail::flip(Flip[Layer][Face][Level], Texture[Layer][Face][Level], BlockSize);
	}
	else
		for(std::size_t Layer = 0; Layer < Flip.layers(); ++Layer)
		for(std::size_t Face = 0; Face < Flip.faces(); ++Face)
		for(std::size_t Level = 0; Level < Flip.levels(); ++Level)
			detail::flip_s3tc(Flip[Layer][Face][Level], Texture[Layer][Face][Level], Texture.format());

	return Flip;
}

template <>
inline texture flip(texture const & Texture)
{
	switch(Texture.target())
	{
	case TARGET_2D:
		return flip(texture2D(Texture));

	case TARGET_2D_ARRAY:
		return flip(texture2DArray(Texture));

	case TARGET_CUBE:
		return flip(textureCube(Texture));

	case TARGET_CUBE_ARRAY:
		return flip(textureCubeArray(Texture));

	default:
		assert(false);
		return Texture;
	}
}

}//namespace gli
