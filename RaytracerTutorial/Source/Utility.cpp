#include "Utility.hpp"

const Interval Interval::empt = Interval{ std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity() };
const Interval Interval::univ = Interval{ -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity() };