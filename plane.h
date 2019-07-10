
#ifndef PLANEH
#define PLANEH

#include "ray.h"
#include <math.h>

class plane: public hitable  {
    public:
        plane() {}
        plane(vec3 point, vec3 normal, material *m) : point(point), normal(normal), mat_ptr(m){};
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
        vec3 compute_normal(const vec3& p) const;

        vec3 point;
        vec3 normal;
        material *mat_ptr;
};

bool plane::hit(const ray& r, float t_min, float t_max, hit_record& rec) const{
    float t = dot((point - r.origin()), normal) / dot(r.direction(), normal);

	if (t < t_max && t > t_min && t > 0) {
		rec.normal = normal;
		rec.p = r.origin() + t * r.direction();
		rec.t = t;
		rec.mat_ptr = mat_ptr;

		return (true);
	}

	return(false);
}

vec3 plane::compute_normal(const vec3& p) const{
    return normal;
}
#endif // planeH

