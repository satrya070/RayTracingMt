#include "hittable.h"
#include "rtweekend.h"

#define CULLING

constexpr float Epsilon = 1e-8;


class triangle : public hittable {
public:
	triangle(vec3 v0, vec3 v1, vec3 v2, shared_ptr<material> mat) : v0(v0), v1(v1), v2(v2), mat(mat) {
	}

	bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
		// moller trumbore ray intersection (reference scratchapixel & paper)
		vec3 v0v1 = v1 - v0;  // AB vector 
		vec3 v0v2 = v2 - v0;  // AC vector
		vec3 pvec = cross(r.direction(), (v0v2)); // normalize direction?
		float det = dot(v0v1, pvec);

#ifdef CULLING
		// determinant negative is back facing triangle
		if(det < Epsilon) return false;
# else
		// determinant close to zero, ray and triangle are parrallel
		if(fabs(det) < Epsilon) return false;
#endif
		float invDet = 1 / det;
		vec3 T = r.origin() - v0;
		double u = dot(pvec, T) * invDet;  // divide by determinent part
		if (u < 0 || u > 1)
			return false;

		vec3 qvec = cross(T, v0v1);
		double v = dot(qvec, r.direction()) * invDet;
		if (v < 0 || u + v > 1)
			return false;

		double t = dot(v0v2, qvec) * invDet;

		if (t > ray_t.max)
			// already hit an closer by object
			return false;

		// update all param references
		rec.t = t;
		rec.p = r.at(rec.t);
		vec3 outward_normal = unit_vector(cross(v0v1, v0v2)); //unit_vector(cross(v0v1, v0v2));

		rec.set_face_normal(r, outward_normal);
		rec.mat = mat;


		return true;
	}

private:
	vec3 v0;
	vec3 v1;
	vec3 v2;
	shared_ptr<material> mat;
};
