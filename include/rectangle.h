#pragma once

#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "triangle.h"
#include "handler.h"

class Rectangle {
public:
    Rectangle(glm::vec3 pos, float width, float height, glm::vec3 rot,
            glm::vec3 c1,glm::vec3 c2,glm::vec3 c3,glm::vec3 c4);
    Rectangle(glm::vec3 pos, float width, float height, glm::vec3 rot, glm::vec3 c);
private:
    Triangle triangle1;
    Triangle triangle2;
};
