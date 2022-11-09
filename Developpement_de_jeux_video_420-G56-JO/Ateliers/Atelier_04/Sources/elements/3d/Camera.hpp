#pragma once

#include "../../Matrix44d.hpp"

class Camera {
private:
    Vector3d position;  
    Matrix44d viewMatrix;

public:
    void setView(const Vector3d& position, const Vector3d& target, const Vector3d& up){
        this->position = position;        
        
        Vector3d f = target - position; f.normalized();
        Vector3d s = f * up; s.normalized();
        Vector3d u = s * f; u.normalized();
        
        viewMatrix.loadView(f, s, u);
    }

    void applyView(){
        glMultMatrixd(viewMatrix.elements);
        glTranslated(-position.x, -position.y, -position.z);
    }
};