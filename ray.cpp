#include <iostream>
#include "ray.hpp"
#include "float.h"
#include "hitablelist.hpp"
#include "sphere.hpp"
// float hit_sphere(const vec3& center,float radius,const ray &r){
//   vec3 oc = r.origin() - center;
//   float a = dot(r.direction(),r.direction());
//   float b = 2.0 * dot(oc,r.direction());
//   float c = dot(oc,oc) - radius*radius;
//   float delta = b*b - 4*a*c;
//   if (delta < 0){
//     return -1.0;
//   }
//   else {
//     return (-b - sqrt(delta)) / (2.0 * a);
//   }
// }


vec3 color(const ray &r,hitable *world){
   hit_record rec;
   if(world->hit(r,0.0,MAXFLOAT,rec)){
     return vec3(rec.normal.x()+1,rec.normal.y()+1,rec.normal.z()+1)*0.5;
   }
   else {
     vec3 unit_direction = unit_vector(r.direction());
     float t = 0.5 * (unit_direction.y()+1.0);
     return vec3(1.0,1.0,1.0)*(1.0-t) + vec3(0.5,0.7,1.0)*t;
   }
}

/* The ​color(ray)​ function linearly blends white and blue depending on the up/downess of the y
coordinate.
I first made it a unit vector so -1.0 < ​y​ < 1.0. I then did a standard graphics trick of
scaling that to 0.0 < t < 1.0. When t=1.0 I want blue.
 When t = 0.0 I want white. In between, I want a blend.
This forms a “linear blend”, or “linear interpolation”, or “lerp” for short, between two
things. A lerp is always of the form: ​blended_value = (1-t)*start_value + t*end_value, ​ with t
going from zero to one. In our case this produces:
*/

int main(){
  int nx = 200;
  int ny = 100;
  std::cout<< "P3\n" << nx << " " << ny << "\n255\n";
  vec3 lower_left_corner(-2.0,-1.0,-1.0);
  vec3 horizontal(4.0,0.0,0.0);
  vec3 vertical(0.0,2.0,0.0);
  vec3 origin(0.0,0.0,0.0);
  hitable *list[2];
  list[0] = new sphere(vec3(0,0,-1),0.5);
  list[1] = new sphere(vec3(0,-100.5,-1),100);
  hitable *world = new hitable_list(list,2); 
  for (int j= ny-1;j>=0;j--){
    for(int i= 0;i< nx ; i++){
      float u = float(i) / float(nx);
      float v = float(j) / float(ny);
      ray r(origin,lower_left_corner+horizontal*u+vertical*v);
      vec3 p = r.point_at_parameter(2.0);
      vec3 col = color(r,world);
      int ir = int(255.99*col[0]);
      int ig = int(255.99*col[1]);
      int ib = int(255.99*col[2]);
      std::cout<< ir << " "<< ig << " " << ib << "\n";
    }
  }
}
