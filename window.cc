#include "window.h"

OGL_Window::OGL_Window() {
    glewInit();
    this->window = glfwCreateWindow(600, 600, "NIGG NIGG REGGIN", NULL, NULL);
            
}


OGL_Window::~OGL_Window() {
    glfwDestroyWindow(window);
	glfwTerminate();
}

GLFWwindow* OGL_Window::getWindow() {
    return this->window;
}
