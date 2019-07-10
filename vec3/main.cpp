#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "vec3.h"
#include "ray.h"
#include <fstream>
#include "hitable.h"
#include <float.h>
#include "hitablelist.h"
#include "sphere.h"
#include "camera.h"
#include "materija.h"

using namespace std;
/*
class vec3{
public:
    float e[3];
    vec3(){}
    vec3(float e0,float e1,float e2){e[0]=e0;e[1]=e1;e[2]=e2; }
    inline float x()const{return e[0];}
    inline float y()const{return e[1];}
    inline float z()const{return e[2];}
    inline float r()const{return e[0];}
    inline float g()const{return e[1];}
    inline float b()const{return e[2];}

    inline const vec3& operator+()const{return *this;}
    inline vec3 operator-()const{return vec3(-e[0],-e[1],-e[2]);}
    inline float operator[](int i)const{return e[i];}
    inline float& operator[](int i){return e[i];}

    inline vec3& operator+=(const vec3 &v2);
    inline vec3& operator-=(const vec3 &v2);
    inline vec3& operator*=(const vec3 &v2);
    inline vec3& operator/=(const vec3 &v2);
    inline vec3& operator*=(const float t);
    inline vec3& operator/=(const float t);

    inline float length() const{
        return sqrt(e[0]*e[0]+e[1]*e[1]+e[2]*e[2]);
    }
    inline float squared_length() const{
        return e[0]*e[0]+e[1]*e[1]+e[2]*e[2];
    }
    inline void make_unit_vector(){
        float k=1.0/sqrt(e[0]*e[0]+e[1]*e[1]+e[2]*e[2]);
        e[0]*=k;e[1]*=k;e[2]*=k;
    }



};
inline std::istream& operator>>(std::istream &is,vec3 &t){
        is>> t.e[0]>> t.e[1] >> t.e[2];
        return is;
    }
    inline std::ostream& operator<<(std::ostream &os, const vec3 &t){
        os<< t.e[0]<<" "<<t.e[1]<<" "<<t.e[2];
        return os;
    }

    inline vec3 operator+(const vec3 &v1, const vec3 &v2){
        return vec3(v1.e[0]+v2.e[0],v1.e[1]+v2.e[1],v1.e[2]+v2.e[2]);
    }
    inline vec3 operator-(const vec3 &v1, const vec3 &v2){
        return vec3(v1.e[0]-v2.e[0],v1.e[1]-v2.e[1],v1.e[2]-v2.e[2]);
    }
    inline vec3 operator*(const vec3 &v1, const vec3 &v2){
        return vec3(v1.e[0]*v2.e[0],v1.e[1]*v2.e[1],v1.e[2]*v2.e[2]);
    }
    inline vec3 operator/(const vec3 &v1, const vec3 &v2){
        return vec3(v1.e[0]/v2.e[0],v1.e[1]/v2.e[1],v1.e[2]/v2.e[2]);
    }
    inline vec3 operator*(float t, const vec3 &v){
        return vec3(t*v.e[0],t*v.e[1],t*v.e[2]);
    }
    inline vec3 operator/(vec3 v, float t){
        return vec3(v.e[0]/t,v.e[1]/t,v.e[2]/t);
    }
    inline vec3 operator*(const vec3 v, float t){
        return vec3(v.e[0]*t,v.e[1]*t,v.e[2]*t);
    }
    inline float dot(const vec3 &v1, const vec3 &v2) {
        return v1.e[0] *v2.e[0] + v1.e[1] *v2.e[1]  + v1.e[2] *v2.e[2];
    }
    inline vec3 cross(const vec3 & v1, const vec3 &v2){
        return vec3((v1.e[1]*v2.e[2]-v1.e[2]*v2.e[1]),(-(v1.e[0]*v2.e[2]-v1.e[2]*v2.e[0])),
                    (v1.e[0]*v2.e[1]-v1.e[1]*v2.e[0]));
    }
    inline vec3& vec3::operator+=(const vec3 &v){
        e[0]  += v.e[0];
        e[1]  += v.e[1];
        e[2]  += v.e[2];
        return *this;
    }
    inline vec3& vec3::operator*=(const vec3 &v){
        e[0]  *= v.e[0];
        e[1]  *= v.e[1];
        e[2]  *= v.e[2];
        return *this;
    }

    inline vec3& vec3::operator/=(const vec3 &v){
        e[0]  /= v.e[0];
        e[1]  /= v.e[1];
        e[2]  /= v.e[2];
        return *this;
    }

    inline vec3& vec3::operator-=(const vec3& v) {
        e[0]  -= v.e[0];
        e[1]  -= v.e[1];
        e[2]  -= v.e[2];
        return *this;
    }

    inline vec3& vec3::operator*=(const float t) {
        e[0]  *= t;
        e[1]  *= t;
        e[2]  *= t;
        return *this;
    }

    inline vec3& vec3::operator/=(const float t) {
        float k = 1.0/t;

        e[0]  *= k;
        e[1]  *= k;
        e[2]  *= k;
        return *this;
    }

    inline vec3 unit_vector(vec3 v) {
        return v / v.length();
    }
*/
class Projectile{
public:
    //Projectile(){}

    Projectile(vec3 p,vec3 v){
        position = p;
        velocity = v;
    }
    vec3 position;
    vec3 velocity;
};
class Envirenment{
public:
    vec3 gravity;
    vec3 wind;
    Envirenment(){}
    Envirenment(vec3 g,vec3 w){
        gravity = g;
        wind = w;
    }

};

