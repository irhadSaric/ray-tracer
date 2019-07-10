#ifndef POLYGONH
#define POLYGONH

#include "ray.h"
#include <vector>
#include "segment.h"
#include <math.h>

using namespace std;

class poly: public hitable  {
    public:
        poly() {}
        poly(vector<segment> segments, material *m) : edges(segments), mat_ptr(m){};
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
        vec3 compute_normal(const vec3& p) const;
        bool is_in_poly(const vec3& point) const;

        vector<segment> edges;
        material *mat_ptr;
};

bool poly::is_in_poly(const vec3& point) const{
    vec3 most_left_point = edges[0].point1;
    for(int i = 0; i < edges.size(); i++){
        if(most_left_point.x() > edges[i].point1.x()){
            most_left_point = edges[i].point1;
        }
        if(most_left_point.x() > edges[i].point2.x()){
            most_left_point = edges[i].point2;
        }
    }

    vec3 most_up_point = edges[0].point1;
    for(int i = 0; i < edges.size(); i++){
        if(most_up_point.y() > edges[i].point1.y()){
            most_up_point = edges[i].point1;
        }
        if(most_up_point.y() > edges[i].point2.y()){
            most_up_point = edges[i].point2;
        }
    }

    segment s1(vec3(most_left_point.x() - 1, most_up_point.y(), 0), point);

    int counter = 0;
    for(int i = 0; i < edges.size(); i++){
        if(segment::segment_intersection(edges[i], s1)){
            counter += 1;
        }
    }

    return counter % 2;
}

bool poly::hit(const ray& r, float t_min, float t_max, hit_record& rec) const{
    vec3 point_on_plane = edges[0].point1;
    vec3 first_vec = edges[0].point2 - edges[0].point1;
    vec3 second_vec = edges[1].point2 - edges[0].point1;
    vec3 normal = cross(first_vec , second_vec);

    float t = dot((point_on_plane - r.origin()), normal) / dot(r.direction(), normal);

	if (t <= t_max && t >= t_min && t >=0) {
        vec3 intersection_point = r.origin() + t * r.direction();
        if(this->is_in_poly(intersection_point)){
            rec.normal = normal;
            rec.p = r.origin() + t * r.direction();
            rec.t = t;
            rec.mat_ptr = mat_ptr;

            return (true);
        }
	}

	return(false);
}

vec3 poly::compute_normal(const vec3& p) const{
    vec3 first_vec = edges[0].point2 - edges[0].point1;
    vec3 second_vec = edges[1].point2 - edges[0].point1;
    vec3 normal = cross(first_vec , second_vec);
    return normal;
}
#endif // POLYGONH

