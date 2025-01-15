#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>

class OGL_Window {
    GLFWwindow* window = NULL;

    public:
        OGL_Window(bool fullscreen = false); // ctor
        ~OGL_Window(); // dtor
        GLFWwindow* getWindow();

};


