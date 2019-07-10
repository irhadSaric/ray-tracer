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
#include "plane.h"
#include "opencv2/opencv.hpp"
#include "polygon.h"
#include "disc.h"

using namespace std;
using namespace cv;

bool do_intersect(vec3 sphere_center, float sphere_radius, vec3 plane_point, vec3 plane_normal)
{
    float ro = dot(sphere_center - plane_point, plane_normal) / plane_normal.length();
    if(ro <= sphere_radius){
        return true;
    }
    return false;
}
//
//float hit_sphere(const vec3& center, float radius, const ray& r){
//    vec3 oc = r.origin() - center;
//    float a = dot(r.direction(),r.direction());
//    float b = 2.0*dot(oc,r.direction());
//    float c = dot(oc,oc)-radius*radius;
//    float discriminant = b*b-4*a*c;
//
//    if(discriminant<0){
//        return -1.0;
//    }else{
//        return (-b-sqrt(discriminant))/(2.0*a);
//    }
//
//
//}

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

class Projectile{
public:
    Projectile(vec3 p,vec3 v){
        position = p;
        velocity = v;
    }
    vec3 position;
    vec3 velocity;
};
class Environment{
public:
    vec3 gravity;
    vec3 wind;
    Environment(){}
    Environment(vec3 g,vec3 w){
        gravity = g;
        wind = w;
    }

};

Projectile tick(Environment env, Projectile proj){
    vec3 position = proj.position;
    vec3 velocity = proj.velocity;
    position = (proj.position + proj.velocity);
    velocity = (proj.velocity + env.gravity + env.wind);
    return  Projectile(position,velocity);
}

int main()
{

    ofstream myfile;
    int nx=400;
    int ny=200;
    int ns = 100;
    hitable *list[2];
    float R = 1;
    list[0] = new plane(vec3(0, 0, 0), vec3(0, 1, 0), new labertian(vec3(0.3, 0.5, 0.5)));
    hitable *world;
    vec3 lookfrom(0, 1, 30);
    vec3 lookat(0, 2, 0);
    float dist_to_focus = (lookfrom-lookat).length();
    float aperture = 0.5;
    camera cam(lookfrom, lookat,vec3(0,1,0),90, float(nx)/float(ny), aperture, dist_to_focus);
    ray r;
    vec3 p;
    vector<string> images;

    vec3 originalVelocity = vec3(1, 1.8, 0);
    Projectile projectile = Projectile(vec3(-50, 2, 0),originalVelocity);

    Environment e = Environment(vec3(0,-0.1,0),vec3(-0.01,0,0));
    for(int i = 0; i < 280; i++)
    {
        cout << i << endl;
        myfile.open(""+to_string(i)+".ppm");
        images.push_back(""+to_string(i)+".ppm");
        myfile<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
        list[1] = new sphere(projectile.position, R , new labertian(vec3(0, 0, 1)));
        if(do_intersect(projectile.position, R, vec3(0, 0, 0), vec3(0, 1, 0))){
            originalVelocity /= 1.2;
            projectile = Projectile(projectile.position, originalVelocity);
        }
        cout << projectile.position.x() << "," << projectile.position.y() << "," << projectile.position.z() << endl;
        world = new hitable_list(list, 2);

        for(int j=ny-1;j>=0;j--){
            for(int i=0;i<nx;i++){
                vec3 col(0, 0, 0);
                for (int s = 0; s < ns; s++){
                    float k = ((double) rand() / (RAND_MAX));
                    float t = ((double) rand() / (RAND_MAX));
                    float u = float(i + k)/ float(nx);
                    float v = float(j + t)/float(ny);
                    r = cam.get_ray(u, v);
                    p = r.point_at_parameter(2.0);
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
        projectile = tick(e, projectile);
        myfile.close();
    }

    VideoWriter video("kraj.avi", VideoWriter::fourcc('M','J','P','G'),20, Size(400,200));
    for(int i = 0; i < images.size(); i++){
        auto img = cv::imread(images[i]);
        video.write(img);
    }
    video.release();

    //-------------

    /*
    ofstream myfile;

    myfile.open("disc2.ppm");
    int nx=400;
    int ny=200;
    int ns = 100;
    myfile<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
    hitable *list[2];
    list[0] = new plane(vec3(0, 0, 0), vec3(1, 0, 0), new labertian(vec3(0.3, 0.5, 0.5)));
    list[1] = new disc(vec3(0, 0, 0), 20, vec3(0, 1, 0), new labertian(vec3(0.8, 0.1, 0.2)));
    hitable *world = new hitable_list(list, 2);
    vec3 lookfrom(30,15,30);
    vec3 lookat(0,0,0);
    float dist_to_focus = (lookfrom-lookat).length();
    float aperture = 0.5;
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
    return 0;*/
}
