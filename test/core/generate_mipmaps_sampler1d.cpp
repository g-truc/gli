/*
 * Tests for loading texels and generating mipmaps (1-D textures + texture sampler)
 */

#include <vector>

#include <gli/comparison.hpp>
#include <gli/type.hpp>
#include <gli/view.hpp>
#include <gli/duplicate.hpp>
#include <gli/generate_mipmaps.hpp>

#include <glm/gtc/epsilon.hpp>

namespace generate_mipmaps
{
	template <typename genType>
	int test(gli::format Format, const genType& BaseColor, const genType& TargetColor, std::size_t Size, gli::filter Filter)
	{
		int Error = 0;

		// create 1-D texture of appropriate size and clear with texels of given colors
		gli::texture1d Texture(Format,
			static_cast<gli::texture1d::extent_type>(static_cast<gli::texture1d::extent_type::value_type>(Size)));
		Texture.clear(BaseColor);
		Texture[0].clear(TargetColor);

		// get texel at position #0 from top mipmap level
		const genType TopTexel = Texture.load<genType>(static_cast<gli::texture1d::extent_type>(0),
			Texture.max_level());

		// If texture has multiple mipmap levels, texel from top level must match base color
		if (Texture.levels() > 1)
			Error += (TopTexel == BaseColor) ? 0 : 1;

		// create a texture view and a sampler
		gli::texture1d TextureView(gli::view(Texture, 0, 0));
		gli::fsampler1D SamplerA(gli::texture1d(gli::duplicate(Texture)), gli::WRAP_CLAMP_TO_EDGE);

		// generate mipmaps via filtering and get
		SamplerA.generate_mipmaps(Filter);
		gli::texture1d MipmapsA = SamplerA();

		// get texel at position #0 from top mipmap level (should match target color)
		const genType TopTexelA = MipmapsA.load<genType>(static_cast<gli::texture1d::extent_type>(0),
			MipmapsA.max_level());
		Error += (TopTexelA == TargetColor) ? 0 : 1;

		// if texture has multiple mipmap levels, texel from top level can't match texel from original texture
		if (Texture.levels() > 1)
			Error += (TopTexelA != TopTexel) ? 0 : 1;

		// create mipmaps view (should match texture view)
		gli::texture1d MipmapsViewA(gli::view(MipmapsA, 0, 0));
		Error += (TextureView == MipmapsViewA) ? 0 : 1;

		// Mipmaps generation using the wrapper function
		gli::texture1d MipmapsB = gli::generate_mipmaps(gli::texture1d(gli::duplicate(Texture)), Filter);

		// load texel at position #0 from top mipmap level (should match target color)
		const genType TopTexelB = MipmapsB.load<genType>(static_cast<gli::texture1d::extent_type>(0),
			MipmapsB.max_level());
		Error += (TopTexelB == TargetColor) ? 0 : 1;

		// if texture has multiple levels, texel from top level can't match texel from original texture
		if (Texture.levels() > 1)
			Error += (TopTexelB != TopTexel) ? 0 : 1;

		// create mipmaps view and match against texture view
		gli::texture1d MipmapsViewB(gli::view(MipmapsB, 0, 0));
		Error += (TextureView == MipmapsViewB) ? 0 : 1;

		Error += LoadA == LoadB ? 0 : 1;
		
		// Check levels
		Error += MipmapsA.max_level() == MipmapsB.max_level() ? 0 : 1;

		for(std::size_t i = 0; i < MipmapsA.max_level(); ++i)
		{
			genType const Load0 = MipmapsA.load<genType>(gli::texture1d::extent_type(0), i);
			genType const Load1 = MipmapsB.load<genType>(gli::texture1d::extent_type(0), i);
			Error += Load0 == Load1 ? 0 : 1;
		}

		// Compare custom mipmaps generation and wrapper mipmaps generation
		Error += MipmapViewA == MipmapViewB ? 0 : 1;

		return Error;
	}
} //namespace generate_mipmaps

