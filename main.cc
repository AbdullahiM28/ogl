#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>

int main() {
	
	glewInit();

	if (!glfwInit()) {
		std::cerr << "Failed to init GLFW" << std::endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(600, 600, "NIGG NIGG REGGIN", NULL, NULL);
	if (!window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// make the OpenGl context current
	glfwMakeContextCurrent(window);

	// Init GLEW 
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to init GLEW" << std::endl;
		return -1;
	}

	// set the OpenGL viewport
	glViewport(0, 0, 600, 600);

 	float vertices[] = {
                0.0f, 0.5f,
                -0.5f, -0.5f,
                0.5f, -0.5f
        };
	
	int x = 0;
	// render loop
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT); // clears the screen

		// draw something
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // clear with blue color

		glEnableClientState(GL_VERTEX_ARRAY);
        	glVertexPointer(2, GL_FLOAT, 0, vertices);
       		glDrawArrays(GL_TRIANGLES, 0, 3);
        	glDisableClientState(GL_VERTEX_ARRAY);
		
		glfwSwapBuffers(window);

		glfwPollEvents();

        while (duration_cast<seconds>(steady_clock::now() - start).count() < 3) {
            std::cout << x << std::endl;
        }
		x++;

	}


	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;	
	
}







