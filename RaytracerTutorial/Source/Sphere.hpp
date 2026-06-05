#pragma once

#include "Hittable.hpp"
#include "Utility.hpp"

class Sphere : public Hittable
{
public:
	explicit Sphere(glm::vec3 cent, float rad);
	bool hit(const Ray& ray, Interval rayTime, HitRecord& hitRec) const override;
private:
	glm::vec3 cent;
	float rad;
};