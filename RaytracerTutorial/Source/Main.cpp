#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

#include <STB/stb_image_write.h>
#include <glm/glm.hpp>

#include "Ray.hpp"

void writeColor(std::vector<uint8_t>& imageData, glm::vec3 color)
{
	imageData.push_back(static_cast<uint8_t>(color.x * 255.0f));
	imageData.push_back(static_cast<uint8_t>(color.y * 255.0f));
	imageData.push_back(static_cast<uint8_t>(color.z * 255.0f));
}

bool hitSphere(const Ray& ray)
{
	glm::vec3 center = glm::vec3(0, 0, -3);
	float radius = 1.0f;

	const glm::vec3& q = ray.getOrigin();
	const glm::vec3& d = ray.getDir();
	
	float a = glm::dot(d, d);
	float b = glm::dot(-2.0f * d, center - q);
	float c = glm::dot(center - q, center - q) - radius * radius;

	float discriminant = b * b - 4.0f * a * c;
	// 36 - 4 * 1 * 8
	return discriminant >= 0;
}

glm::vec3 rayColor(const Ray& ray)
{
	if (hitSphere(ray))
	{
		return glm::vec3(0.0f, 0.5f, 1.0f);
	}

	glm::vec3 unitDirection = glm::normalize(ray.getDir());
	float a = 0.5f * (unitDirection.y + 1.0f);

	return (1.0f - a) * glm::vec3(0.0f, 0.0f, 0.0f) + a * glm::vec3(0.5f, 0.7f, 1.0f);
}

int main()
{
	const uint32_t imageWidth = 2560;
	const uint32_t imageHeight = 1600;
	const float aspectRatio = static_cast<float>(imageWidth) / imageHeight;
	
	const float viewportHeight = 2.0f;
	const float viewportWidth = viewportHeight * aspectRatio;

	const float rayDeltaX = viewportWidth / imageWidth;
	const float rayDeltaY = -viewportHeight / imageHeight;
	// glm::vec2 rayDelta = glm::vec2(rayDeltaX, rayDeltaY);
	const float rayInitX = -viewportWidth / 2.0f + 0.5f * rayDeltaX;
	const float rayInitY = viewportHeight / 2.0f + 0.5f * rayDeltaY;

	glm::vec3 cameraPos = glm::vec3(0, 0, 0);

	std::vector<uint8_t> imageData;

	for (uint32_t i = 0; i < imageHeight; i++)
	{
		for (uint32_t j = 0; j < imageWidth; j++)
		{
			float y = rayInitY + rayDeltaY * i;
			float x = rayInitX + rayDeltaX * j;
			float z = -1.0f;

			glm::vec3 viewportPos = glm::vec3(x, y, z);
			// std::cout << x << " " << y << " " << z << std::endl;
			Ray ray = Ray(cameraPos, viewportPos - cameraPos);

			glm::vec3 color = rayColor(ray);

			writeColor(imageData, glm::vec3(color.x, color.y, color.z));
		}

		uint32_t hundredth = static_cast<uint32_t>(imageHeight / 100.0f);
		if ((i + 1) % hundredth == 0)
		{
			std::cout << "Progress: " << static_cast<float>(i + 1) / imageHeight << std::endl;
		}
	}

	stbi_write_png("Renders/Render.png", imageWidth, imageHeight, 3, imageData.data(), 3 * imageWidth * sizeof(uint8_t));

	return 0;
}