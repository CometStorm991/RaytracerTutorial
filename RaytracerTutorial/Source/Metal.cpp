#include "Metal.hpp"

Metal::Metal(const glm::vec3& albedo, float fuzzRad)
	: albedo{ albedo }, fuzzRad{ fuzzRad > 1.0f ? 1.0f : fuzzRad }
{

}

bool Metal::scatter(const Ray& in, const HitRecord& hitRec, glm::vec3& att, Ray& scatt) const
{
	glm::vec3 dir = glm::reflect(in.getDir(), hitRec.norm);
	dir = glm::normalize(dir) + fuzzRad * randomUnitVec3();
	scatt = Ray{ hitRec.point, dir };
	att = albedo;
	return glm::dot(scatt.getDir(), hitRec.norm) > 0.0f;
}