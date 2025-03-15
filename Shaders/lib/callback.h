#ifndef CALLBACK_H
#define CALLBACK_H

#include <GLFW/glfw3.h>
#include <stdio.h>

#ifndef CALLBACK_NO_INLINE
#define CALLBACK_H_FUNC static
#else
#define CALLBACK_H_FUNC static inline
#endif

#endif // CALLBACK_H

CALLBACK_H_FUNC void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

CALLBACK_H_FUNC void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}