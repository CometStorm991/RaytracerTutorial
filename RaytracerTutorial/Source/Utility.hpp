#pragma once

#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <numbers>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "Ray.hpp"

constexpr float degToRad(float degs)
{
	return degs * std::numbers::pi / 180.0f;
}

constexpr float radToDeg(float rads)
{
	return rads * 180.0f / std::numbers::pi;
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

	static const Interval empt, univ;
};