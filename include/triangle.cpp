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
    center = glm::vec3(av1, av2, av3);

    // translate points to the center
    glm::vec3 tp1 = p1 - center;
    glm::vec3 tp2 = p2 - center;
    glm::vec3 tp3 = p3 - center;
}
