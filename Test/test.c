#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "lib/linmath.h"
 
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>


typedef struct Vertex {
    vec2 pos;  // Position
    vec3 col;  // RGB color
} Vertex;

// Triangle
static const Vertex vertices[3] = {
    { { -0.6f, -0.4f }, { 1.f, 0.f, 0.f } },
    { {  0.6f, -0.4f }, { 0.f, 1.f, 0.f } },
    { {   0.f,  0.6f }, { 0.f, 0.f, 1.f } }
};

static const char* vertex_shader_text =
"#version 330\n"  // 1. Definirea versiunii GLSL (în acest caz 3.30 pentru OpenGL 3.3)
"uniform mat4 MVP;\n"  // 2. Uniformă (matrice de transformare MVP)
"in vec3 vCol;\n"  // 3. Intrare (culoarea vertex-ului)
"in vec2 vPos;\n"  // 4. Intrare (poziția 2D a vertex-ului)
"out vec3 color;\n"  // 5. Ieșire (culoarea vertex-ului)
"void main()\n"  // 6. Funcția principală (execuată pentru fiecare vertex)
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"  // 7. Calculul poziției finale a vertex-ului
"    color = vCol;\n"  // 8. Atribuirea culorii
"}\n";  // 9. Închiderea funcției

static const char* fragment_shader_text =
"#version 330\n"
"in vec3 color;\n"
"out vec4 fragment;\n"
"void main()\n"
"{\n"
"    fragment = vec4(color, 1.0);\n"
"}\n";

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {
    glfwSetErrorCallback(error_callback);

    // INITIALIZATION
    if (!glfwInit())
    {
        // Initialization failed
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(640, 480, "Triangle", NULL, NULL);
    if (!window)
    {
        // Window or OpenGL context creation failed
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetKeyCallback(window, key_callback);

    // OpenGL can't work directly with windows so we need a context
    glfwMakeContextCurrent(window);
    // Loading extensions library
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Eroare: GLAD nu a fost inițializat corect!\n");
        return -1;
    }
    glfwSwapInterval(1);

    // BUFFERS
    GLuint vertex_buffer;  // this buffer takes the data for the points of the triangle
    glGenBuffers(1, &vertex_buffer);  // we gen a buffer for the vertex_buffer
    

    while (!glfwWindowShouldClose(window)) {
        // Gets the keypresses
        glfwPollEvents(); 
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}