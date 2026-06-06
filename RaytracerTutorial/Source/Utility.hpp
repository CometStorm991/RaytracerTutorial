#pragma once

#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <numbers>
#include <random>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

#include "Ray.hpp"

constexpr float degreesToRadians(float degs)
{
	return degs * std::numbers::pi / 180.0f;
}

constexpr float radiansToDegrees(float rads)
{
	return rads * 180.0f / std::numbers::pi;
}

inline float randomFloat()
{
	static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
	static std::mt19937 gen;
	return dist(gen);
}

inline double randomFloat(float min, float max)
{
	return min + (max - min) * randomFloat();
}

inline glm::vec3 randomVec3()
{
	return glm::vec3{ randomFloat(), randomFloat(), randomFloat() };
}

inline glm::vec3 randomVec3(float min, float max)
{
	return glm::vec3{ randomFloat(min, max), randomFloat(min, max), randomFloat(min, max) };
}

inline glm::vec3 randomUnitVec3()
{
	glm::vec3 point = randomVec3(-1.0f, 1.0f);
	float lenSquared = std::numeric_limits<float>::infinity();
	while (lenSquared < 1e-18f || lenSquared > 1.0f)
	{
		glm::vec3 point = randomVec3(-1.0f, 1.0f);
		lenSquared = point.x * point.x + point.y * point.y + point.z * point.z;
	}

	return point / std::sqrtf(lenSquared);
}

inline glm::vec3 randomOnHemisphere(const glm::vec3& norm)
{
	glm::vec3 point = randomUnitVec3();
	if (glm::dot(norm, point) > 0.0f)
	{
		return point;
	}
	else
	{
		return -point;
	}
}

inline bool nearZero(const glm::vec3& vec)
{
	float thresh = 0.001f;
	return std::fabs(vec.x) < thresh && std::fabs(vec.y) < thresh && std::fabs(vec.z) < thresh;
}

inline glm::vec3 refract(const glm::vec3& in, const glm::vec3 norm, float eta)
{
	float cosThet = std::fmin(glm::dot(-in, norm), 1.0f);
	glm::vec3 outPerp = eta * (in + cosThet * norm);
	glm::vec3 outPar = -std::sqrtf(std::fabs(1.0f - glm::length2(outPerp))) * norm;
	return outPerp + outPar;
}

class Interval
{
public:
	float min, max;
	
	explicit Interval() : min{ std::numeric_limits<float>::infinity() }, max{ -std::numeric_limits<float>::infinity() } {};
	explicit Interval(float min, float max) : min{ min }, max{ max } {};

	float size() const
	{
		return max - min;
	}

	float contains(float val) const
	{
		return val >= min && val <= max;
	}

	float surrounds(float val) const
	{
		return val > min && val < max;
	}

	float clamp(float val) const
	{
		if (val < min)
			return min;
		if (val > max)
			return max;
		return val;
	}

	static const Interval empt, univ;
};