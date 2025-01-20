#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include <map>
#include <string>
#include <glm/glm.hpp>  // for position and color handling

GLFWwindow* window;
GLuint shaderProgram;
std::map<GLchar, GLuint> CharacterTextures;

void initOpenGL() {
    if (!glfwInit()) { std::cerr << "GLFW initialization failed!" << std::endl; exit(-1); }
    window = glfwCreateWindow(800, 600, "OpenGL Text", nullptr, nullptr);
    if (!window) { glfwTerminate(); std::cerr << "Window creation failed!" << std::endl; exit(-1); }
    glfwMakeContextCurrent(window);
    glewInit();
}

void loadFont(const char* fontPath) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) { std::cerr << "Could not init FreeType!" << std::endl; exit(-1); }

    FT_Face face;
    std::cout << fontPath << std::endl;
    if (FT_New_Face(ft, fontPath, 0, &face)) { std::cerr << "Could not open font!" << std::endl; exit(-1); }
    FT_Set_Pixel_Sizes(face, 0, 48);

    for (GLubyte c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) continue;
        
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows,
                     0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        CharacterTextures[c] = texture;
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void renderText(const std::string &text, float x, float y, float scale, glm::vec3 color) {
    glUseProgram(shaderProgram);
    glUniform3f(glGetUniformLocation(shaderProgram, "textColor"), color.x, color.y, color.z);

    for (const char &c : text) {
        GLuint texture = CharacterTextures[c];
        glBindTexture(GL_TEXTURE_2D, texture);

        // Rendering the character (set up your quad vertices and texture coords)
    }
}

int main() {
    initOpenGL();    // Initialize GLFW, GLEW, OpenGL
    loadFont("path_to_font.ttf");  // Load the font

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        renderText("Hello, OpenGL!", 25.0f, 25.0f, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
