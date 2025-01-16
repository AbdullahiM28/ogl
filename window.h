#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <string>

enum Colors {
    BLACK, WHITE, RED, BLUE, GREEN, LIGHT_BLUE, PURPLE, YELLOW 
};

class OGL_Window {
    GLFWwindow* window = NULL;

    public:
        OGL_Window(int width, int height, std::string name = "window", bool fullscreen = false);
        ~OGL_Window();
        // drawRectangle(int width, int height, Color c)
        GLFWwindow* getWindow();

};


