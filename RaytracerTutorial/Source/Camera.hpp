#pragma once

#include <STB/stb_image_write.h>

#include "Hittable.hpp"
#include "Material.hpp"

class Camera
{
public:
	void render(const Hittable& world);
	void accumulate(const Hittable& world);

	uint32_t imageWidth = 2560;
	uint32_t imageHeight = 1440;
	float aspectRatio;

	uint32_t sampsPerPix = 10;
	uint32_t maxDepth = 50;

	float vertFov = 90.0f;
	glm::vec3 lookFrom = glm::vec3{ 0.0f, 0.0f, 0.0f };
	glm::vec3 lookAt = glm::vec3{ 0.0f, 0.0f, -1.0f };
	glm::vec3 viewUp = glm::vec3{ 0.0f, 1.0f, 0.0f };
	float defocAng = 0.0f;
	float focDist = 10.0f;

	glm::vec3 pos{ 0.0f, 0.0f, 0.0f };

	glm::vec3 rayDeltU;
	glm::vec3 rayDeltV;

	glm::vec3 pix00Loc;

	std::vector<uint8_t> imageData;
private:
	void init();
	Ray getRay(uint32_t i, uint32_t j) const;
	glm::vec3 sampleSquare() const;
	glm::vec3 defocusDiskSample() const;
	glm::vec3 rayColor(const Ray& ray, uint32_t depth, const Hittable& world) const;
	void writeColor(std::vector<uint8_t>& imageData, const glm::vec3& color);
	constexpr float linearToGamma(float val);

	float pixSampsScale = 1.0f / sampsPerPix;

	glm::vec3 u, v, w;
	glm::vec3 defocDiskU;
	glm::vec3 defocDiskV;
};