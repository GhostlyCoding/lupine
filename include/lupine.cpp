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

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    //glGenBuffers(1, &this->EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_DYNAMIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

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
    Handler::getInstance().getVertices();
    if((Handler::getInstance().FLAG >> 0) & 1U) {
        float vertices[Handler::getInstance().vertices.size()];
        int indices[Handler::getInstance().indices.size()];

        for(int i=0; i < Handler::getInstance().vertices.size(); i++) {
            vertices[i] = Handler::getInstance().vertices[i];
        }

        for(int i=0; i < Handler::getInstance().indices.size(); i++) {
            indices[i] = Handler::getInstance().indices[i];
        }

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
        /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);*/
        Handler::getInstance().FLAG &= ~(1UL << 0);
    }

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -20.0f));
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    int viewLoc = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projLoc = glGetUniformLocation(shader.ID, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    for(int i=0; i < Handler::getInstance().indices.size()/3; i++){
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, Handler::getInstance().triangles[i]->center);
        model = glm::scale(model, glm::vec3(Handler::getInstance().triangles[i]->scale));

        int modelLoc = glGetUniformLocation(shader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glDrawArrays(GL_TRIANGLES, i*3, 3);
    }
    glBindVertexArray(0);
}

void Lupine::background(float r, float g, float b, float a) {
    glClearColor(r/255, g/255, b/255, a/255);
    glClear(GL_COLOR_BUFFER_BIT);
}

// handler passthroughs
void Lupine::unregisterTriangle(Triangle triangle) {
    Handler::getInstance().unregisterTriangle(triangle);
}
