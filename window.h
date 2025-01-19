#ifndef OGL_WINDOW_H
#define OGL_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <array>

enum Colors {
    BLACK, WHITE, RED, BLUE, GREEN, CYAN, PURPLE, YELLOW 
};

class OGL_Window {
    GLFWwindow* window = NULL;

    public:
        OGL_Window(int width, int height, std::string name = "window", bool fullscreen = false);
        ~OGL_Window();
        
        void drawRectangle(int width, int height, Colors c = Colors::BLACK);
        // void drawText(put params here);

        std::array<float, 4> getColor(Colors c); // returns (R, G, B, opacity)
        GLFWwindow* getWindow();

        void chooseColor(Colors c);
        void chooseClearColor(Colors c);
        void startDrawing();
        void stopDrawing();

};

#endif
