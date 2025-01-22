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
		// moller trumbore ray intersection (reference scratchapixel & paper)
		vec3 v0v1 = v1 - v0;  // AB vector 
		vec3 v0v2 = v2 - v0;  // AC vector
		vec3 pvec = cross(r.direction(), (v0v2)); // normalize direction?
		float det = dot(v0v1, pvec);

		float invDet = 1 / det;
		vec3 T = r.origin() - v0;
		double u = dot(pvec, T) * invDet;  // divide by determinent part
		if (u < 0 || u > 1)
			return false;

		vec3 qvec = cross(T, v0v1);
		double v = dot(qvec, r.direction()) * invDet;
		if (v < 0 || u + v > 1)
			return false;

		return true;


#ifdef CULLING
		// determinant negative is back facing triangle
		// if(det < kEpsilon) return false;
# else
		// determinant close to zero, ray and triangle are parrallel
		// if(det < kEpsilon) return false;
#endif
	}

private:
	vec3 v0;
	vec3 v1;
	vec3 v2;
};
