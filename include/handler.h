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
    static Handler& getInstance();
    void registerTriangle(Triangle* triangle);
    void unregisterTriangle(Triangle triangle);
    
    void getVertices();

    std::vector<Triangle*> triangles;
    std::vector<float> vertices;
    std::vector<int> indices;
    unsigned int FLAG;
private:
    Handler();
};
