#ifndef DISCH
#define DISCH

#include "ray.h"
#include <math.h>

class disc: public hitable  {
    public:
        disc() {}
        disc(vec3 center, float radius, vec3 normal, material *m) : center(center), normal(normal), radius(radius), mat_ptr(m){};
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
        vec3 compute_normal(const vec3& p) const;

        vec3 center;
        float radius;
        vec3 normal;
        material *mat_ptr;
};

bool disc::hit(const ray& r, float t_min, float t_max, hit_record& rec) const{
    float t = dot((center - r.origin()), normal) / dot(r.direction(), normal);

	if (t < t_max && t > t_min) {
        vec3 intersection_point = r.origin() + t * r.direction();
        if(dot(intersection_point - center, intersection_point - center) <= radius*radius){
            rec.normal = normal;
            rec.p = r.origin() + t * r.direction();
            rec.t = t;
            rec.mat_ptr = mat_ptr;

            return (true);
        }
	}

	return(false);
}

vec3 disc::compute_normal(const vec3& p) const{
    return normal;
}

#endif // DISCH
