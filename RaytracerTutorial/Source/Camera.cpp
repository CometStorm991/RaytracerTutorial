#pragma once

#include "Camera.hpp"

void Camera::render(const Hittable& world)
{
	init();

	for (uint32_t i = 0; i < imageHeight; i++)
	{
		for (uint32_t j = 0; j < imageWidth; j++)
		{
			glm::vec3 pixCol{ 0.0f, 0.0f, 0.0f };
			for (uint32_t k = 0; k < sampsPerPix; k++)
			{
				Ray ray = getRay(i, j);
				pixCol += rayColor(ray, maxDepth, world);
			}
			pixCol *= pixSampsScale;

			writeColor(imageData, pixCol);
		}

		uint32_t hundredth = static_cast<uint32_t>(std::max(imageHeight / 100.0f, 1.0f));
		if ((i + 1) % hundredth == 0)
		{
			std::cout << "Progress: " << std::fixed << std::setprecision(3) << static_cast<float>(i + 1) / imageHeight << std::endl;
		}
	}

	stbi_write_png("Renders/Render.png", imageWidth, imageHeight, 3, imageData.data(), 3 * imageWidth * sizeof(uint8_t));
}

void Camera::accumulate(const Hittable& world)
{
	init();

	uint32_t totalSamps = 0;
	std::vector<float> sampData;
	sampData.reserve(imageHeight * imageWidth * 3);

	for (uint32_t i = 0; i < imageHeight; i++)
	{
		for (uint32_t j = 0; j < imageWidth; j++)
		{
			for (uint32_t k = 0; k < 3; k++)
			{
				sampData.push_back(0.0f);
			}
		}
	}

	while (true)
	{
		for (uint32_t it = 0;; it++)
		{
			uint32_t sampsPerIt = it == 0 ? 1 : static_cast<uint32_t>(std::powf(2, it - 1));

			for (uint32_t k = 0; k < sampsPerIt; k++)
			{
				for (uint32_t i = 0; i < imageHeight; i++)
				{
					for (uint32_t j = 0; j < imageWidth; j++)
					{
						Ray ray = getRay(i, j);
						glm::vec3 pixCol = rayColor(ray, maxDepth, world);

						float& sampR = sampData[3 * (i * imageWidth + j) + 0];
						float& sampG = sampData[3 * (i * imageWidth + j) + 1];
						float& sampB = sampData[3 * (i * imageWidth + j) + 2];

						sampR = (sampR * totalSamps + pixCol.r) / (totalSamps + 1.0f);
						sampG = (sampG * totalSamps + pixCol.g) / (totalSamps + 1.0f);
						sampB = (sampB * totalSamps + pixCol.b) / (totalSamps + 1.0f);
					}
				}

				totalSamps++;
			}

			imageData.clear();
			for (uint32_t i = 0; i < imageHeight; i++)
			{
				for (uint32_t j = 0; j < imageWidth; j++)
				{
					glm::vec3 color = reinterpret_cast<glm::vec3&>(sampData.data()[3 * (i * imageWidth + j)]);
					writeColor(imageData, color);
				}
			}

			stbi_write_png(("Renders/Render" + std::to_string(totalSamps) + ".png").c_str(), imageWidth, imageHeight, 3, imageData.data(), 3 * imageWidth * sizeof(uint8_t));
			std::cout << "Iteration " << it << " done\n";
		}
	}
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

Ray Camera::getRay(uint32_t i, uint32_t j) const
{
	glm::vec3 offs = sampleSquare();
	glm::vec3 pixSamp{ rayInitX + (j + offs.x) * rayDeltaX, rayInitY + (i + offs.y) * rayDeltaY, pos.z - 1.0f };

	return Ray{ pos, pixSamp - pos };
}

glm::vec3 Camera::sampleSquare() const
{
	return glm::vec3{ randomFloat() - 0.5f, randomFloat() - 0.5f, 0.0f };
}

glm::vec3 Camera::rayColor(const Ray& ray, uint32_t depth, const Hittable& world) const
{
	if (depth <= 0)
	{
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}

	HitRecord hitRec;
	bool hit = world.hit(ray, Interval{ 0.001f, std::numeric_limits<float>::infinity() }, hitRec);
	if (hit)
	{
		glm::vec3 att;
		Ray scattDir;
		if (hitRec.mat->scatter(ray, hitRec, att, scattDir))
		{
			return att * rayColor(scattDir, depth - 1, world);
		}
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}

	glm::vec3 unitDir = glm::normalize(ray.getDir());
	float a = 0.5f * (unitDir.y + 1.0f);

	return (1.0f - a) * glm::vec3(0.0f, 0.0f, 0.0f) + a * glm::vec3(0.5f, 0.7f, 1.0f);
}

void Camera::writeColor(std::vector<uint8_t>& imageData, const glm::vec3& color)
{
	static const Interval intens{0.0f, 0.999f};
	
	const float r = intens.clamp(linearToGamma(color.r));
	const float g = intens.clamp(linearToGamma(color.g));
	const float b = intens.clamp(linearToGamma(color.b));

	imageData.push_back(static_cast<uint8_t>(256.0f * r));
	imageData.push_back(static_cast<uint8_t>(256.0f * g));
	imageData.push_back(static_cast<uint8_t>(256.0f * b));
}

constexpr float Camera::linearToGamma(float val)
{
	if (val > 0.0f)
	{
		return std::sqrt(val);
	}
	return 0.0f;
}