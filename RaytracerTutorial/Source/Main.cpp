#include <cstdint>
#include <iostream>
#include <vector>

#include <STB/stb_image_write.h>

int main()
{
	const unsigned int imageWidth = 1920;
	const unsigned int imageHeight = 1080;

	std::vector<uint8_t> imageData;

	for (unsigned int i = 0; i < imageHeight; i++)
	{
		for (unsigned int j = 0; j < imageWidth; j++)
		{
			float r = static_cast<float>(i) / (imageHeight - 1);
			float g = static_cast<float>(j) / (imageWidth - 1);
			float b = 0.0f;

			imageData.push_back(static_cast<uint8_t>(r * 256.0f));
			imageData.push_back(static_cast<uint8_t>(g * 256.0f));
			imageData.push_back(static_cast<uint8_t>(b * 256.0f));
		}
	}

	stbi_write_png("Renders/Render.png", imageWidth, imageHeight, 3, imageData.data(), 3 * imageWidth * sizeof(uint8_t));

	return 0;
}