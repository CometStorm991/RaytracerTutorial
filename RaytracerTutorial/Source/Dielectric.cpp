#include "Dielectric.hpp"

Dielectric::Dielectric(float refInd)
	: refInd{ refInd }
{
	
}

bool Dielectric::scatter(const Ray& in, const HitRecord& hitRec, glm::vec3& att, Ray& scatt) const
{
	att = glm::vec3{ 1.0f, 1.0f, 1.0f };

	float newRefInd = hitRec.frontFace ? 1.0f / refInd : refInd;

	glm::vec3 unitDir = glm::normalize(in.getDir());
	float cosThet = std::fmin(glm::dot(-unitDir, hitRec.norm), 1.0f);
	float sinThet = std::sqrtf(1.0f - cosThet * cosThet);

	glm::vec3 scattDir;
	if (newRefInd * sinThet > 1.0f || reflectance(cosThet, newRefInd) > randomFloat())
	{
		// Can't refract, must reflect
		scattDir = glm::reflect(unitDir, hitRec.norm);
	}
	else
	{
		scattDir = refract(unitDir, hitRec.norm, newRefInd);
	}

	scatt = Ray{ hitRec.point, scattDir };
	return true;
}

float Dielectric::reflectance(float cos, float refInd) const
{
	float r0 = (1.0f - refInd) / (1.0f + refInd);
	r0 *= r0;
	return r0 + (1.0f - r0) * std::powf(1.0f - cos, 5.0f);
}