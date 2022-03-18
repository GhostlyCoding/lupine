#include "triangle.h"

Triangle::Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3,
        glm::vec3 c1,glm::vec3 c2,glm::vec3 c3){
    this->c1 = c1;
    this->c2 = c2;
    this->c3 = c3;

    // find center
    float av1 = (p1.x + p2.x + p3.x) / 3.0f;
    float av2 = (p1.y + p2.y + p3.y) / 3.0f;
    float av3 = (p1.z + p2.z + p3.z) / 3.0f;
    this->center = glm::vec3(av1, av2, av3);

    std::cout << p3.x << std::endl;

    // translate points to the center
    glm::vec3 tp1 = p1 - center;
    glm::vec3 tp2 = p2 - center;
    glm::vec3 tp3 = p3 - center;

    float dist1 = tp1.length();
    float dist2 = tp2.length();
    float dist3 = tp3.length();

    this->scale = std::max(std::max(dist1,dist2),dist3);


    this->p1 = tp1 / scale;
    this->p2 = tp2 / scale;
    this->p3 = tp3 / scale;
}

float* Triangle::getVertices() {
    float* vertices = new float[]{
        p1.x, p1.y, p1.z, c1.x, c1.y, c1.z,
        p2.x, p2.y, p2.z, c2.x, c2.y, c2.z,
        p3.x, p3.y, p3.z, c3.x, c3.y, c3.z
    };
    return vertices;
}
