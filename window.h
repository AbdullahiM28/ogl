#ifndef OGL_WINDOW.H
#define OGL_WINDOW.H

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
        
        void drawRectangle(int width = 5, int height = 5, Colors c = Colors::WHITE);
        // void drawText(put params here);

        void startDrawing();
       // void chooseColor(Color c);
        void stopDrawing();

        GLFWwindow* getWindow();
};

#endif
