#include "../include/lupine.h"

int main() {
    const char* name = "name";
    Lupine lupine(name, 800, 600); 
    if(lupine.err == -1) {
        return -1;
    }

    lupine.registerKey(GLFW_KEY_ESCAPE, [&lupine](){ glfwSetWindowShouldClose(lupine.window, true); });

    while (!glfwWindowShouldClose(lupine.window)) {
        lupine.processInput();

        lupine.background(124, 152, 194, 255);

        lupine.use();

        glfwSwapBuffers(lupine.window);
        glfwPollEvents();
    }

    return 0;
}
