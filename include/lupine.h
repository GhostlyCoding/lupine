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
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "triangle.h"
#include "shader.h"
#include "handler.h"

class Lupine {
public:
    GLFWwindow* window;
    int err;
    Lupine(const char* name, int width, int height);
    ~Lupine();
    void registerKey(int key, const std::function<void()>& func);
    void unregisterKey(int key);
    void processInput();
    void background(float r, float g, float b, float a);
    void use();
private:
    std::function<void()> keys[348];
    Shader shader;
    Handler handler;
    std::vector<float> vertices;
};
