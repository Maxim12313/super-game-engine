#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

int main() {
    if (!glfwInit())
        return 1;

    GLFWwindow *window = glfwCreateWindow(640, 400, "hi", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glfwSwapBuffers(window);
    }
    glfwTerminate();
}
