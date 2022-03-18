#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "triangle.h"

class Handler {
public:
    Handler();

    Triangle registerTriangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3,
        glm::vec3 c1,glm::vec3 c2,glm::vec3 c3);
    void unregisterTriangle(Triangle triangle);
    
    void getVertices();

    std::vector<float> vertices;
    std::vector<int> indices;
private:
    std::vector<Triangle> triangles;
};
