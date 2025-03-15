#ifndef SSC_H
#define SSC_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#ifndef SSC_NO_INLINE
#define SSC_H_FUNC static
// #else
// #define SSC_H_FUNC static inline
#endif

#endif // SSC_H

// SHADERS SOURCE CODE
static const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "out vec4 vertexColor;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   vertexColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\n";

static const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 ourColor;\n"
    "void main() {\n"
    "   FragColor = ourColor;\n"
    "}\n";
