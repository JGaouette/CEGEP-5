#include "Vector3d.hpp"

class Collider{
public:
    Collider() {

    };

    Vector3d isColliding(Vector3d position, Vector3d speed, Vector3d t0, Vector3d t1, Vector3d t2, Vector3d normal){
        //Check if is parallel
        if(!(speed % normal)) {
            return {0, 0, 0};
        }

        //Check if is in the same direction
        int ratio = (normal * (t0 - position)) / (normal * speed);
        if(ratio < 0 || ratio < 0 || ratio < 0){
             return {0, 0, 0};
        }
        
        //Check if is in the triangle
        Vector3d intersection = position + speed * ratio;

        double det0 = (t1 - t0) * (intersection - t0);
        double det1 = (t2 - t1) * (intersection - t1);
        double det2 = (t0 - t2) * (intersection - t2);

        if( (det0 <= 0 && det1 <= 0 && det2 <= 0) || 
            (det0 >= 0 && det1 >= 0 && det2 >= 0)){
            return intersection;
        }
        
        return {0, 0, 0};
    }
};

