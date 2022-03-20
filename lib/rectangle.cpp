#include "rectangle.h"
Rectangle::Rectangle(glm::vec3 pos, float width, float height, glm::vec3 rot,
        glm::vec3 c1,glm::vec3 c2,glm::vec3 c3,glm::vec3 c4) {
    glm::vec3 p1 = pos;
    glm::mat4 rotation = glm::mat4(1.0f);
    rotation = glm::translate(rotation, pos);
    rotation = glm::rotate(rotation, glm::radians(rot.x), glm::vec3(1.0, 0.0, 0.0));
    rotation = glm::rotate(rotation, glm::radians(rot.y), glm::vec3(0.0, 1.0, 0.0));
    rotation = glm::rotate(rotation, glm::radians(rot.z), glm::vec3(0.0, 0.0, 1.0));
    rotation = glm::translate(rotation, -pos);
    glm::vec4 p2 = glm::vec4(pos.x+width, pos.y, pos.z,1);
    p2 = rotation * p2;
    glm::vec4 p3 = glm::vec4(pos.x, pos.y-height, pos.z,1);
    p3 = rotation * p3;
    glm::vec4 p4 = glm::vec4(pos.x+width, pos.y-height, pos.z,1);
    p4 = rotation * p4;
    //triangle1 = Handler::getInstance().registerTriangle(p1,p2,p3,c1,c2,c3);
    triangle1 = triangle1(p1,p2,p3,c1,c2,c3);
    //triangle2 = Handler::getInstance().registerTriangle(p2,p4,p3,c2,c4,c3);
    triangle2 = triangle2(p2,p4,p3,c2,c4,c3);
}
Rectangle::Rectangle(glm::vec3 pos, float width, float height, glm::vec3 rot, glm::vec3 c) {
    Rectangle(pos, width, height, rot, c, c, c, c);
}
