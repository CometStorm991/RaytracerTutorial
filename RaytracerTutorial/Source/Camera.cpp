#pragma once

#include "Camera.hpp"

void Camera::render(const Hittable& world)
{
	init();

	for (uint32_t i = 0; i < imageHeight; i++)
	{
		for (uint32_t j = 0; j < imageWidth; j++)
		{
			float y = rayInitY + rayDeltaY * i;
			float x = rayInitX + rayDeltaX * j;
			float z = -1.0f;

			glm::vec3 viewportPos = glm::vec3(x, y, z);
			// std::cout << x << " " << y << " " << z << std::endl;
			Ray ray = Ray(pos, viewportPos - pos);

			glm::vec3 color = rayColor(ray, world);

			writeColor(imageData, glm::vec3(color.x, color.y, color.z));
		}

		uint32_t hundredth = static_cast<uint32_t>(imageHeight / 100.0f);
		if ((i + 1) % hundredth == 0)
		{
			std::cout << "Progress: " << std::fixed << std::setprecision(3) << static_cast<float>(i + 1) / imageHeight << std::endl;
		}
	}

	stbi_write_png("Renders/Render.png", imageWidth, imageHeight, 3, imageData.data(), 3 * imageWidth * sizeof(uint8_t));
}

void Camera::init()
{
	aspectRatio = static_cast<float>(imageWidth) / imageHeight;

	imageData.reserve(imageHeight * imageWidth * 3);

	const float viewportHeight = 2.0f;
	const float viewportWidth = viewportHeight * aspectRatio;

	rayDeltaX = viewportWidth / imageWidth;
	rayDeltaY = -viewportHeight / imageHeight;

	rayInitX = -viewportWidth / 2.0f + 0.5f * rayDeltaX;
	rayInitY = viewportHeight / 2.0f + 0.5f * rayDeltaY;
}

glm::vec3 Camera::rayColor(const Ray& ray, const Hittable& world) const
{
	HitRecord hitRec;
	bool hit = world.hit(ray, Interval{ 0.0f, std::numeric_limits<float>::infinity() }, hitRec);
	if (hit)
	{
		glm::vec3 norm = hitRec.norm;
		norm *= 0.5f;
		norm += 0.5f;
		return norm;
	}

	glm::vec3 unitDir = glm::normalize(ray.getDir());
	float a = 0.5f * (unitDir.y + 1.0f);

	return (1.0f - a) * glm::vec3(0.0f, 0.0f, 0.0f) + a * glm::vec3(0.5f, 0.7f, 1.0f);
}

void Camera::writeColor(std::vector<uint8_t>& imageData, glm::vec3 color)
{
	imageData.push_back(static_cast<uint8_t>(color.x * 255.0f));
	imageData.push_back(static_cast<uint8_t>(color.y * 255.0f));
	imageData.push_back(static_cast<uint8_t>(color.z * 255.0f));
}