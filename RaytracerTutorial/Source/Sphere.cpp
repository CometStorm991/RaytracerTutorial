#include "Sphere.hpp"

Sphere::Sphere(glm::vec3 cent, float rad, std::shared_ptr<Material> mat)
	: cent{ cent }, rad{ rad }, mat{ mat }
{
}

bool Sphere::hit(const Ray& ray, Interval rayTime, HitRecord& hitRec) const
{
	const glm::vec3& q = ray.getOrigin();
	const glm::vec3& d = ray.getDir();

	float a = glm::dot(d, d);
	float h = glm::dot(d, cent - q);
	float c = glm::dot(cent - q, cent - q) - rad * rad;

	float discriminant = h * h - a * c;
	if (discriminant < 0)
	{
		return false;
	}

	float sqrtDisc = std::sqrtf(discriminant);
	float time = (h - sqrtDisc) / a;
	if (!rayTime.surrounds(time))
	{
		time = (h + sqrtDisc) / a;
		if (!rayTime.surrounds(time))
		{
			return false;
		}
	}

	hitRec.time = time;
	hitRec.point = ray.at(time);
	glm::vec3 outNorm = (hitRec.point - cent) / rad;
	hitRec.setFaceNormal(ray, outNorm);
	hitRec.mat = mat;

	return true;
}