int main()
{
	int Error = 0;

	// select filters for mipmap generation
	std::vector<gli::filter> Filters = {
		gli::FILTER_NEAREST,
		gli::FILTER_LINEAR
	};

	// select texture sizes
	std::vector<gli::size_t> Sizes = { 1, 2, 3, 4, 8, 16, 17, 24, 28, 32, 64, 128 };

	// run tests for each filter and size
	for (const auto Filter: Filters) {
		for (const auto Size: Sizes) {
			Error += generate_mipmaps::test(gli::FORMAT_R16_SFLOAT_PACK16,
				gli::packHalf(glm::vec1(0.0f)),
				gli::packHalf(glm::vec1(1.0f)),
				Size,
				Filter);

			Error += generate_mipmaps::test(gli::FORMAT_RG16_SFLOAT_PACK16,
				gli::packHalf(glm::vec2(0.0f, 0.0f)),
				gli::packHalf(glm::vec2(1.0f, 0.5f)),
				Size,
				Filter);

			Error += generate_mipmaps::test(gli::FORMAT_RGB16_SFLOAT_PACK16,
				gli::packHalf(glm::vec3(0.0f, 0.0f, 0.0f)),
				gli::packHalf(glm::vec3(1.0f, 0.5f, 0.0f)),
				Size,
				Filter);

			Error += generate_mipmaps::test(gli::FORMAT_RGBA16_SFLOAT_PACK16,
				gli::packHalf(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)),
				gli::packHalf(glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)),
				Size,
				Filter);

			Error += generate_mipmaps::test(gli::FORMAT_R32_SFLOAT_PACK32,
				glm::vec1(0.0f),
				glm::vec1(1.0f),
				Size,
				Filter);

			Error += generate_mipmaps::test(gli::FORMAT_RG32_SFLOAT_PACK32,
				glm::vec2(0.0f, 0.0f),
				glm::vec2(1.0f, 0.5f),
				Size,
				Filter);

			Error += generate_mipmaps::test(gli::FORMAT_RGB32_SFLOAT_PACK32,
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 0.5f, 0.0f),
				Size,
				Filter);

			Error += generate_mipmaps::test(gli::FORMAT_RGBA32_SFLOAT_PACK32,
				glm::vec4(0.0f, 0.0f, 0.0f, 0.0f),
				glm::vec4(1.0f, 0.5f, 0.0f, 1.0f),
				Size,
				Filter);

			Error += generate_mipmaps::test(gli::FORMAT_RGBA4_UNORM_PACK16,
				gli::packUnorm4x4(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)),
				gli::packUnorm4x4(glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)),
				Size,
				Filter);

			Error += generate_mipmaps::test(gli::FORMAT_RGBA8_UNORM_PACK8,
				glm::u8vec4(0, 0, 0, 0),
				glm::u8vec4(255, 127, 0, 255),
				Size,
				Filter);

			Error += generate_mipmaps::test(gli::FORMAT_RGBA8_SNORM_PACK8,
				glm::i8vec4(0, 0, 0, 0),
				glm::i8vec4(127, 63, 0, 1),
				Size,
				Filter);

			Error += generate_mipmaps::test(gli::FORMAT_RGB10A2_UNORM_PACK32,
				gli::packUnorm3x10_1x2(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)),
				gli::packUnorm3x10_1x2(glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)),
				Size,
				Filter);

			Error += generate_mipmaps::test(gli::FORMAT_RGB10A2_SNORM_PACK32,
				gli::packSnorm3x10_1x2(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)),
				gli::packSnorm3x10_1x2(glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)),
				Size,
				Filter);

			Error += generate_mipmaps::test(gli::FORMAT_RGB9E5_UFLOAT_PACK32,
				gli::packF3x9_E1x5(glm::vec3(0.0f, 0.0f, 0.0f)),
				gli::packF3x9_E1x5(glm::vec3(1.0f, 0.5f, 0.0f)),
				Size,
				Filter);
		}
	}

	return Error;
}

