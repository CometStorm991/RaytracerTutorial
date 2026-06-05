#pragma once

#include "Hittable.hpp"

class HittableList : public Hittable
{
public:
	explicit HittableList();

	void clear();
	void add(std::shared_ptr<Hittable> obj);
	bool hit(const Ray& ray, Interval rayTime, HitRecord& hitRec) const override;
private:
	std::vector<std::shared_ptr<Hittable>> objs;
};