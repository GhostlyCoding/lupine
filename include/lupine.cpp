#include "lupine.h"

Lupine::Lupine(const char* name, int width, int height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    Lupine::window = glfwCreateWindow(800, 600, name, NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        err = -1;
        return;
    }
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        err = -1;
        return;
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    for(int i = 0; i < 348; i++) {
        this->keys[i] = []() {return;};
    }

    char buff[FILENAME_MAX];
    getcwd(buff, FILENAME_MAX);
    std::string currentDirString(buff);
    const char* currentDir = currentDirString.c_str();
    char* vertex = (char*) malloc(FILENAME_MAX);
    strcpy(vertex, currentDir);
    strcat(vertex, "/shaders/vertex.glsl");
    char* fragment = (char*) malloc(FILENAME_MAX);
    strcpy(fragment, currentDir);
    strcat(fragment, "/shaders/fragment.glsl");
    shader = Shader(vertex, fragment);

    float vertexArray[vertices.size()];
    std::copy(vertices.begin(), vertices.end(), vertexArray);
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_DYNAMIC_DRAW);
}

Lupine::~Lupine() {
    glfwTerminate();
}

void Lupine::use() {
    shader.use();
}

void Lupine::registerKey(int key, const std::function<void()>& func) {
    this->keys[key] = func;
}

void Lupine::unregisterKey(int key) {
        this->keys[key] = []() {return;};
}

void Lupine::processInput() {
    for(int i = 0; i < 348; ++i) {
        if(glfwGetKey(this->window, i) == GLFW_PRESS)
            this->keys[i]();
    }
}

void Lupine::background(float r, float g, float b, float a) {
    glClearColor(r/255, g/255, b/255, a/255);
    glClear(GL_COLOR_BUFFER_BIT);
}
