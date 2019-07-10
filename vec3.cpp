#include "vec3.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>

extern inline std::istream& operator>>(std::istream &is,vec3 &t);
extern inline std::ostream& operator<<(std::ostream &os, const vec3 &t);
extern inline vec3 operator+(const vec3 &v1, const vec3 &v2);
extern inline vec3 operator-(const vec3 &v1, const vec3 &v2);
extern inline vec3 operator*(const vec3 &v1, const vec3 &v2);
extern inline vec3 operator/(const vec3 &v1, const vec3 &v2);
extern inline vec3 operator*(float t, const vec3 &v);
extern inline vec3 operator/(vec3 v, float t);
extern inline vec3 operator*(const vec3 v, float t);
extern inline float dot(const vec3 &v1, const vec3 &v2);
extern inline vec3 cross(const vec3 & v1, const vec3 &v2);
//extern inline vec3& vec3::operator+=(const vec3 &v);

extern inline vec3 unit_vector(vec3 v);
extern inline void test();
