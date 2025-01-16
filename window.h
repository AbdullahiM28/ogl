#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>

enum Colors {
    BLACK, WHITE, RED, BLUE, GREEN, LIGHT_BLUE, PURPLE, YELLOW 
};

class OGL_Window {
    GLFWwindow* window = NULL;

    public:
        OGL_Window(int width, int height, bool fullscreen = false); // ctor
        ~OGL_Window(); // dtor
        // drawRectangle(int width, int height, Color c)
        GLFWwindow* getWindow();

};


