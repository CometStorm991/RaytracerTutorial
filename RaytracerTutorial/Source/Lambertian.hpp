#pragma once

#include "Material.hpp"
#include "Utility.hpp"

class Lambertian : public Material
{
public:
	explicit Lambertian(const glm::vec3& albedo);
	bool scatter(const Ray& in, const HitRecord& hitRec, glm::vec3& att, Ray& scatt) const override;
private:
	glm::vec3 albedo;
};