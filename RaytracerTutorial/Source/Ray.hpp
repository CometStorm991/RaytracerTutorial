#pragma once

#include <glm/glm.hpp>

class Ray
{
private:
	glm::vec3 origin;
	glm::vec3 dir;
public:
	Ray();
	Ray(const glm::vec3& origin, const glm::vec3& dir);

	glm::vec3 at(float t) const;

	const glm::vec3& getOrigin() const;
	const glm::vec3& getDir() const;
};