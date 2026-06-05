#include "HittableList.hpp"

HittableList::HittableList()
	: objs{}
{

}

void HittableList::clear()
{
	objs.clear();
}

void HittableList::add(std::shared_ptr<Hittable> obj)
{
	objs.push_back(obj);
}

bool HittableList::hit(const Ray& ray, Interval rayTime, HitRecord& hitRec) const
{
	HitRecord tempRec;
	float closestTime = rayTime.max;
	bool hitAny = false;
	
	for (std::shared_ptr<Hittable> obj : objs)
	{
		if (obj->hit(ray, Interval{rayTime.min, closestTime}, tempRec))
		{
			hitAny = true;
			closestTime = tempRec.time;
			hitRec = tempRec;
		}
	}

	return hitAny;
}