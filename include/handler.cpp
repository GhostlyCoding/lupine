#include "handler.h"

Handler::Handler() {
    //
}

void Handler::registerTriangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3,
        glm::vec3 c1, glm::vec3 c2, glm::vec3 c3) {
    Triangle triangle(p1, p2, p3, c1, c2, c3);

    triangles.push_back(triangle);
}
