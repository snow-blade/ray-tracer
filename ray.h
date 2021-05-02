#ifndef RAYH
#define RAYH
#include "vec3.h"

class ray{
 public: 
    ray() {}
    ray(const vec3& v1, const vec3& v2) const {A=v1; B=v2;}
    vec3 origin() const {return A;}
    vec3 direction() const {return B;}
    vec3 point_at_parameter(float t ) const {return A + t*B; }
    
    vec3 A;
    vec3 B;
};

#endif // !RAYH
