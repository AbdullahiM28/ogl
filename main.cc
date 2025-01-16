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


	// making each point 0.25f makes the square smaller (compared to 0.5f)
	// adding 0.5f to a point moves the point to the right
	// adding 0.5f to all points puts the square in the top right
	float vertices[] = { 
    	-0.25f,  0.25f,  // top-left
    	0.25f,  0.25f,   // top-right
    	-0.25f, -0.25f,  // bottom-left
    	0.25f, -0.25f  // bottom-right
	};
	
	int x = 0;
	// render loop
	OGL_Window w;
	GLFWwindow *window = w.getWindow();

	while (true) {
			// #### glClearColour(red, green, blue, opaqueness)

	if (x % 3 == 0) {
			glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // puts color on the screen
			glClear(GL_COLOR_BUFFER_BIT); // clears the screen
			
	} else if (x % 3 == 1) {
			glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // puts color on the screen
			glClear(GL_COLOR_BUFFER_BIT); // clears the screen
			
	} else {
			glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // puts color on the screen
			glClear(GL_COLOR_BUFFER_BIT); // clears the screen
	}


	glEnableClientState(GL_VERTEX_ARRAY); // eneables drawing (using arrays)
    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY); // disables drawing

	glfwSwapBuffers(window);

	glfwPollEvents();
		using namespace std::chrono;
		auto start = steady_clock::now();
        while (duration_cast<seconds>(steady_clock::now() - start).count() < speed) {
			// DO NOTHING for speed amount of seconds
			for (int i = 0; i < 8; i++) {
				vertices[i] += 0.25f;
			}
        }
		std::cout << x << std::endl;
		x++;
	}
	return 0;	
}

