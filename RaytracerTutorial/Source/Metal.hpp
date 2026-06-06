#pragma once

#include "Material.hpp"

class Metal : public Material
{
public:
	explicit Metal(const glm::vec3& albedo, float fuzzRad);
	bool scatter(const Ray& in, const HitRecord& hitRec, glm::vec3& att, Ray& scatt) const override;
private:
	glm::vec3 albedo;
	float fuzzRad;
};