#ifndef CALLBACK_H
#define CALLBACK_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <stdio.h>

#include "constants.h"

#ifndef CALLBACK_NO_INLINE
#define CALLBACK_H_FUNC static
#else
#define CALLBACK_H_FUNC static inline
#endif

#endif // CALLBACK_H

// CALLBACK_H_FUNC void error_callback(int error, const char* description)
// {
//     fprintf(stderr, "Error: %s\n", description);
// }

// CALLBACK_H_FUNC void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
//     if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, GLFW_TRUE);
// }

CALLBACK_H_FUNC void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // making the app match the new window dimensions
    glViewport(0, 0, width, height);
}

CALLBACK_H_FUNC void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xPos = (float)xposIn;
    float yPos = (float)yposIn;

    if (firstMouse) {
        lastX = xPos;
        lastY = yPos;
        firstMouse =  false;
    }

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;

    camera.processMouseMovement(xOffset, yOffset);
}

CALLBACK_H_FUNC void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.processMouseScroll((float)yoffset);
}