Projectile tick(Envirenment env, Projectile proj){
    vec3 position = proj.position;
    vec3 velocity = proj.velocity;
    position += (proj.position+proj.velocity);
    velocity += (proj.velocity + env.gravity + env.wind);
    return  Projectile(position,velocity);
}

/*vec3 color(const ray& r){

    vec3 unit_direction = unit_vector(r.direction());
    float t = abs(unit_direction.y());
    return (1.0-t)*vec3(1.0,1.0,1.0)+t*vec3(0.5,0.7,1.0);

}*/

float hit_sphere(const vec3& center, float radius, const ray& r){
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(),r.direction());
    float b = 2.0*dot(oc,r.direction());
    float c = dot(oc,oc)-radius*radius;
    float discriminant = b*b-4*a*c;

    if(discriminant<0){
        return -1.0;
    }else{
        return (-b-sqrt(discriminant))/(2.0*a);
    }


}
/*vec3 color(const ray& r){
    /*if (hit_sphere(vec3(0,0,-1),0.5,r))
        return vec3(1,0,0);
    if(hit_sphere(vec3(0,-1,-1),0.5,r))
        return vec3(0,1,0);

    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y()+1.0);
    return (1.0-t)*vec3(1.0,1.0,1.0)+t*vec3(0.5,0.7,1.0);*/

    /*float t = hit_sphere(vec3(0,0,-1),0.5,r);
    if(t>0.0){
        vec3 N = unit_vector(r.point_at_parameter(t)-vec3(0,0,-1));
        //return 0.5*vec3(N.x()+1,N.y()+1,N.z()+1);
        return vec3(fabs(N.x()),fabs(N.y()),fabs(N.z()));
    }
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5 * (unit_direction.y()+1.0);
    return (1.0-t)*vec3(1.0,1.0,1.0)+t*vec3(0.5,0.7,1.0);

}
vec3 random_in_unit_sphere(){
    vec3 p;
    do{
        /*float k = ((dousble) rand() / (RAND_MAX));
        #float t = ((double) rand() / (RAND_MAX));
        #float c = ((double) rand() / (RAND_MAX));
        p = 2.0*vec3(((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX)), ((double) rand() / (RAND_MAX))) - vec3(1, 1, 1);
    }
        while (p.squared_length() >= 1.0);
    return p;
}*/
/*
vec3 color(const ray& r, hitable *world) {
    hit_record rec;
    if(world->hit(r, 0.001, FLT_MAX, rec)) {

        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5*color(ray(rec.p, target-rec.p), world);
    }
    else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y()+1.0);
        return (1.0-t)*vec3(1.0,1.0,1.0)+t*vec3(0.5,0.7,1.0);
    }
}
*/
vec3 color(const ray& r, hitable *world, int depth) {
    hit_record rec;
    if(world->hit(r, 0.001, FLT_MAX, rec)) {
        ray scattered;
        vec3 attenuation;
        if( depth < 10 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)){
            return attenuation * color(scattered, world, depth +1);
        }
        else{
            return vec3(0,0,0);
    }
    }
    else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y()+1.0);
        return (1.0-t)*vec3(1.0,1.0,1.0)+t*vec3(0.5,0.7,1.0);
    }
}


int main()
{
    /*vec3 v1 = vec3(1,1,1);
    vec3 v2 = vec3(1,2,1);
    test();

    vec3 v3 = v1+v2;


    vec3 temp = cross(v1,v2);
    float x = dot(v1,v2);

    cout <<temp<<endl;
    cout<<x;*/

    /*Projectile p = Projectile(vec3(0,1,0),unit_vector(vec3(1,1,0)));
    Envirenment e = Envirenment(vec3(0,-0.1,0),vec3(-0.01,0,0));

    Projectile temp = tick(e,p);



    cout << temp.position<<temp.velocity;*/

    ofstream myfile;
    myfile.open("zadnje_vjezbe_9.ppm");
/// titlt shift ideja za projekat
    int nx=400;
    int ny=200;
    int ns = 100;
    myfile<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
    hitable *list[2];
    float R = cos(3.14/4);
    list[0] = new sphere(vec3(-R, 0, -1), R , new labertian(vec3(0, 0, 1)));
    list[1] = new sphere(vec3(R, 0, -1), R, new labertian(vec3(1, 0, 0)));
    hitable *world = new hitable_list(list, 2);
    vec3 lookfrom(3,3,2);
    vec3 lookat(0,0,1);
    float dist_to_focus = (lookfrom-lookat).length();
    float aperture = 2.0;
    camera cam(lookfrom, lookat,vec3(0,1,0),90, float(nx)/float(ny), aperture, dist_to_focus);
    for(int j=ny-1;j>=0;j--){
        for(int i=0;i<nx;i++){
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++){
                float k = ((double) rand() / (RAND_MAX));
                float t = ((double) rand() / (RAND_MAX));
                float u = float(i + k)/ float(nx);
                float v = float(j + t)/float(ny);
                ray r = cam.get_ray(u, v);
                vec3 p = r.point_at_parameter(2.0);
                col += color(r, world, 0);
            }
            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            int ir = int(255.99*col[0]);
            int iq = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            myfile<<ir<<" "<<iq<<" "<<ib<<"\n";
        }
    }
    myfile.close();
    return 0;
}
