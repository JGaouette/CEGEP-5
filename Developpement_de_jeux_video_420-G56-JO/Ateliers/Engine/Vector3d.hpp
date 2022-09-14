#include <math.h>

struct Vector3d{
    double x, y, z;

    Vector3d(double x, double y, double z){
    
    }

    ~Vector3d();

    double norm(){
        return sqrt(x * x + y * y + z * z);
    }
    
    Vector3d normalized(){
        return Vector3d(x / norm(), y / norm(), z / norm());
    }

    Vector3d operator+(const Vector3d& v){
        return Vector3d(x + v.x, y + v.y, z + v.z);
    }

    Vector3d operator-(const Vector3d& v){
        return Vector3d(x - v.x, y - v.y, z - v.z);
    }

    Vector3d operator*(const Vector3d& v){
        return Vector3d((v.y * z) - (y * v.z), (v.z * x) - (z * v.x), (v.x * y) - (x * v.y));
    }

    Vector3d operator*(const double n){
        return Vector3d(x * n, y * n, z * n);
    }

    double operator%(const Vector3d& v){
        return x * v.x + y * v.y + z * v.z;
    }

    double angleBetween(Vector3d v){
        return acos(*this % v / (norm() * v.norm()));
    }
};