#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "lib/linmath.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

// Vertex input
float vertices[] = {
    0.5f, 0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5, -0.5f, 0.0f,  // bottom left
    -0.5f, 0.5f, 0.0f  // top left
};

GLuint indices[] = {
    0, 1, 3,  // first triangle
    1, 2, 3  // second triangle
};

// SHADERS
const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSource= "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0f, 0.5f, 0.5f, 0.7f);\n"
    "}\0";

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
    // VBO = has brute data in it
    GLuint VBO;  // i use GLuint cuz it has 32bits
    glGenBuffers(1, &VBO);

    // ARRAY OBJ
    // VAO = has the config on how to read data from VBO
    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    // EBO = vertices and indices
    GLuint EBO;
    glGenBuffers(1, &EBO);

    // SHADERS

    // -> VERTEX SHADER
    GLuint vertexShader;  // a program that runs on GPU and memorizes the vertexes and transforms them
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check if compilation was successful
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
    }

    // -> FRAGMENT SHADER
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check if compilation was successful
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
    }

    // -> SHADER PROGRAM
    // We need this everytime we render objects in our project
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check if linking was successful
    // They must pe linked like this vertexShader -> output -> input -> fragementShader
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n%s\n", infoLog);   
    }

    // -> DELETING SHADERS AFTER MAKING PROGRAM
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // LINKING
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  // we copy the data from vertices to our buffer

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // 1st argument = location of vertexShader
    // 2nd argument = vertex its a vec3
    // 4th argument = normalized (true / false)  
    // 5th argument = offset
    // glEnableVertexArrayAttrib(NULL, 0);
    glEnableVertexArrayAttrib(VAO, 0);
    glUseProgram(shaderProgram);

    // WIREFRAME
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Shader program
        glUseProgram(shaderProgram);

        // USING VBO + VAO
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        // DRAW TRIANGLE
        // glDrawArrays(GL_TRIANGLES, 0, 3);


        // USING EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}