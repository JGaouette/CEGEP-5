#include "Collider.hpp"
#include "Vector3d.hpp"

int main(int argc, char const *argv[])
{
    Vector3d v1 = {1, 1, 0};
    Vector3d v2 = {2, 1, 0};
    Vector3d v3 = {1, 2, 0};

    Vector3d position = {-1.5, -1.5, -2};
    Vector3d speed = {3, 3, 2};
    Vector3d normal = v1 * v2;


    Collider* c = new Collider();
    Vector3d intersection = c->isColliding(position, speed, v1, v2, v3, normal);

    std::cout << "(" << intersection.x << ", " << intersection.y << ", " << intersection.z << ")" << std::endl;

    return 0;
}
