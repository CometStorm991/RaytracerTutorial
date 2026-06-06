#pragma once

#include "Utility.hpp"

class Material;
struct HitRecord
{
	glm::vec3 point;
	glm::vec3 norm;
	std::shared_ptr<Material> mat;
	float time;
	bool frontFace;

	void setFaceNormal(const Ray& ray, const glm::vec3& outNorm)
	{
		frontFace = glm::dot(ray.getDir(), outNorm) < 0.0f;
		norm = frontFace ? outNorm : -outNorm;
	}
};

class Hittable
{
public:
	virtual ~Hittable() = default;
	virtual bool hit(const Ray& ray, Interval rayTime, HitRecord& hitRec) const = 0;
};