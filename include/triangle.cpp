#include "triangle.h"

Triangle::Triangle() {
/*
    this->c1 = glm::vec3(0,0,0);
    this->c2 = glm::vec3(0,0,0);
    this->c3 = glm::vec3(0,0,0);

    // find center
    this->center = glm::vec3(0, 0, 0);

    // translate points to the center
    glm::vec3 tp1 = glm::vec3(0, 0, 0);
    glm::vec3 tp2 = glm::vec3(0, 0, 0);
    glm::vec3 tp3 = glm::vec3(0, 0, 0);

    this->scale = 0;


    this->p1 = tp1 / 1.0f;
    this->p2 = tp2 / 1.0f;
    this->p3 = tp3 / 1.0f;
    Handler::getInstance().registerTriangle(this);*/
    this->c1 = glm::vec3(0,0,0);
    this->c2 = glm::vec3(0,0,0);
    this->c3 = glm::vec3(0,0,0);

    this->center = glm::vec3(0, 0, 0);
    this->scale = 0;

    this->p1 = glm::vec3(0,0,0);
    this->p2 = glm::vec3(0,0,0);
    this->p3 = glm::vec3(0,0,0);
}

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

    // translate points to the center
    glm::vec3 tp1 = p1 - center;
    glm::vec3 tp2 = p2 - center;
    glm::vec3 tp3 = p3 - center;

    float dist1 = glm::distance(center, p1);
    float dist2 = glm::distance(center, p2);
    float dist3 = glm::distance(center, p3);

    this->scale = std::max(std::max(dist1,dist2),dist3);


    this->p1 = tp1 / scale;
    this->p2 = tp2 / scale;
    this->p3 = tp3 / scale;
    Handler::getInstance().registerTriangle(this);
}
Triangle Triangle::operator()(glm::vec3 p1,glm::vec3 p2,glm::vec3 p3,
    glm::vec3 c1, glm::vec3 c2, glm::vec3 c3){
    this->c1 = c1;
    this->c2 = c2;
    this->c3 = c3;

    std::cout << p1.x << std::endl;
    float av1 = (p1.x + p2.x + p3.x) / 3.0f;
    float av2 = (p1.y + p2.y + p3.y) / 3.0f;
    float av3 = (p1.z + p2.z + p3.z) / 3.0f;
    this->center = glm::vec3(av1, av2, av3);

    glm::vec3 tp1 = p1 - center;
    glm::vec3 tp2 = p2 - center;
    glm::vec3 tp3 = p3 - center;

    float dist1 = glm::distance(center, p1);
    float dist2 = glm::distance(center, p2);
    float dist3 = glm::distance(center, p3);

    this->scale = std::max(std::max(dist1,dist2),dist3);

    this->p1 = tp1 / scale;
    this->p2 = tp2 / scale;
    this->p3 = tp3 / scale;
    Handler::getInstance().registerTriangle(this);
    return *this;
    //return Triangle(p1, p2, p3, c1, c2, c3);
}

float* Triangle::getVertices() {
    float* vertices = new float[]{
        p1.x, p1.y, p1.z, c1.x, c1.y, c1.z,
        p2.x, p2.y, p2.z, c2.x, c2.y, c2.z,
        p3.x, p3.y, p3.z, c3.x, c3.y, c3.z
    };
    return vertices;
}

void Triangle::move(glm::vec3 m) {
    this->center += m;
}
