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
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   ourColor = aColor;\n"
    "}\n";

static const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main() {\n"
    "   FragColor = vec4(ourColor, 1.0f);\n"
    "}\n";
