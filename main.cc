#include <functional>
#include <iostream>
#include <unordered_map>
#include <utility>
#include "window.h"


class hash_pair { // lifted from geeksforgeeks
	public:
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const
    {
        // Hash the first element
        size_t hash1 = std::hash<T1>{}(p.first);
        // Hash the second element
        size_t hash2 = std::hash<T2>{}(p.second);
        // Combine the two hash values
        return hash1
               ^ (hash2 + 0x9e3779b9 + (hash1 << 6)
                  + (hash1 >> 2));
    }
};

int main() {
	float speed = 3; // determines have fast the block drops
	OGL_Window w;
	GLFWwindow *window = w.getWindow();



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

		using namespace std::chrono;
		auto start = steady_clock::now();
        while (duration_cast<seconds>(steady_clock::now() - start).count() < speed) {
			// DO NOTHING
        }
		std::cout << x << std::endl;
		x++;
	}



	
	return 0;	
}







