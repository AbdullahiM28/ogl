#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>

class OGL_Window {
    GLFWwindow* window;

    public:
        OGL_Window(); // ctor
        ~OGL_Window(); // dtor
        GLFWwindow* getWindow();

};


