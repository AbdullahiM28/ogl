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

	glColor3f(0.0f, 0.0f, 0.0f); // sets the drawing color
	chooseColor(c);


    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	stopDrawing();

	glfwSwapBuffers(window);
	glfwPollEvents();
}

GLFWwindow* OGL_Window::getWindow() {
    return this->window;
}

std::array<float, 4> OGL_Window::getColor(Colors c) {
	switch (c) {
		case Colors::BLACK:
			return std::array<float, 4> {0.0f, 0.0f, 0.0f, 1.0f};

		case Colors::WHITE:
			return std::array<float, 4> {1.0f, 1.0f, 1.0f, 1.0f};

		case Colors::RED:
			return std::array<float, 4> {1.0f, 0.0f, 0.0f, 1.0f};

		case Colors::GREEN:
			return std::array<float, 4> {0.0f, 1.0f, 0.0f, 1.0f};
	
		case Colors::BLUE:
			return std::array<float, 4> {0.0f, 0.0f, 1.0f, 1.0f};

		case Colors::CYAN:
			return std::array<float, 4> {0.0f, 1.0f, 1.0f, 1.0f};

		case Colors::YELLOW:
			return std::array<float, 4> {1.0f, 1.0f, 0.1f, 1.0f};

		case Colors::PURPLE:
			break;
	}
	return std::array<float, 4> {0.5f, 0.0f, 1.0f, 1.0f}; // purple
}

void OGL_Window::chooseColor(Colors c) {
	// glColor3f(red, green, blue)
	std::array<float, 4> color = getColor(c); // (R, G, B, opacity)
	glColor3f(color[0], color[1], color[2]);
}

void OGL_Window::chooseClearColor(Colors c) {
	std::array<float, 4> color = getColor(c); // (R, G, B, opacity)
	glClearColor(color[0], color[1], color[2], color[3]); // set clear color 
	glClear(GL_COLOR_BUFFER_BIT); // puts clear color on screen
}

