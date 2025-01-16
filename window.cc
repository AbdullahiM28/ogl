#include "window.h"

OGL_Window::OGL_Window(int width, int height, bool fullscreen) {

    glewInit();
	if (!glfwInit()) {
		std::cerr << "Failed to init GLFW" << std::endl;
		exit(-1);
	}
	if (fullscreen) {
		window = glfwCreateWindow(width, height, "Tetris", glfwGetPrimaryMonitor(), NULL);
	} else {
		window = glfwCreateWindow(width, height, "Tetris", NULL, NULL);
	}
    
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
	glViewport(0, 0, width + 100, height + 100);     
}


OGL_Window::~OGL_Window() {
    glfwDestroyWindow(window);
	glfwTerminate();
}

GLFWwindow* OGL_Window::getWindow() {
    return this->window;
}
