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
    glfwSetFramebufferSizeCallback(window, Lupine::framebuffer_size_callback);

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

    glGenBuffers(1, &this->VBO);

    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &this->EBO);
    glBindBuffer(GL_ARRAY_BUFFER, EBO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));

    Handler handler;
}

void Lupine::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
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

void Lupine::render() {
    handler.getVertices();
    float vertices[handler.vertices.size()];
    int indices[handler.indices.size()];

    for(int i=0; i < handler.vertices.size(); i++) {
        vertices[i] = handler.vertices[i];
    }
    std::cout << "[";
    for(int i=0; i < handler.indices.size(); i++) {
        indices[i] = handler.indices[i];
        std::cout << handler.indices[i] << ", ";
    }
    std::cout << "]" << std::endl;

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, handler.indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Lupine::background(float r, float g, float b, float a) {
    glClearColor(r/255, g/255, b/255, a/255);
    glClear(GL_COLOR_BUFFER_BIT);
}

// handler passthroughs
Triangle Lupine::registerTriangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3,
        glm::vec3 c1, glm::vec3 c2, glm::vec3 c3) {
    return handler.registerTriangle(p1, p2, p3, c1, c2, c3);
}
void Lupine::unregisterTriangle(Triangle triangle) {
    handler.unregisterTriangle(triangle);
}
