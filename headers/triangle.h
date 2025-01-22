#include "hittable.h"
#include "rtweekend.h"


class triangle : hittable {
public:
	triangle(vec3 v0, vec3 v1, vec3 v2) {
		this->v0 = v0;
		this->v1 = v1;
		this->v2 = v2;
	}

	bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
		// moller trumbore ray intersection
		vec3 v0v1 = v1 - v0;  // AB vector 
		vec3 v0v2 = v2 - v0;  // AC vector
		vec3 pvec = r.direction().cross(v0v2);
	}

private:
	vec3 v0;
	vec3 v1;
	vec3 v2;
};
