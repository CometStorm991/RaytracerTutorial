#include "Lambertian.hpp"

Lambertian::Lambertian(const glm::vec3& albedo)
	: albedo{ albedo }
{
	
}

bool Lambertian::scatter(const Ray& in, const HitRecord& hitRec, glm::vec3& att, Ray& scatt) const
{
	glm::vec3 dir = hitRec.norm + randomUnitVec3();
	if (nearZero(dir))
	{
		dir = hitRec.norm;
	}

	scatt = Ray{ hitRec.point, dir };
	att = albedo;
	return true;
}