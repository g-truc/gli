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

	struct dxt1_block
	{
		uint16_t Color0;
		uint16_t Color1;
		uint8_t Row0;
		uint8_t Row1;
		uint8_t Row2;
		uint8_t Row3;
	};

	struct dxt3_block
	{
		uint16_t AlphaRow0;
		uint16_t AlphaRow1;
		uint16_t AlphaRow2;
		uint16_t AlphaRow3;
		uint16_t Color0;
		uint16_t Color1;
		uint8_t Row0;
		uint8_t Row1;
		uint8_t Row2;
		uint8_t Row3;
	};

	struct dxt5_block
	{
		uint8_t Alpha0;
		uint8_t Alpha1;
		uint8_t AlphaR0;
		uint8_t AlphaR1;
		uint8_t AlphaR2;
		uint8_t AlphaR3;
		uint8_t AlphaR4;
		uint8_t AlphaR5;
		uint16_t Color0;
		uint16_t Color1;
		uint8_t Row0;
		uint8_t Row1;
		uint8_t Row2;
		uint8_t Row3;
	};
	
	inline void flip_block_s3tc(uint8_t* BlockDst, uint8_t* BlockSrc, format Format, bool HeightTwo)
	{
		// All DXT-compressed textures are stored as RGBA, the RGB format is used only to tell OpenGL
		// how to interpret the data. It does not, however, matter for how the data is laid out,
		// so it can be flipped the same way.
		if(Format == FORMAT_RGB_DXT1_UNORM || Format == FORMAT_RGB_DXT1_SRGB
		|| Format == FORMAT_RGBA_DXT1_UNORM || Format == FORMAT_RGBA_DXT1_SRGB)
		{
			dxt1_block* Src = reinterpret_cast<dxt1_block*>(BlockSrc);
			dxt1_block* Dst = reinterpret_cast<dxt1_block*>(BlockDst);
	
			if(HeightTwo)
			{
				Dst->Color0 = Src->Color0;
				Dst->Color1 = Src->Color1;
				Dst->Row0 = Src->Row1;
				Dst->Row1 = Src->Row0;
				Dst->Row2 = Src->Row2;
				Dst->Row3 = Src->Row3;
				
				return;
			}

			Dst->Color0 = Src->Color0;
			Dst->Color1 = Src->Color1;
			Dst->Row0 = Src->Row3;
			Dst->Row1 = Src->Row2;
			Dst->Row2 = Src->Row1;
			Dst->Row3 = Src->Row0;
				
			return;
		}

		// DXT3
		if(Format == FORMAT_RGBA_DXT3_UNORM || Format == FORMAT_RGBA_DXT3_SRGB)
		{
			dxt3_block* Src = reinterpret_cast<dxt3_block*>(BlockSrc);
			dxt3_block* Dst = reinterpret_cast<dxt3_block*>(BlockDst);

			if(HeightTwo)
			{
				Dst->AlphaRow0 = Src->AlphaRow1;
				Dst->AlphaRow1 = Src->AlphaRow0;
				Dst->AlphaRow2 = Src->AlphaRow2;
				Dst->AlphaRow3 = Src->AlphaRow3;
				Dst->Color0 = Src->Color0;
				Dst->Color1 = Src->Color1;
				Dst->Row0 = Src->Row1;
				Dst->Row1 = Src->Row0;
				Dst->Row2 = Src->Row2;
				Dst->Row3 = Src->Row3;

				return;
			}

			Dst->AlphaRow0 = Src->AlphaRow3;
			Dst->AlphaRow1 = Src->AlphaRow2;
			Dst->AlphaRow2 = Src->AlphaRow1;
			Dst->AlphaRow3 = Src->AlphaRow0;
			Dst->Color0 = Src->Color0;
			Dst->Color1 = Src->Color1;
			Dst->Row0 = Src->Row3;
			Dst->Row1 = Src->Row2;
			Dst->Row2 = Src->Row1;
			Dst->Row3 = Src->Row0;
				
			return;
		}

		// DXT5
		if(Format == FORMAT_RGBA_DXT5_UNORM || Format == FORMAT_RGBA_DXT5_SRGB)
		{
			dxt5_block* Src = reinterpret_cast<dxt5_block*>(BlockSrc);
			dxt5_block* Dst = reinterpret_cast<dxt5_block*>(BlockDst);

			if(HeightTwo)
			{
				Dst->Alpha0 = Src->Alpha0;
				Dst->Alpha1 = Src->Alpha1;
				// operator+ has precedence over operator>> and operator<<, hence the parentheses. very important!
				Dst->AlphaR0 = ((Src->AlphaR1 & 0b11110000) >> 4) + ((Src->AlphaR2 & 0b1111) << 4);
				Dst->AlphaR1 = ((Src->AlphaR2 & 0b11110000) >> 4) + ((Src->AlphaR0 & 0b1111) << 4);
				Dst->AlphaR2 = ((Src->AlphaR0 & 0b11110000) >> 4) + ((Src->AlphaR1 & 0b1111) << 4);
				Dst->AlphaR3 = Src->AlphaR3;
				Dst->AlphaR4 = Src->AlphaR4;
				Dst->AlphaR5 = Src->AlphaR5;
				Dst->Color0 = Src->Color0;
				Dst->Color1 = Src->Color1;
				Dst->Row0 = Src->Row1;
				Dst->Row1 = Src->Row0;
				Dst->Row2 = Src->Row2;
				Dst->Row3 = Src->Row3;
			
				return;
			}

			Dst->Alpha0 = Src->Alpha0;
			Dst->Alpha1 = Src->Alpha1;
			// operator+ has precedence over operator>> and operator<<, hence the parentheses. very important!
			Dst->AlphaR0 = ((Src->AlphaR4 & 0b11110000) >> 4) + ((Src->AlphaR5 & 0b1111) << 4);
			Dst->AlphaR1 = ((Src->AlphaR5 & 0b11110000) >> 4) + ((Src->AlphaR3 & 0b1111) << 4);
			Dst->AlphaR2 = ((Src->AlphaR3 & 0b11110000) >> 4) + ((Src->AlphaR4 & 0b1111) << 4);
			Dst->AlphaR3 = ((Src->AlphaR1 & 0b11110000) >> 4) + ((Src->AlphaR2 & 0b1111) << 4);
			Dst->AlphaR4 = ((Src->AlphaR2 & 0b11110000) >> 4) + ((Src->AlphaR0 & 0b1111) << 4);
			Dst->AlphaR5 = ((Src->AlphaR0 & 0b11110000) >> 4) + ((Src->AlphaR1 & 0b1111) << 4);
			Dst->Color0 = Src->Color0;
			Dst->Color1 = Src->Color1;
			Dst->Row0 = Src->Row3;
			Dst->Row1 = Src->Row2;
			Dst->Row2 = Src->Row1;
			Dst->Row3 = Src->Row0;
			
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
				flip_block_s3tc(ImageDst.data<uint8_t>() + i_block * block_size(Format), ImageSrc.data<uint8_t>() + i_block * block_size(Format), Format, true);
			
			return;
		}

		std::size_t const MaxYBlock = ImageSrc.dimensions().y / 4 - 1;
		for(std::size_t i_row = 0; i_row <= MaxYBlock; ++i_row)
			for(std::size_t i_block = 0; i_block < XBlocks; ++i_block)
				flip_block_s3tc(ImageDst.data<uint8_t>() + (MaxYBlock - i_row) * block_size(Format) * XBlocks + i_block * block_size(Format), ImageSrc.data<uint8_t>() + i_row * block_size(Format) * XBlocks + i_block * block_size(Format), Format, false);
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
