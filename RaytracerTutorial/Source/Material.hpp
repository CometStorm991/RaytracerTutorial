#pragma once

#include "Hittable.hpp"
#include "Utility.hpp"

class Material
{
public:
	virtual ~Material() = default;
	virtual bool scatter(const Ray& in, const HitRecord& hitRec, glm::vec3& att, Ray& scatt) const
	{
		return false;
	};
};