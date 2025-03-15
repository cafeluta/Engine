#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "lib/linmath.h"
#include "lib/callback.h"
#include "include/shader.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

// TRIANGLE 
float vertices[] = {
    // colors           rgb
    -0.25f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.25f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
};

int main() {
    if (!glfwInit()) {
        // Initialization failed
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Shaders", NULL, NULL);
    if (!window) {
        // Window creation failed
        exit(EXIT_FAILURE);
    }
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        // Glad initialization failed
        exit(EXIT_FAILURE);
    }
    glfwSwapInterval(1);

    // VERTEX OBJECTS
    GLuint VBO;
    glGenBuffers(1, &VBO);
    
    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    // // VERTEX SHADER
    // GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // glCompileShader(vertexShader);
    // checkIfCompileWasSuccessful(&vertexShader, "VERTEX");

    // // FRAGMENT SHADER
    // GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // glCompileShader(fragmentShader);
    // checkIfCompileWasSuccessful(&fragmentShader, "FRAGMENT");

    // // SHADER PROGRAM
    // GLuint shaderProgram = glCreateProgram();
    // glAttachShader(shaderProgram, vertexShader);
    // glAttachShader(shaderProgram, fragmentShader);
    // glLinkProgram(shaderProgram);
    // checkIfCompileWasSuccessful(&shaderProgram, "PROGRAM");

    // glDeleteShader(vertexShader);
    // glDeleteShader(fragmentShader);

    Shader shader;
    Shader_init(&shader, "ssc/vertex_shader.glsl", "ssc/fragment_shader.glsl");
    Shader_use(&shader);

    // LINKING
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // POSITION ATTRIBUTE
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);  // stride = distance between elements
    glEnableVertexAttribArray(0);  // position has location = 0

    // COLOR ATTRIBUTE
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);  // color has location = 1


    // LOOP
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Shader_use(&shader); 

        // Gradually changing color over time
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        // we get the location of ourColor from fragmentShaderSource
        // int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        Shader_setFloat4(&shader, "ourColor", 0.0f, greenValue, 0.0f, 1.0f);

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