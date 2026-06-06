#pragma once

#include "Material.hpp"
#include "Utility.hpp"

class Dielectric : public Material
{
public:
	explicit Dielectric(float refInd);
	bool scatter(const Ray& in, const HitRecord& hitRec, glm::vec3& att, Ray& scatt) const override;
private:
	float refInd; // Reflection index

	float reflectance(float cos, float refInd) const;
};