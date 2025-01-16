#include "window.h"

OGL_Window::OGL_Window(int width, int height, std::string name, bool fullscreen) {

    glewInit();
	if (!glfwInit()) {
		std::cerr << "Failed to init GLFW" << std::endl;
		exit(-1);
	}
	if (fullscreen) {
		window = glfwCreateWindow(width, height, name.c_str(), glfwGetPrimaryMonitor(), NULL);
	} else {
		window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
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

	// glViewport(0, 0, width, height); viewport is automatically set to window size 
}


OGL_Window::~OGL_Window() {
    glfwDestroyWindow(window);
	glfwTerminate();
}

GLFWwindow* OGL_Window::getWindow() {
    return this->window;
}
