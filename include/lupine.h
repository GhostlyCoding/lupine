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
#include "rectangle.h"
#include "shader.h"
#include "handler.h"

class Lupine {
public:
    GLFWwindow* window;
    int err;
    Lupine(const char* name, int width, int height);
    ~Lupine();
    // input
    void registerKey(int key, const std::function<void()>& func);
    void unregisterKey(int key);
    // game engine
    void processInput();
    void background(float r, float g, float b, float a);
    void use();
    void render();
    // handler passthrough functions
    void unregisterTriangle(Triangle triangle);
private:
    std::function<void()> keys[348];
    Shader shader;
    std::vector<float> vertices;
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
