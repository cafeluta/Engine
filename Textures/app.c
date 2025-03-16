#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "lib/linmath.h"
#include "lib/callback.h"
#include "include/stb_image.h"
#include "include/shader.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

// TRIANGLE 
float vertices[] = {
    // colors           rgb               texPos
    -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f
};

// TEXTURE
// float texCoords[] = {
//     0.0f, 0.0f,
//     1.0f, 0.0f,
//     0.5f, 1.0f
// };

int main() {
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Shaders", NULL, NULL);
    if (!window) {
        exit(EXIT_FAILURE);
    }
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        exit(EXIT_FAILURE);
    }
    glfwSwapInterval(1);

    // BUFFERS
    GLuint VBO;
    glCreateBuffers(1, &VBO);

    GLuint VAO;
    glCreateVertexArrays(1, &VAO);

    // SHADER PROGRAM
    Shader shader;
    Shader_init(&shader, "ssc/vertex_shader.glsl", "ssc/fragment_shader.glsl");
    Shader_use(&shader);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // POSITION ATTRIBUTE
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // COLOR ATTRIBUTE
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // TEXCOORD ATTRIBUTE
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // TEXTURE
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // TEXTURE WRAPPING
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);  // x axis
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);  // y axis

    // TEXTURE FILTERING
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // when zoomed out its smooth
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // when zoomed in we see the individual pixels

    // LOAD IMAGE
    int width, height, nrChannels;  // nrChannels = 3 (rgb) / 4 (rgba)
    unsigned char* data = stbi_load("img/wall.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("Failed to load texture!\n");
        return -1;
    }
    stbi_image_free(data);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Shader_use(&shader);

        float timeValue = glfwGetTime();
        float redValue = (sin(timeValue) / 2.0f) + 0.5f;
        Shader_setFloat4(&shader, "ourColor", redValue, 0.0f, 0.0f, 1.0f);

        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}