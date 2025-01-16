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

// for now, these two functions take now params,
void OGL_Window::startDrawing() {
	glEnableClientState(GL_VERTEX_ARRAY);
}

void OGL_Window::stopDrawing() {
	glDisableClientState(GL_VERTEX_ARRAY);
}

void OGL_Window::drawRectangle(int width, int height, Colors c) {
	float vertices[] = { 
    	-0.01f * width,  0.01f * height,  // top-left (x, y)
    	0.01f * width,  0.01f * height,   // top-right 
    	-0.01f * width, -0.01f * height,  // bottom-left
    	0.01f * width, -0.01f * height  // bottom-right
	};
	startDrawing();
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	// chooseColor(c); // this will clear the old color then choose the new color
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	stopDrawing();

	glfwSwapBuffers(window);
	glfwPollEvents();
}
