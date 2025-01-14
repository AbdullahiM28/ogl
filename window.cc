#include "window.h"

OGL_Window::OGL_Window() {

    glewInit();
	if (!glfwInit()) {
		std::cerr << "Failed to init GLFW" << std::endl;
		exit(-1);
	}

    window = glfwCreateWindow(600, 600, "Tetris", glfwGetPrimaryMonitor(), NULL);
    if (!window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	// make the OpenGl context current
	glfwMakeContextCurrent(window);

	// Init GLEW 
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to init GLEW" << std::endl;
		exit(-1);
	}

	// set the OpenGL viewport
	glViewport(0, 0, 600, 600);     
}


OGL_Window::~OGL_Window() {
    glfwDestroyWindow(window);
	glfwTerminate();
}

GLFWwindow* OGL_Window::getWindow() {
    return this->window;
}
