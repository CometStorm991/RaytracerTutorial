#include "Ray.hpp"

Ray::Ray()
{

}

Ray::Ray(const glm::vec3& origin, const glm::vec3& dir)
	: origin(origin), dir(dir)
{

}

const glm::vec3& Ray::getOrigin() const
{
	return origin;
}

const glm::vec3& Ray::getDir() const
{
	return dir;
}


glm::vec3 Ray::at(float t) const
{
	return origin + t * dir;
}