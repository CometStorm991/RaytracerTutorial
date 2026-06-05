#pragma once

#include <STB/stb_image_write.h>

#include "Hittable.hpp"

class Camera
{
public:
	void render(const Hittable& world);

	uint32_t imageWidth = 2560;
	uint32_t imageHeight = 1440;
	float aspectRatio;

	glm::vec3 pos{0.0f, 0.0f, 0.0f};

	float rayDeltaX;
	float rayDeltaY;
	float rayInitX;
	float rayInitY;

	std::vector<uint8_t> imageData;
private:
	void init();
	glm::vec3 rayColor(const Ray& ray, const Hittable& world) const;
	void writeColor(std::vector<uint8_t>& imageData, glm::vec3 color);
};