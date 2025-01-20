#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include <map>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Global variables
GLFWwindow* window;
GLuint shaderProgram;
std::map<GLchar, GLuint> CharacterTextures;
GLuint VAO, VBO;

// Shader program loading (vertex and fragment shaders)
GLuint loadShader(const char* vertexPath, const char* fragmentPath) {
    // (Shader loading logic here)
    // Return the compiled shader program
}

void initOpenGL() {
    if (!glfwInit()) { std::cerr << "GLFW initialization failed!" << std::endl; exit(-1); }
    window = glfwCreateWindow(800, 600, "OpenGL Text", nullptr, nullptr);
    if (!window) { glfwTerminate(); std::cerr << "Window creation failed!" << std::endl; exit(-1); }
    glfwMakeContextCurrent(window);
    glewInit();
    
    // Load and compile shaders
    shaderProgram = loadShader("vertex_shader.glsl", "fragment_shader.glsl");
    
    // Setup OpenGL buffers for text rendering (quad for each character)
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    GLfloat vertices[] = {
        // Positions     // Texture Coords
        0.0f,  1.0f,  0.0f, 1.0f,  // top-left
        0.0f,  0.0f,  0.0f, 0.0f,  // bottom-left
        1.0f,  0.0f,  1.0f, 0.0f,  // bottom-right
        1.0f,  1.0f,  1.0f, 1.0f   // top-right
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void loadFont(const char* fontPath) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) { std::cerr << "Could not init FreeType!" << std::endl; exit(-1); }

    FT_Face face;
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

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    for (const char &c : text) {
        GLuint texture = CharacterTextures[c];
        glBindTexture(GL_TEXTURE_2D, texture);

        // Calculate the character's position on the screen
        float xpos = x;
        float ypos = y;

        // Update character's quad vertices based on character size
        GLfloat vertices[6][4] = {
            { xpos,     ypos + 48.0f,   0.0f, 1.0f },
            { xpos,     ypos,            0.0f, 0.0f },
            { xpos + 48.0f, ypos,        1.0f, 0.0f },

            { xpos,     ypos + 48.0f,   0.0f, 1.0f },
            { xpos + 48.0f, ypos,        1.0f, 0.0f },
            { xpos + 48.0f, ypos + 48.0f, 1.0f, 1.0f }
        };

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (48.0f + 1.0f) * scale;  // Advance to the next character
    }

    glBindVertexArray(0);
}

int main() {
    initOpenGL();
    loadFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf");

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
